#pragma once
#include <Adafruit_BME280.h>
#include <etl/singleton.h>
#include "BMEConstants.h"

class BMESPIInterface
{
public:
    BMESPIInterface() : _bme(BMEConstants::BME_CS_PIN) {}

    // Starts the sensor. Returns false if it isn't found (wiring problem).
    bool init();

    // Reads the sensor and stores the result.
    void update();

    float get_temperature() const;
    bool is_connected() const;

private:
    Adafruit_BME280 _bme;       // constructed with a chip-select pin = hardware SPI
    float _temperature_c = 0.0f;
    bool _connected = false;
};

using BMESPIInterfaceInstance = etl::singleton<BMESPIInterface>;