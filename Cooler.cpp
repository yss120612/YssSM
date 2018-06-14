#include "Cooler.h"

Cooler::Cooler(Hardware * hr)
{
	hard = hr;
}

Cooler::~Cooler()
{
}

void Cooler::setup( uint8_t pin)
{
	isON = false;
	cooler_pin = pin;
}

void Cooler::run(boolean swc)
{
	hard->getExtender()->registerWrite(cooler_pin, swc);
	isON = swc;
}

void Cooler::process(uint16_t ms) 
{
	if (hard->getTTriak() == NULL) return;
	float tm=hard->getTTriak()->getTemp();
	if (isON) {

	}
	else {

	}
}
