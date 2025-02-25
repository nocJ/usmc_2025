#ifndef BADGE_MODE_H
#define BADGE_MODE_H

#include <unordered_map>
#include "display/DisplayManager.h"
#include "led/LedHandler.h"
#include "touch/TouchHandler.h"

#define PROMPT_FONT          u8g2_font_ncenB08_tr

// List of modes
enum class ModeType {
    HOME,
    LED_MODES,
    DISPLAY_RANK,
    DISPLAY_HANDLE,
    ABOUT,
};


class BadgeMode {
  public:
    friend class Badge;

    BadgeMode(DisplayManager *display, LedHandler *leds, TouchHandler *touch, ModeType type)
        : display(display)
        , leds(leds)
        , touch(touch)
        , type(type)
        , inputStates(touch->getInputStates())
        , latestEvents(touch->getLatestEvents())
        , allPins(handshakePins.right.keys()) {};
    BadgeMode(ModeType type)
        : BadgeMode(&DisplayManager::getInstance(), &LedHandler::getInstance(), &TouchHandler::getInstance(), type) {};
    virtual ~BadgeMode() {};
    ModeType getType() {
        return type;
    }
    virtual const char *getBaseType() const {
        return "BadgeMode";
    }

  protected:
    DisplayManager *display;
    LedHandler *leds;
    TouchHandler *touch;
    ModeType type;

    // Touch event handling
    TouchEvent (&latestEvents)[HANDSHAKE_COUNT];
    TouchEventType (&inputStates)[HANDSHAKE_COUNT];
    void handleTouch(TouchEvent event);

    virtual void enter() = 0;
    virtual void leave() = 0;

    // Touch event
    virtual void receiveTouch(TouchEvent event) {};

  private:
    std::set<int> allPins;

};

// Menu items
extern const std::unordered_map<ModeType, const char *> ModeTitle;

#endif // BADGE_MODE_H
