
#include "WaterSensor.h"
#include "Log.h"

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
	//logg.logging(String(mult->anaRead(sensor_pin)));
	if (alarm) return;
	if (mult->anaRead(sensor_pin)>limit) {
		counter--;
		logg.logging("Warning sensor alarm " +String(mult->anaRead(sensor_pin)));
		if (counter == 0)
		{
			logg.logging("Water sensor triggered " + String(mult->anaRead(sensor_pin)));
			ext->digWrite(power_pin, LOW);
			alarm = true;
		}
	}
	else {
		counter = limit_count;
	}
}




void WaterSensor::arm(uint8_t lim, uint8_t lc)
{
	ext->digWrite(power_pin, HIGH);
	alarm = false;
	limit_count = lc;
	counter = limit_count;
	limit = lim;
}

void WaterSensor::setLimit(int lm)
{
	limit = lm;
	
}

int WaterSensor::getLimit()
{
	return limit;
}
