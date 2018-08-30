// 
// 
// 

#include "Multiplexor.h"


Multiplexor::Multiplexor()
{
}

Multiplexor::~Multiplexor()
{
}

void Multiplexor::setup(uint8_t dP, uint8_t A, uint8_t B, uint8_t C, uint8_t D, PinExtender * ex)
{
	dataPin = dP;
	pinA = A;
	pinB = B;
	pinC = C;
	pinD = D;
	ext = ex;
	ext->setPinMode(pinA, OUTPUT);
	ext->setPinMode(pinB, OUTPUT);
	ext->setPinMode(pinC, OUTPUT);
	ext->setPinMode(pinD, OUTPUT);
}

int Multiplexor::anaRead(uint8_t pin)
{
	ext->digWrite(pinA, pin & 0x01);
	ext->digWrite(pinB, pin & 0x02);
	ext->digWrite(pinC, pin & 0x04);
	ext->digWrite(pinD, pin & 0x08);
	return analogRead(dataPin);
}
