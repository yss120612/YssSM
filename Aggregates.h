// Aggregates.h
//Составное из компонентов hardware железо
#ifndef _AGGREGATES_h
#define _AGGREGATES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Heater.h"
#include "Cooler.h"
#include "Kran.h"


class Aggregates
{
public:
	Aggregates(Hardware * ha);
	~Aggregates();
	void init();
	void timed_process(long ms);
	void process(long ms);
	/*void setTCooler(Cooler * t) { cool = t; }
	void setHeater(Heater * h) { heater = h; }
	void setKran(Kran * cr) { kran = cr; }*/

	Cooler * getTCooler() { return & cool; }
	Heater * getHeater() { return & heater; }
	Kran * getKran() { return & kran; }
	Hardware * getHardware() { return hard; }
private:
	Hardware * hard;
	Cooler cool;
	Heater heater;
	Kran kran;
};




#endif

