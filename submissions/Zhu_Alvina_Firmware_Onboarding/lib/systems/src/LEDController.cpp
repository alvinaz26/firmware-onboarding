#include "LEDController.h"

void LEDController::init()
{
    pinMode(BMEConstants::LED_PIN, OUTPUT);
    digitalWrite(BMEConstants::LED_PIN, LOW);
}

unsigned long LEDController::compute_interval_ms(float temperature_c) const
{
    // Clamp to the configured range
    if (temperature_c <= BMEConstants::MIN_TEMP_C)
    {
        return BMEConstants::SLOWEST_BLINK_MS;
    }
    if (temperature_c >= BMEConstants::MAX_TEMP_C)
    {
        return BMEConstants::FASTEST_BLINK_MS;
    }

    // Linear interpolation: MIN_TEMP -> slowest, MAX_TEMP -> fastest
    float fraction = (temperature_c - BMEConstants::MIN_TEMP_C)
                   / (BMEConstants::MAX_TEMP_C - BMEConstants::MIN_TEMP_C);
    float span = static_cast<float>(BMEConstants::SLOWEST_BLINK_MS - BMEConstants::FASTEST_BLINK_MS);
    return BMEConstants::SLOWEST_BLINK_MS - static_cast<unsigned long>(fraction * span);
}

void LEDController::set_temperature(float temperature_c)
{
    _interval_ms = compute_interval_ms(temperature_c);
}

void LEDController::update(unsigned long now_ms)
{
    if (now_ms - _last_toggle_ms >= _interval_ms)
    {
        _last_toggle_ms = now_ms;
        _led_on = !_led_on;
        digitalWrite(BMEConstants::LED_PIN, _led_on ? HIGH : LOW);
    }
}

unsigned long LEDController::get_interval_ms() const
{
    return _interval_ms;
}