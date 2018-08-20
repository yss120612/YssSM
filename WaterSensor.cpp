// 
// 
// 

#include "WaterSensor.h"


WaterSensor::WaterSensor()
{
	
}

WaterSensor::~WaterSensor()
{

}

void WaterSensor::setup(uint8_t sens, uint8_t pwr) {
	sensor_pin = sens;
	power_pin = pwr;

}



void WaterSensor::process(long ms)
{
}

void WaterSensor::arm()
{
	alarm = false;
}
