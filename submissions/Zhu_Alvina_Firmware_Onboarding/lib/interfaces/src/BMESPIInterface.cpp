#include "BMESPIInterface.h"

bool BMESPIInterface::init()
{
    _connected = _bme.begin();
    return _connected;
}

void BMESPIInterface::update()
{
    if (!_connected)
    {
        return;
    }
    _temperature_c = _bme.readTemperature();
}

float BMESPIInterface::get_temperature() const
{
    return _temperature_c;
}

bool BMESPIInterface::is_connected() const
{
    return _connected;
}