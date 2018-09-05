// 
// 
// 

#include "Pump.h"

Pump::Pump()
{
}

Pump::~Pump()
{
}

void Pump::setup(uint8_t pin, PinExtender * ex)
{
	ext = ex;
	pump_pin = pin;
	working = false;
	ext->setPinMode(pump_pin, OUTPUT);
	ext->digWrite(pump_pin, LOW);
}

void Pump::start()
{
	ext->digWrite(pump_pin, HIGH);
	working = true;
}

void Pump::stop()
{
	ext->digWrite(pump_pin, LOW);
	working = false;
}

boolean Pump::isWorking()
{
	return working;
}


