// Beeper.h

#ifndef _BEEPER_h
#define _BEEPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Beeper
{
public:
	Beeper();
	void setup(uint8_t pin);
	void beep(uint16_t freq = 1000, uint16_t dur = 1000);
	void process();
	void stop();
	boolean isOn() { return is_on; }
private:
	uint8_t beeper_pin;
	long tone_time;
	boolean is_on;
};


extern ICACHE_RAM_ATTR void t1IntHandler();

#endif

