#pragma once
#include <Arduino.h>
#include <etl/singleton.h>
#include "BMEConstants.h"

class LEDController
{
public:
    LEDController() = default;

    // Sets up the LED pin as an output.
    void init();

    // Feed in the latest temperature (degrees C). Updates the blink interval.
    void set_temperature(float temperature_c);

    // Call every loop. Toggles the LED when the blink interval has elapsed.
    void update(unsigned long now_ms);

    // Maps a temperature to a blink interval in ms. Hotter = shorter interval.
    unsigned long compute_interval_ms(float temperature_c) const;

    unsigned long get_interval_ms() const;

private:
    unsigned long _interval_ms = BMEConstants::SLOWEST_BLINK_MS;
    unsigned long _last_toggle_ms = 0;
    bool _led_on = false;
};

using LEDControllerInstance = etl::singleton<LEDController>;