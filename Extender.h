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

	void setup(uint8_t addr = 0x20);

	void setAB(uint8_t bitsToSend, uint8_t ab);

	uint8_t getAB(uint8_t ab);

	uint8_t readRegister(uint8_t addr);

	void writeRegister(uint8_t regAddr, uint8_t regValue);

	void setAll(uint16_t bitsToSend);

	void registerWrite(int8_t whichPin, uint8_t whichState);

	boolean getPin(int8_t whichPin);

	uint16_t getAll();

private:
	//��� ��������� � ST_CP ����� 74HC595
	uint8_t latchPin;
	//��� ��������� � SH_CP ����� 74HC595
	uint8_t clockPin;
	//��� ��������� � DS ����� 74HC595
	uint8_t dataPin;

	uint8_t _address;

	uint16_t data;

	uint8_t dataA;

	uint8_t dataB;

};



#endif

