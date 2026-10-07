#include <Arduino.h>
#include "BMEI2CInterface.h"
#include "LEDController.h"
#include "BMEConstants.h"

static unsigned long last_read_ms = 0;

void setup()
{
    Serial.begin(BMEConstants::SERIAL_BAUD);

    // Create the single shared instances
    BMEI2CInterfaceInstance::create();
    LEDControllerInstance::create();

    LEDControllerInstance::instance().init();

    if (!BMEI2CInterfaceInstance::instance().init())
    {
        Serial.println(F("BME280 not found. Check wiring or I2C address."));
        // Keep running: the LED stays at the slowest blink so you can see the board is alive.
    }
}

void loop()
{
    unsigned long now = millis();

    // Read the sensor on a fixed schedule (not every loop pass)
    if (now - last_read_ms >= BMEConstants::SENSOR_READ_INTERVAL_MS)
    {
        last_read_ms = now;

        BMEI2CInterfaceInstance::instance().update();

        if (BMEI2CInterfaceInstance::instance().is_connected())
        {
            // Data flow: interface -> main -> system
            float temp_c = BMEI2CInterfaceInstance::instance().get_temperature();
            LEDControllerInstance::instance().set_temperature(temp_c);

            Serial.print(F("Temp: "));
            Serial.print(temp_c);
            Serial.print(F(" C, blink interval: "));
            Serial.print(LEDControllerInstance::instance().get_interval_ms());
            Serial.println(F(" ms"));
        }
    }

    // Runs every pass so the blink timing stays accurate
    LEDControllerInstance::instance().update(now);
}