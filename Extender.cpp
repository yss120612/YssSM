
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
	// для хранения 16 битов используем unsigned int
	data = bitsToSend;
	// выключаем на время передачи битов
	digitalWrite(latchPin, LOW);
	// разбиваем наши 16 бит на два байта
	// для записи в первый и второй регистр
	// "проталкиваем" байты в регистры
	shiftOut(dataPin, clockPin, MSBFIRST, lowByte(data));
	shiftOut(dataPin, clockPin, MSBFIRST, highByte(data));

	// "защелкиваем" регистр, чтобы биты появились на выходах регистра
	digitalWrite(latchPin, HIGH);
}


void PinExtender::registerWrite(uint8_t whichPin, uint8_t whichState) {
	// для хранения 16 битов используем unsigned int
	uint16_t bitsToSend = data;
	// устанавливаем HIGH в соответствующий бит
	bitWrite(bitsToSend, whichPin, whichState);
	//УЖЕ УСТАНОВЛЕНО
	if (bitsToSend == data) return;

	setAll(bitsToSend);
}


boolean PinExtender::getPin(uint8_t whichPin) {
	return (data & 1 < whichPin);
}

uint16_t PinExtender::getAll() {
	return data;
}
