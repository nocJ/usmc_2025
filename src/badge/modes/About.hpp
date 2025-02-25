#ifndef MODE_ABOUT_HPP
#define MODE_ABOUT_HPP

#include "badge/BadgeMode.h"
#include "badge/BadgeManager.h"
#include "version.h"

static const char *TAG_ABOUTMODE = "AboutMode";

class AboutMode : public BadgeMode {
  public:
    AboutMode() : BadgeMode(ModeType::ABOUT) {
    }

    void enter() override {
        ESP_LOGD(TAG_ABOUTMODE, "Entering About mode");
        
        leds->lockNonAddressable(LED_A, true);
        leds->lockNonAddressable(LED_B, true);
        leds->lockNonAddressable(LED_C, true);
        
        std::string aboutText = "Created by\n Josiah Jacobberger\nv" + std::string(VERSION_STRING);
        display->clear();
        display->setFont(u8g2_font_ncenB08_tr);
        display->showTextCentered(aboutText.c_str());
    }

    void leave() override {
        ESP_LOGD(TAG_ABOUTMODE, "Exiting About mode");

        leds->unlockNonAddressable(LED_A);
        leds->unlockNonAddressable(LED_B);
        leds->unlockNonAddressable(LED_C);

        display->clear();
    }

  protected:
    void receiveTouch(TouchEvent event) override {
        if (event.pin == HANDSHAKE_1 && event.type == TOUCH_DOWN) {
            Badge::getInstance().setMode(ModeType::HOME);
        }
    }
};

#endif // MODE_ABOUT_HPP