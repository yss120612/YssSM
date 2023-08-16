// Extender.h

#ifndef _EXTENDER_h
#define _EXTENDER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

const uint8_t IODIRA = 0x00;
const uint8_t IODIRB = 0x01;
const uint8_t GPIOA = 0x12;
const uint8_t GPIOB = 0x13;
const uint8_t GPPUA = 0x0C;
const uint8_t GPPUB = 0x0D;
const uint8_t OLATA = 0x14;
const uint8_t OLATB = 0x15;


class PinExtender
{
public:
	PinExtender();

	~PinExtender();

	//void setPinMode(int8_t pin, uint8_t mode);

	//void setup(uint8_t ST_CP, uint8_t SH_CP, uint8_t DS);

	void setup(uint8_t addr = 0x20);

	//void setAB(uint8_t bitsToSend, uint8_t ab);

	//uint8_t getAB(uint8_t ab);

	uint8_t readRegister(uint8_t addr);

	void writeRegister(uint8_t regAddr, uint8_t regValue);

	void updateRegisterBit(uint8_t pin, uint8_t pValue, uint8_t portAaddr, uint8_t portBaddr);

	void pullUp(uint8_t p, uint8_t d);

	uint8_t digRead(uint8_t pin);

	void setPinMode(uint8_t p, uint8_t state);

	void digWrite(uint8_t p, uint8_t d);

	//void setAll(uint16_t bitsToSend);

	//void registerWrite(int8_t whichPin, uint8_t whichState);

	//boolean getPin(int8_t whichPin);

	//uint16_t getAll();

private:
	//Пин подключен к ST_CP входу 74HC595
	//uint8_t latchPin;
	//Пин подключен к SH_CP входу 74HC595
	//uint8_t clockPin;
	//Пин подключен к DS входу 74HC595
	//uint8_t dataPin;

	uint8_t _address;

	//uint16_t data;

	//uint8_t dataA;

	//uint8_t dataB;

};



#endif

