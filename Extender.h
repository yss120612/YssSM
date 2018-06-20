// Extender.h

#ifndef _EXTENDER_h
#define _EXTENDER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class PinExtender
{
public:
	PinExtender();
	~PinExtender();

	void setPinMode(int8_t pin, uint8_t mode);

	void setup(uint8_t ST_CP, uint8_t SH_CP, uint8_t DS);

	void setAll(uint16_t bitsToSend);

	void registerWrite(int8_t whichPin, uint8_t whichState);

	boolean getPin(int8_t whichPin);

	uint16_t getAll();

private:
	//Пин подключен к ST_CP входу 74HC595
	uint8_t latchPin;
	//Пин подключен к SH_CP входу 74HC595
	uint8_t clockPin;
	//Пин подключен к DS входу 74HC595
	uint8_t dataPin;

	uint16_t data;

};



#endif

