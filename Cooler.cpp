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


void Cooler::setTemperature(float t1, float gis)
{
	borderT = t1;
	gesteresis = gis;
}


void Cooler::process(uint16_t ms) 
{
	if (hard->getTTriak() == NULL) return;
	float tm=hard->getTTriak()->getTemp();
	if (isON) {
		if (tm < borderT - gesteresis)
		{
			run(false);
		}
	}
	else {
		if (tm > borderT)
		{
			run(true);
		}
	}
}
