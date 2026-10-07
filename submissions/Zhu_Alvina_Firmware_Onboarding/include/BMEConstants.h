#pragma once
#include <Arduino.h>

namespace BMEConstants
{
    // Serial
    constexpr unsigned long SERIAL_BAUD = 115200;   // matches monitor_speed in platformio.ini

    // I2C
    constexpr uint8_t BME_I2C_ADDRESS = 0x76;       // try 0x77 if the sensor isn't found

    // SPI
    constexpr uint8_t BME_CS_PIN = 10;              // chip-select pin

    // LED
    constexpr uint8_t LED_PIN = 7;

    // Temperature range that maps to blink speed (degrees C)
    constexpr float MIN_TEMP_C = 20.0f;             // at or below this: slowest blink
    constexpr float MAX_TEMP_C = 35.0f;             // at or above this: fastest blink

    // Blink intervals (milliseconds)
    constexpr unsigned long SLOWEST_BLINK_MS = 1000;
    constexpr unsigned long FASTEST_BLINK_MS = 100;

    // How often to read the sensor (milliseconds)
    constexpr unsigned long SENSOR_READ_INTERVAL_MS = 500;
}