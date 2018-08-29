
#include "Extender.h"
#include "Log.h"
#include <Wire.h>

PinExtender::PinExtender()
{
}

PinExtender::~PinExtender()
{
}

void PinExtender::setPinMode(int8_t pin, uint8_t mode)
{
	if (pin<0 || pin >= 100) return;
	pinMode(pin, mode);
	
}

void PinExtender::setup(uint8_t ST_CP, uint8_t SH_CP, uint8_t DS)
{
	latchPin = ST_CP;
	clockPin = SH_CP;
	dataPin = DS;
	pinMode(latchPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	setAll(0);
}

void PinExtender::setup(uint8_t addr)
{
	_address = addr;
	Wire.beginTransmission(_address);  // i2c � ����� (A0-0,A1-0,A2-0)
	Wire.write(0x00); // IODIRA register
	Wire.write(0x00); // ��������� PORT A ��� output //bit 0-output 1-input
	Wire.write(0x10); // IODIRB register
	Wire.write(0x00); // ��������� PORT A ��� output 
	Wire.endTransmission();
}

/**
 * new
 */

void PinExtender::setAB(uint8_t bitsToSend,uint8_t ab) {//ab=0-A< ab=1-B
	Wire.beginTransmission(_address);
	if (ab == 0)
	{
		Wire.write(0x12); // address PORT A
	}
	else {
		Wire.write(0x13); // address PORT B
	}
	Wire.write(bitsToSend);    // PORT A
	Wire.endTransmission();
}

uint8_t PinExtender::getAB(uint8_t ab) {//ab=0-A< ab=1-B
	Wire.beginTransmission(_address);
	if (ab == 0)
	{
		Wire.write(0x12); // address PORT A
	}
	else 
	{
		Wire.write(0x13); // address PORT B
	}
	Wire.endTransmission();
	Wire.requestFrom(_address, (uint8_t)1);
	return Wire.read();
}

uint8_t PinExtender::readRegister(uint8_t addr) {
	// read the current GPINTEN
	Wire.beginTransmission(_address);
	Wire.write(addr);
	Wire.endTransmission();
	Wire.requestFrom(_address, (uint8_t)1);
	return Wire.read();
}

void PinExtender::writeRegister(uint8_t regAddr, uint8_t regValue) {
	// Write the register
	Wire.beginTransmission(_address);
	Wire.write(regAddr);
	Wire.write(regValue);
	Wire.endTransmission();
}

/**
 * OLD
 */

void PinExtender::setAll(uint16_t bitsToSend) {
	// ��� �������� 16 ����� ���������� unsigned int
	data = bitsToSend;
	// ��������� �� ����� �������� �����
	digitalWrite(latchPin, LOW);
	//delay(100);
	// ��������� ���� 16 ��� �� ��� �����
	// ��� ������ � ������ � ������ �������
	// "������������" ����� � ��������
	shiftOut(dataPin, clockPin, MSBFIRST, lowByte(data));
	shiftOut(dataPin, clockPin, MSBFIRST, highByte(data));

	// "�����������" �������, ����� ���� ��������� �� ������� ��������
	digitalWrite(latchPin, HIGH);
}


void PinExtender::registerWrite(int8_t whichPin, uint8_t whichState) {
	if (whichPin < 0)  return;
	//logg.logging("Set pin " + String(whichPin) + " to " + String(whichState));
	if (whichPin < 100) {
		digitalWrite(whichPin, whichState);
		return;
	}

	// ��� �������� 16 ����� ���������� unsigned int
	uint16_t bitsToSend = data;
	// ������������� HIGH � ��������������� ���
	bitWrite(bitsToSend, whichPin-100, whichState);
	//��� �����������
	if (bitsToSend == data) return;

	setAll(bitsToSend);
}


boolean PinExtender::getPin(int8_t whichPin) {
	if (whichPin < 0) return false;
	if (whichPin < 100) return digitalRead(whichPin);
	return  bitRead(data, whichPin-100);
}

uint16_t PinExtender::getAll() {
	return data;
}
