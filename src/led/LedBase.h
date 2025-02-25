#ifndef LED_BASE_H
#define LED_BASE_H

#ifndef FASTLED_INTERNAL
    #define FASTLED_INTERNAL // Disable pragma message
#endif

#include <unordered_map>
#include "FastLED.h"
#include "config.h"

/**
 * @brief Addressable LED strips
 */
enum AddressableStrip {
    UPPER, // Upper PCB LEDs
    LOWER, // Lower PCB LEDs
    MAIN,  // Main PCB ring
    TOUCH, // Touch button LEDs
};
#define ADDRESSABLE_STRIP_COUNT 4
const uint8_t LedCounts[ADDRESSABLE_STRIP_COUNT] = {
    UPPER_LED_COUNT,
    LOWER_LED_COUNT,
    MAIN_LED_COUNT,
    TOUCH_LED_COUNT,
};

/**
 * @brief Non-addressable LEDs
 */
enum NonAddressableLed {
    LED_A, // LED A
    LED_B, // LED B
    LED_C, // LED C
    LED_D, // LED D
};
#define NON_ADDRESSABLE_LED_COUNT 4

/**
 * @brief Addressable LED strip type alias
 */
using AddressableStrips = std::unordered_map<AddressableStrip, CPixelView<CRGB> *>;

/**
 * @brief Non-addressable LED type alias
 */
using NonAddressableLeds = std::unordered_map<NonAddressableLed, uint8_t>;

#endif // LED_BASE_H