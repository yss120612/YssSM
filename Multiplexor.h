// Multiplexor.h

#ifndef _MULTIPLEXOR_h
#define _MULTIPLEXOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Extender.h"

class Multiplexor
{
public:
	Multiplexor();
	~Multiplexor();
	void setup(uint8_t dP, uint8_t A, uint8_t B, uint8_t C, uint8_t D, PinExtender * ex);
	int anaRead(uint8_t);
private:
	uint8_t pinA, pinB, pinC, pinD, dataPin;
	PinExtender * ext;
};



#endif

