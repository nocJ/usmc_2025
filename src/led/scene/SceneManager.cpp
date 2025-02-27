#include "SceneManager.h"
#include "ScenePalettes.h"

static const char *TAG = "SceneManager";

void SceneManager::init() {
    if (initialized) {
        return;
    }

    //
    // Create all scenes here
    //

    // clang-format off
   scenes[SceneType::RED_WHITE_BLUE] = std::make_unique<Scene>(
        SceneConfigMapAddressable{
            {AddressableStrip::UPPER, SceneConfigAddressable(red_white_blue_p, 0, UPPER_LED_BASE_BRIGHTNESS, 5, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::LOWER, SceneConfigAddressable(red_white_blue_p, 0, LOWER_LED_BASE_BRIGHTNESS, 5, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::MAIN,  SceneConfigAddressable(red_white_blue_main_p, 0, MAIN_LED_BASE_BRIGHTNESS, 5, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::TOUCH, SceneConfigAddressable(CRGB::DarkOrange, 0, TOUCH_LED_BASE_BRIGHTNESS, 150, ScenePattern::COLOR_CYCLE)},
        },
        SceneConfigNonAddr{250, ScenePatternNonAddr::RANDOM}
    );
    scenes[SceneType::CELESTIAL_CLOUDS] = std::make_unique<Scene>(
        SceneConfigMapAddressable{
            {AddressableStrip::UPPER, SceneConfigAddressable(celestial_clouds_p, 0, UPPER_LED_BASE_BRIGHTNESS, 20, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::LOWER, SceneConfigAddressable(celestial_clouds_p, 0, LOWER_LED_BASE_BRIGHTNESS, 20, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::MAIN,  SceneConfigAddressable(celestial_clouds_main_p, 0, MAIN_LED_BASE_BRIGHTNESS, 20, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::TOUCH, SceneConfigAddressable(CRGB::SkyBlue, 0, TOUCH_LED_BASE_BRIGHTNESS, 275, ScenePattern::COLOR_CYCLE)},
        },
        SceneConfigNonAddr{250, ScenePatternNonAddr::RANDOM}
    );
    scenes[SceneType::GONE_TO_HELL] = std::make_unique<Scene>(
        SceneConfigMapAddressable{
            {AddressableStrip::UPPER, SceneConfigAddressable(gone_to_hell_p, 0, UPPER_LED_BASE_BRIGHTNESS, 5, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::LOWER, SceneConfigAddressable(gone_to_hell_p, 0, LOWER_LED_BASE_BRIGHTNESS, 5, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::MAIN,  SceneConfigAddressable(gone_to_hell_main_p, 0, MAIN_LED_BASE_BRIGHTNESS, 5, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::TOUCH, SceneConfigAddressable(CRGB::Red, 0, TOUCH_LED_BASE_BRIGHTNESS, 150, ScenePattern::COLOR_CYCLE)},
        },
        SceneConfigNonAddr{250, ScenePatternNonAddr::RANDOM}
    );
    scenes[SceneType::SECRET_COMBINATIONS] = std::make_unique<Scene>(
        SceneConfigMapAddressable{
            {AddressableStrip::UPPER, SceneConfigAddressable(secret_combinations_p, 0, UPPER_LED_BASE_BRIGHTNESS, 5, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::LOWER, SceneConfigAddressable(secret_combinations_p, 0, LOWER_LED_BASE_BRIGHTNESS, 5, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::MAIN,  SceneConfigAddressable(secret_combinations_main_p, 0, MAIN_LED_BASE_BRIGHTNESS, 5, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::TOUCH, SceneConfigAddressable(CRGB::Red, 0, TOUCH_LED_BASE_BRIGHTNESS, 150, ScenePattern::COLOR_CYCLE)},
        },
        SceneConfigNonAddr{250, ScenePatternNonAddr::RANDOM}
    );
    scenes[SceneType::THE_SALAMANDER] = std::make_unique<Scene>(
        SceneConfigMapAddressable{
            {AddressableStrip::UPPER, SceneConfigAddressable(the_salamander_p, 0, UPPER_LED_BASE_BRIGHTNESS, 20, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::LOWER, SceneConfigAddressable(the_salamander_p, 0, LOWER_LED_BASE_BRIGHTNESS, 20, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::MAIN,  SceneConfigAddressable(the_salamander_main_p, 0, MAIN_LED_BASE_BRIGHTNESS, 10, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::TOUCH, SceneConfigAddressable(CRGB::Green, 0, TOUCH_LED_BASE_BRIGHTNESS, 200, ScenePattern::COLOR_CYCLE)},
        },
        SceneConfigNonAddr{250, ScenePatternNonAddr::RANDOM}
    );
   
    scenes[SceneType::TAPIR_JOYRIDE] = std::make_unique<Scene>(
        SceneConfigMapAddressable{
            {AddressableStrip::UPPER, SceneConfigAddressable(tapir_joyride_p, 0, UPPER_LED_BASE_BRIGHTNESS, 15, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::LOWER, SceneConfigAddressable(tapir_joyride_p, 0, LOWER_LED_BASE_BRIGHTNESS, 15, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::MAIN,  SceneConfigAddressable(tapir_joyride_main_p, 0, MAIN_LED_BASE_BRIGHTNESS, 10, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::TOUCH, SceneConfigAddressable(CRGB::Orange, 0, TOUCH_LED_BASE_BRIGHTNESS, 250, ScenePattern::COLOR_CYCLE)},
        },
        SceneConfigNonAddr{250, ScenePatternNonAddr::RANDOM}
    );

    scenes[SceneType::SUPPRESSIVE_BADGE] = std::make_unique<Scene>(
        SceneConfigMapAddressable{
            {AddressableStrip::UPPER, SceneConfigAddressable(suppressive_badge_p, 0, UPPER_LED_BASE_BRIGHTNESS, 5, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::LOWER, SceneConfigAddressable(suppressive_badge_p, 0, LOWER_LED_BASE_BRIGHTNESS, 5, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::MAIN,  SceneConfigAddressable(suppressive_badge_main_p, 0, MAIN_LED_BASE_BRIGHTNESS, 5, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::TOUCH, SceneConfigAddressable(CRGB::Gold, 0, TOUCH_LED_BASE_BRIGHTNESS, 150, ScenePattern::COLOR_CYCLE)},
        },
        SceneConfigNonAddr{250, ScenePatternNonAddr::RANDOM}
    );

    scenes[SceneType::CRAZY] = std::make_unique<Scene>(
        SceneConfigMapAddressable{
            {AddressableStrip::UPPER, SceneConfigAddressable(crazy_p, 0, UPPER_LED_BASE_BRIGHTNESS, 8, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::LOWER, SceneConfigAddressable(crazy_p, 0, LOWER_LED_BASE_BRIGHTNESS, 8, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::MAIN,  SceneConfigAddressable(crazy_main_p, 0, MAIN_LED_BASE_BRIGHTNESS, 8, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::TOUCH, SceneConfigAddressable(CRGB::Red, 0, TOUCH_LED_BASE_BRIGHTNESS, 200, ScenePattern::COLOR_CYCLE)},
        },
        SceneConfigNonAddr{250, ScenePatternNonAddr::RANDOM}
    );

    scenes[SceneType::THETAN_POSSESSION] = std::make_unique<Scene>(
        SceneConfigMapAddressable{
            {AddressableStrip::UPPER, SceneConfigAddressable(thetan_possession_p, 0, UPPER_LED_BASE_BRIGHTNESS, 5, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::LOWER, SceneConfigAddressable(thetan_possession_p, 0, LOWER_LED_BASE_BRIGHTNESS, 5, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::MAIN,  SceneConfigAddressable(thetan_possession_main_p, 0, MAIN_LED_BASE_BRIGHTNESS, 15, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::TOUCH, SceneConfigAddressable(CRGB::Red, 0, TOUCH_LED_BASE_BRIGHTNESS, 200, ScenePattern::COLOR_CYCLE)},
        },
        SceneConfigNonAddr{250, ScenePatternNonAddr::RANDOM}
    );

    scenes[SceneType::DRUNK_AS_HELL] = std::make_unique<Scene>(
        SceneConfigMapAddressable{
            {AddressableStrip::UPPER, SceneConfigAddressable(drunk_as_hell_p, 0, UPPER_LED_BASE_BRIGHTNESS, 2, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::LOWER, SceneConfigAddressable(drunk_as_hell_p, 0, LOWER_LED_BASE_BRIGHTNESS, 2, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::MAIN,  SceneConfigAddressable(drunk_as_hell_main_p, 0, MAIN_LED_BASE_BRIGHTNESS, 2, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::TOUCH, SceneConfigAddressable(CRGB::Orange, 0, TOUCH_LED_BASE_BRIGHTNESS, 75, ScenePattern::COLOR_CYCLE)},
        },
        SceneConfigNonAddr{250, ScenePatternNonAddr::RANDOM}
    );

     scenes[SceneType::GONE_CLEAR] = std::make_unique<Scene>(
        SceneConfigMapAddressable{
            {AddressableStrip::UPPER, SceneConfigAddressable(gone_clear_p, 0, UPPER_LED_BASE_BRIGHTNESS, 10, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::LOWER, SceneConfigAddressable(gone_clear_p, 0, LOWER_LED_BASE_BRIGHTNESS, 10, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::MAIN,  SceneConfigAddressable(gone_clear_main_p, 0, MAIN_LED_BASE_BRIGHTNESS, 10, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::TOUCH, SceneConfigAddressable(CRGB::WhiteSmoke, 0, TOUCH_LED_BASE_BRIGHTNESS, 200, ScenePattern::COLOR_CYCLE)},
        },
        SceneConfigNonAddr{250, ScenePatternNonAddr::RANDOM}

    );

    scenes[SceneType::AMERICAN] = std::make_unique<Scene>(
        SceneConfigMapAddressable{
            {AddressableStrip::UPPER, SceneConfigAddressable(american_p, 0, UPPER_LED_BASE_BRIGHTNESS, 10, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::LOWER, SceneConfigAddressable(american_p, 0, LOWER_LED_BASE_BRIGHTNESS, 10, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::MAIN,  SceneConfigAddressable(american_main_p, 0, MAIN_LED_BASE_BRIGHTNESS, 10, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::TOUCH, SceneConfigAddressable(CRGB::Red, 0, TOUCH_LED_BASE_BRIGHTNESS, 100, ScenePattern::COLOR_CYCLE)},
        },
        SceneConfigNonAddr{250, ScenePatternNonAddr::RANDOM}

    );
    
    scenes[SceneType::USMC_2025] = std::make_unique<Scene>(
        SceneConfigMapAddressable{
            {AddressableStrip::UPPER, SceneConfigAddressable(usmc_p, 0, UPPER_LED_BASE_BRIGHTNESS, 10, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::LOWER, SceneConfigAddressable(usmc_p, 0, LOWER_LED_BASE_BRIGHTNESS, 10, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::MAIN,  SceneConfigAddressable(usmc_main_p, 0, MAIN_LED_BASE_BRIGHTNESS, 10, ScenePattern::PALETTE_FILL)},
            {AddressableStrip::TOUCH, SceneConfigAddressable(CRGB::Teal, 0, TOUCH_LED_BASE_BRIGHTNESS, 200, ScenePattern::COLOR_CYCLE)},
        },
        SceneConfigNonAddr{250, ScenePatternNonAddr::RANDOM}
    );
    // clang-format on

    // Create the scene task
    xTaskCreate(sceneTask, "SceneTask", 2048, this, 5, NULL);

    initialized = true;
}

void SceneManager::setScene(SceneType scene) {
    ESP_LOGD(TAG, "Switching to scene %d", static_cast<int>(scene));
    std::lock_guard<std::mutex> lock(sceneMutex);
    currentScene = scenes[scene].get();
}

void SceneManager::sceneTask(void *pvParameters) {
    SceneManager *self = static_cast<SceneManager *>(pvParameters);

    while (true) {
        std::lock_guard<std::mutex> lock(self->sceneMutex);
        if (self->currentScene) {
            self->currentScene->tick();
        }
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}
