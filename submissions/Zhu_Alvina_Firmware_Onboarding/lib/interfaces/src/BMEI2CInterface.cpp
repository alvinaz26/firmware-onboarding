#include "BMEI2CInterface.h"

bool BMEI2CInterface::init()
{
    _connected = _bme.begin(BMEConstants::BME_I2C_ADDRESS);
    return _connected;
}

void BMEI2CInterface::update()
{
    if (!_connected)
    {
        return;
    }
    _temperature_c = _bme.readTemperature();
}

float BMEI2CInterface::get_temperature() const
{
    return _temperature_c;
}

bool BMEI2CInterface::is_connected() const
{
    return _connected;
}