#include "Scene.h"
#include "led/LedHandler.h"

#include "esp_log.h"
#include "esp_task_wdt.h"
#include "Rank.h"

static const char *TAG = "Scene";

Scene::Scene(const SceneConfigMapAddressable &addressableConfig,
             const SceneConfigNonAddr &nonAddrConfig)
    : leds(LedHandler::getInstance())
    , addressableConfig(addressableConfig)
    , nonAddrConfig(nonAddrConfig) {
    for (auto &config : addressableConfig) {
        lastUpdateTime[config.first] = 0;
    }
    lastUpdateTimeNonAddr = 0;
}

void Scene::tick() {
    unsigned long currentTime = millis();

    // Update addressable LED strips
    for (auto &entry : addressableConfig) {
        auto strip   = entry.first;
        auto &config = entry.second;

        if (currentTime - lastUpdateTime[strip] >= config.interval) {
            switch (config.pattern) {
                case ScenePattern::PALETTE_FILL:
                    updateLedsWithPalette(strip, config.colorConfig.palette, config.startIndex,
                                          config.brightness);
                    config.startIndex++;
                    break;
                case ScenePattern::COLOR_CYCLE:
                    updateLedsCycleColorNext(strip, config.colorConfig.color, config.startIndex,
                                             config.brightness);
                    break;
            }
            lastUpdateTime[strip] = currentTime;
        }
    }

    // Update non-addressable LEDs
    if (currentTime - lastUpdateTimeNonAddr >= nonAddrConfig.interval) {
        switch (nonAddrConfig.pattern) {
            case ScenePatternNonAddr::RANDOM: updateNonAddressableLedRandom(); break;
        }
        lastUpdateTimeNonAddr = currentTime;
    }
}

void Scene::updateLedsWithPalette(AddressableStrip strip, const CRGBPalette16 &palette,
                                  uint8_t startIndex, uint8_t brightness) {
    for (int i = 0; i < LedCounts[strip]; i++) {

        
        //ESP_LOGD(TAG, "The current led value is: %d", i);

        if(displayRankLED == i && strip == 0){
            //ESP_LOGD(TAG, "The strip value is: %d", strip, i);
            leds.setAddressable(strip, i, CRGB::Red);
        }else{
            uint8_t colorIndex = startIndex + (i * 255 / LedCounts[strip]);
            leds.setAddressable(strip, i, ColorFromPalette(palette, colorIndex, brightness));
        }
        
    }
    leds.show();
}

void Scene::updateLedsCycleColorNext(AddressableStrip strip, const CRGB &color, uint8_t startIndex,
                                     uint8_t brightness) {
    static int currentLed = 0;
    leds.setAddressable(strip, currentLed, CRGB::Black);
    currentLed = (currentLed + 1) % LedCounts[strip];
    leds.setAddressable(strip, currentLed, color);
    leds.show();
}

void Scene::updateNonAddressableLedRandom() {
    int led = random(0, NON_ADDRESSABLE_LED_COUNT);
    //ESP_LOGD(TAG, "The i value is: %d", NON_ADDRESSABLE_LED_COUNT);
    for (int i = 0; i < NON_ADDRESSABLE_LED_COUNT; i++) {
        leds.setNonAddressable(static_cast<NonAddressableLed>(i), i == led);
    }
}
