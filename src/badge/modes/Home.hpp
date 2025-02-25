#ifndef MODE_HOME_HPP
#define MODE_HOME_HPP

#include <map>
#include "esp_log.h"
#include "badge/BadgeMode.h"
#include "badge/BadgeManager.h"
#include "Rank.h"

static const char *TAG_HOMEMODE = "HomeMode";

struct MenuItem {
    std::string name;             // Name of the menu item
    std::function<bool()> action; // Action to perform when the item is selected
                                  // Return true if the menu should navigate back, false to stay where it is
};

class HomeMode : public BadgeMode {
  public:
    HomeMode()
        : BadgeMode(ModeType::HOME)
        , taskHandle(nullptr)
        , badgeStartup(true)
        , inMenu(false)
        , switchingModes(false)
        , menuIndex(0) {
        initializeMenu();
    }

    void enter() override {
        ESP_LOGD(TAG_HOMEMODE, "Entering Home mode");
        switchingModes = false;
        if (badgeStartup) {
            badgeStartup = false;
            ESP_LOGD(TAG_HOMEMODE, "Badge startup detected, starting home init task");
            xTaskCreate(homeInitTask, "Home Init Task", 2048, this, 5, &taskHandle);
        } else {
            updateDisplay();
        }
    }

    void leave() override {
        ESP_LOGD(TAG_HOMEMODE, "Exiting Home mode");
        stopInitTask();
        leds->unlockNonAddressable(LED_D); // In case we were in (or switched modes from) the menu
    }

  protected:
    void receiveTouch(TouchEvent event) override {
        // Only react to touch down events
        if (!event.changed || event.type != TOUCH_DOWN) {
            return;
        }

        if (event.pin == HANDSHAKE_1) {
            if (!inMenu) {
                showMainMenu();
            } else {
                navigateBack();
            }
        }
    }

  private:
    TaskHandle_t taskHandle;
    bool badgeStartup;
    bool inMenu;
    bool switchingModes;
    int menuIndex;
    std::vector<MenuItem> currentMenu;
    std::vector<MenuItem> mainMenu;
    std::vector<std::pair<std::vector<MenuItem>, int>> menuStack; // Stack with menu and index

    void initializeMenu() {
        // clang-format off

        // Define the LED Modes submenu
        std::vector<MenuItem> ledModesMenu = {
            {"Red White Blue",      [this]() { return setScene(SceneType::RED_WHITE_BLUE); }},
            {"Celestial Clouds",    [this]() { return setScene(SceneType::CELESTIAL_CLOUDS); }},
            {"Gone to Hell",        [this]() { return setScene(SceneType::GONE_TO_HELL); }},
            {"Secret Combinations", [this]() { return setScene(SceneType::SECRET_COMBINATIONS); }},
            {"The Salamander",      [this]() { return setScene(SceneType::THE_SALAMANDER); }},
            {"Tapir Joyride",       [this]() { return setScene(SceneType::TAPIR_JOYRIDE); }},
            {"Suppressive Badge",   [this]() { return setScene(SceneType::SUPPRESSIVE_BADGE); }},
            {"Thetan Possession",   [this]() { return setScene(SceneType::THETAN_POSSESSION); }},
            {"Crazy",               [this]() { return setScene(SceneType::CRAZY); }},
            {"Drunk as Hell",       [this]() { return setScene(SceneType::DRUNK_AS_HELL); }},
            {"Gone Clear",          [this]() { return setScene(SceneType::GONE_CLEAR);}},
            {"American",            [this]() { return setScene(SceneType::AMERICAN);}},
            {"USMC 2025",           [this]() { return setScene(SceneType::USMC_2025); }},
        };

        // Define the Display Rank submenu
        std::vector<MenuItem> displayRankMenu = {
            {"Private",                                     [this]() { return setRank(RankLevel::Private); }},
            {"Private First Class",                         [this]() { return setRank(RankLevel::Private_First_Class); }},
            {"Lance Corporalss",                            [this]() { return setRank(RankLevel::Lance_Corporal); }},
            {"Corporal",                                    [this]() { return setRank(RankLevel::Corporal); }},
            {"Sergeant",                                    [this]() { return setRank(RankLevel::Sergeant); }},
            {"Staff Sergeant",                              [this]() { return setRank(RankLevel::Staff_Sergeant); }},
            {"Gunnery Sergeant",                            [this]() { return setRank(RankLevel::Gunnery_Sergeant); }},
            {"Master Sergeant",                             [this]() { return setRank(RankLevel::Master_Sergeant); }},
            {"First Sergeant",                              [this]() { return setRank(RankLevel::First_Sergeant); }},
            {"Master Gunnery Sgt",                          [this]() { return setRank(RankLevel::Master_Gunnery_Sergeant); }},
            {"Sergeant Major",                              [this]() { return setRank(RankLevel::Sergeant_Major); }},
            {"Sergeant Major MC",                           [this]() { return setRank(RankLevel::Sergeant_Major_Of_The_Marine_Corps); }},
        };

        // Define the top-level menu
        mainMenu = {
            {"LED Modes",           [this, ledModesMenu]() { return enterSubMenu(ledModesMenu); }},
            {"Display Rank",        [this, displayRankMenu]() { return enterSubMenu(displayRankMenu); }},
            {"Display Handle",      [this]() { return setMode(ModeType::DISPLAY_HANDLE); }},
            {"About",               [this]() { return setMode(ModeType::ABOUT); }},
        };

        // clang-format on
    }

