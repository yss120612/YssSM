#include "Cooler.h"

Cooler::Cooler()
{
	
}

Cooler::~Cooler()
{
}


void Cooler::setup(Hardware * h,uint8_t pin)
{
	isON = false;
	hard = h;
	cooler_pin = pin;
}

void Cooler::run(boolean swc)
{
	hard->getExtender()->registerWrite(cooler_pin, swc);
	isON = swc;
}


void Cooler::setParams(float t1, float gis)
{
	borderT = t1;
	gesteresis = gis;
}


void Cooler::process(long ms) 
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
