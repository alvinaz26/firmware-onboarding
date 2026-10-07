#include <Arduino.h>
#include "BMESPIInterface.h"
#include "LEDController.h"
#include "BMEConstants.h"

static unsigned long last_read_ms = 0;

void setup()
{
    Serial.begin(BMEConstants::SERIAL_BAUD);

    BMESPIInterfaceInstance::create();
    LEDControllerInstance::create();

    LEDControllerInstance::instance().init();

    if (!BMESPIInterfaceInstance::instance().init())
    {
        Serial.println(F("BME280 not found. Check SPI wiring and chip-select pin."));
    }
}

void loop()
{
    unsigned long now = millis();

    if (now - last_read_ms >= BMEConstants::SENSOR_READ_INTERVAL_MS)
    {
        last_read_ms = now;

        BMESPIInterfaceInstance::instance().update();

        if (BMESPIInterfaceInstance::instance().is_connected())
        {
            float temp_c = BMESPIInterfaceInstance::instance().get_temperature();
            LEDControllerInstance::instance().set_temperature(temp_c);

            Serial.print(F("Temp: "));
            Serial.print(temp_c);
            Serial.print(F(" C, blink interval: "));
            Serial.print(LEDControllerInstance::instance().get_interval_ms());
            Serial.println(F(" ms"));
        }
    }

    LEDControllerInstance::instance().update(now);
}