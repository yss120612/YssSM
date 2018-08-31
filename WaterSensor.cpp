
#include "WaterSensor.h"


WaterSensor::WaterSensor()
{
	
}

WaterSensor::~WaterSensor()
{

}

void WaterSensor::setup(uint8_t sens, uint8_t pwr, Multiplexor *m, PinExtender *p) {
	sensor_pin = sens;
	power_pin = pwr;
	mult = m;
	ext = p;
	ext->setPinMode(power_pin, OUTPUT);
	ext->digWrite(power_pin, LOW);
}


void WaterSensor::process(long ms)
{
	if (alarm) return;
	if (mult->anaRead(sensor_pin)<limit) {
		counter--;
		if (counter == 0)
		{
			ext->digWrite(power_pin, LOW);
			alarm = true;
		}
	}
	else {
		counter = limit_count;
	}
}




void WaterSensor::arm(uint8_t lc)
{
	ext->digWrite(power_pin, HIGH);
	alarm = false;
	limit_count = lc;
	counter = limit_count;
}

void WaterSensor::setLimit(int lm)
{
	limit = lm;
	
}

int WaterSensor::getLimit()
{
	return limit;
}
