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
	//void setParams(int t1, int8_t gis);
	//int getTemperature() { return borderT; }
	//uint8_t getGesteresis() { return gesteresis; }
	void process(long ms);
private:
	//int borderT;
	//int8_t gesteresis;
	uint8_t cooler_pin;
	Hardware * hard;
	boolean isON;
};
#endif

