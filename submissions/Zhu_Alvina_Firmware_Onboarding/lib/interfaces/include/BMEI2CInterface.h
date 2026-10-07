#pragma once
#include <Adafruit_BME280.h>
#include <etl/singleton.h>
#include "BMEConstants.h"

class BMEI2CInterface
{
public:
    BMEI2CInterface() = default;

    // Starts the sensor. Returns false if it isn't found (wiring or address problem).
    bool init();

    // Reads the sensor and stores the result. Call this periodically.
    void update();

    // Last temperature stored by update(), in degrees C.
    float get_temperature() const;

    // True if init() succeeded.
    bool is_connected() const;

private:
    Adafruit_BME280 _bme;       // no-argument constructor = I2C
    float _temperature_c = 0.0f;
    bool _connected = false;
};

using BMEI2CInterfaceInstance = etl::singleton<BMEI2CInterface>;