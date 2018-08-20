// WaterSensor.h

#ifndef _WATERSENSOR_h
#define _WATERSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class WaterSensor
{
public:
	WaterSensor();
	~WaterSensor();
	void setup(uint8_t sens, uint8_t pwr);
	void process(long ms);
	boolean isAlarmed() { return alarm; }
	void arm();
private:
	boolean alarm;
	uint8_t sensor_pin;
	uint8_t power_pin;
};



#endif

