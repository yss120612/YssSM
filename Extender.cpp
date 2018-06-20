
#include "Extender.h"

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


void PinExtender::setAll(uint16_t bitsToSend) {
	// ��� �������� 16 ����� ���������� unsigned int
	data = bitsToSend;
	// ��������� �� ����� �������� �����
	digitalWrite(latchPin, LOW);
	delay(50);
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
