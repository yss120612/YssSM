// Pump.h

#ifndef _PUMP_h
#define _PUMP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Extender.h"

class Pump
{
public:
	Pump();
	~Pump();
	void setup(uint8_t pin, PinExtender * ex);
	void start();
	void stop();
	boolean isWorking();
private:
	boolean working;
	PinExtender * ext;
	uint8_t pump_pin;
};



#endif

