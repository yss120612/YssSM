
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
	// для хранения 16 битов используем unsigned int
	data = bitsToSend;
	// выключаем на время передачи битов
	digitalWrite(latchPin, LOW);
	delay(50);
	// разбиваем наши 16 бит на два байта
	// для записи в первый и второй регистр
	// "проталкиваем" байты в регистры
	shiftOut(dataPin, clockPin, MSBFIRST, lowByte(data));
	shiftOut(dataPin, clockPin, MSBFIRST, highByte(data));

	// "защелкиваем" регистр, чтобы биты появились на выходах регистра
	digitalWrite(latchPin, HIGH);
}


void PinExtender::registerWrite(int8_t whichPin, uint8_t whichState) {
	if (whichPin < 0)  return;
	if (whichPin < 100) {
		digitalWrite(whichPin, whichState);
		return;
	}

	// для хранения 16 битов используем unsigned int
	uint16_t bitsToSend = data;
	// устанавливаем HIGH в соответствующий бит
	bitWrite(bitsToSend, whichPin-100, whichState);
	//УЖЕ УСТАНОВЛЕНО
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
