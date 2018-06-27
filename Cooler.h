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
	Cooler();
	~Cooler();
	void setup(Hardware * h,uint8_t pin);
	void run(boolean swc);
	void setParams(float t1, float gis);
	float getTemperature() { return borderT; }
	float getGesteresis() { return gesteresis; }
	void process(long ms);
private:
	float borderT;
	float gesteresis;
	uint8_t cooler_pin;
	Hardware * hard;
	boolean isON;
};
#endif

