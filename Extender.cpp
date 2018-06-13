
#include "Extender.h"

PinExtender::PinExtender()
{
}

PinExtender::~PinExtender()
{
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
	// ��������� ���� 16 ��� �� ��� �����
	// ��� ������ � ������ � ������ �������
	// "������������" ����� � ��������
	shiftOut(dataPin, clockPin, MSBFIRST, lowByte(data));
	shiftOut(dataPin, clockPin, MSBFIRST, highByte(data));

	// "�����������" �������, ����� ���� ��������� �� ������� ��������
	digitalWrite(latchPin, HIGH);
}


void PinExtender::registerWrite(uint8_t whichPin, uint8_t whichState) {
	// ��� �������� 16 ����� ���������� unsigned int
	uint16_t bitsToSend = data;
	// ������������� HIGH � ��������������� ���
	bitWrite(bitsToSend, whichPin, whichState);
	//��� �����������
	if (bitsToSend == data) return;

	setAll(bitsToSend);
}


boolean PinExtender::getPin(uint8_t whichPin) {
	return (data & 1 < whichPin);
}

uint16_t PinExtender::getAll() {
	return data;
}
