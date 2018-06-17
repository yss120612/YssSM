// Cooler.h

#ifndef _COOLER_h
#define _COOLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Hardware.h"

class Cooler
{
public:
	Cooler(Hardware * hr);
	~Cooler();
	void setup(uint8_t pin);
	void run(boolean swc);
	void setTemperature(float t1, float gis);
	void process(uint16_t ms);
private:
	float borderT;
	float gesteresis;
	uint8_t cooler_pin;
	Hardware * hard;
	boolean isON;
};
#endif

