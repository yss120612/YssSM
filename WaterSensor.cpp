
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
	check_me = false;
}


void WaterSensor::process(long ms)
{
	if (!check_me) return;
	data = mult->anaRead(sensor_pin);
	if (data>limit) {
		counter--;
		logg.logging("Warning sensor alarm " +String(data));
		if (counter == 0)
		{
			logg.logging("Water sensor triggered " + String(data));
			ext->digWrite(power_pin, LOW);
			alarm = true;
			check_me = false;
		}
	}
	else {
		counter = limit_count;
	}
}

uint16_t WaterSensor::getValue()
{
	return data;
}

void WaterSensor::disarm()
{
	ext->digWrite(power_pin, LOW);
	alarm = false;
	check_me = false;
	counter = 0;
	data = 0;
}

void WaterSensor::arm(uint8_t lim, uint8_t lc)
{
	ext->digWrite(power_pin, HIGH);
	alarm = false;
	check_me = true;
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