    void showMainMenu() {
        currentMenu = mainMenu;
        inMenu      = true;
        updateDisplay();
    }

    bool enterSubMenu(const std::vector<MenuItem> &subMenu) {
        menuStack.emplace_back(currentMenu, menuIndex); // Save current menu and index
        currentMenu = subMenu;
        menuIndex   = 0;
        updateDisplay();
        return false;
    }

    void navigateBack() {
        if (!menuStack.empty()) {
            // Restore previous menu and index
            std::tie(currentMenu, menuIndex) = menuStack.back();
            menuStack.pop_back();
            updateDisplay();
        } else {
            inMenu = false;
            updateDisplay();
        }
    }

    bool setScene(SceneType scene) {
        leds->setScene(scene);
        return false;
    }

    bool setRank(RankLevel rank) {
        //ESP_LOGE(TAG_HOMEMODE, "------------>: %d", rank); 
        //int displayRankLED = static_cast<int>(rank);
        setRankVariable(static_cast<int>(rank));
        return false;
    }

    bool setMode(ModeType mode) {
        Badge &badge = Badge::getInstance();
        if (badge.hasMode(mode)) {
            switchingModes = true;
            badge.setMode(mode);
        } else {
            ESP_LOGE(TAG_HOMEMODE, "Mode not found: %d", static_cast<int>(mode));
            badge.flashLedStrip(AddressableStrip::TOUCH, CRGB::Yellow, 3, 900);
            return false;
        }

        return true;
    }

    void updateDisplay() {
        ESP_LOGD(TAG_HOMEMODE, "Updating display");

        if (switchingModes) {
            ESP_LOGD(TAG_HOMEMODE, "Switching modes, waiting for mode to change");
            display->clear();
        } else {
            if (inMenu) {
                ESP_LOGD(TAG_HOMEMODE, "Showing menu");
                leds->lockNonAddressable(LED_D, true);
                display->setFont(u8g2_font_ncenB08_tr);

                std::vector<const char *> menuItems;
                for (const auto &item : currentMenu) {
                    menuItems.push_back(item.name.c_str());
                }

                display->showList(menuItems.data(), menuItems.size(), menuIndex, [this](int index) {
                    if (index == -1) {
                        navigateBack();
                    } else if (index >= 0 && index < currentMenu.size()) {
                        menuIndex = index;
                        if (currentMenu[index].action()) {
                            navigateBack();
                        } else {
                            updateDisplay();
                        }
                    }
                });
            } else {
                ESP_LOGD(TAG_HOMEMODE, "USMC 1775-2025");
                leds->unlockNonAddressable(LED_D);
                display->drawImage(ImageID::USMC_V2, 0, 0);
            }
        }

        // Make sure the init task is stopped
        stopInitTask();
    }

    void stopInitTask() {
        if (taskHandle) {
            ESP_LOGD(TAG_HOMEMODE, "Stopping home init task");

            // If called from the task itself
            if (xTaskGetCurrentTaskHandle() == taskHandle) {
                ESP_LOGD(TAG_HOMEMODE, "Deleting self");
                taskHandle = nullptr;
                vTaskDelete(nullptr);
            }
            // If called from outside the task
            else {
                ESP_LOGD(TAG_HOMEMODE, "Deleting task");
                vTaskDelete(taskHandle);
                taskHandle = nullptr;
            }
        }
    }

    static void homeInitTask(void *pvParameters) {
        HomeMode *self = static_cast<HomeMode *>(pvParameters);
        self->runInit();
    }

    void runInit() {
        // Set the menu flag to false in case we're coming back from somewhere else
        inMenu = false;

        // Start default Rank
        //setRank(RankLevel::NONE);

        // Start the LEDs
        ESP_LOGD(TAG_HOMEMODE, "USMC 2025");
        leds->clear(true);
        leds->setScene(SceneType::USMC_2025);

        // Show the title
        display->setFont(u8g2_font_lubB10_tf);
        display->showTextCentered("USMC\n250th\nAnniversary");

        // Wait for 3 seconds
        vTaskDelay(3000 / portTICK_PERIOD_MS);

        // Show the main image
        //   NOTE: as a side effect, updateDisplay() will delete this task via stopInitTask()
        updateDisplay();
    }
};

#endif // MODE_HOME_HPP
