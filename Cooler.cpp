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
	hard->getExtender()->digWrite(cooler_pin, swc);
	isON = swc;
}


//void Cooler::setParams(int t1, int8_t gis)
//{
//	borderT = t1;
//	gesteresis = gis;
//}


void Cooler::process(long ms) 
{
	if (hard->getTTriak() == NULL) return;
	int tm=hard->getTTriak()->getTemp();
	if (isON) {
		if (tm < CONF.getTriakCoolerTemp() - CONF.getTriakCoolerGist())
		{
			run(false);
		}
	}
	else {
		if (tm > CONF.getTriakCoolerTemp())
		{
			run(true);
		}
	}
}
