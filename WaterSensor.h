// WaterSensor.h

#ifndef _WATERSENSOR_h
#define _WATERSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Multiplexor.h"
#include "Extender.h"

class WaterSensor
{
public:
	WaterSensor();
	~WaterSensor();
	void setup(uint8_t sens, uint8_t pwr, Multiplexor * m, PinExtender *p);
	void process(long ms);
	uint16_t getValue();
	void disarm();
	boolean isAlarmed() { return alarm; }
	void arm(uint8_t lim, uint8_t lc = 3);
	void setLimit(int lm);
	int getLimit();
private:
	uint16_t data;
	boolean alarm;
	boolean check_me;
	Multiplexor * mult;
	PinExtender * ext;
	uint8_t sensor_pin;
	uint8_t power_pin;
	int limit;
	uint8_t limit_count;
	uint8_t counter;
};



#endif


