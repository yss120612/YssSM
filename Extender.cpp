
#include "Extender.h"
#include "Log.h"
#include <Wire.h>

PinExtender::PinExtender()
{
}

PinExtender::~PinExtender()
{
}




/**
 * new
 */
void PinExtender::setup(uint8_t addr)
{
	_address = addr;
	Wire.beginTransmission(_address);  // i2c Ц адрес (A0-0,A1-0,A2-0)
	Wire.write(IODIRA); // IODIRA register
	Wire.write(0x00); // настроить PORT A как output //bit 0-output 1-input
	Wire.write(IODIRB); // IODIRB register
	Wire.write(0x00); // настроить PORT B как output 
	Wire.endTransmission();
}


//void PinExtender::setAB(uint8_t bitsToSend,uint8_t ab) {//ab=0:A ab=1:B
//	if (ab == 0)
//	{
//		writeRegister(GPIOA, bitsToSend);
//	}
//	else {
//		writeRegister(GPIOB, bitsToSend);
//	}
//}
//
//uint8_t PinExtender::getAB(uint8_t ab) {//ab=0-A< ab=1-B
//	if (ab == 0)
//	{
//		return readRegister(GPIOA);
//	}
//	else 
//	{
//		return readRegister(GPIOB);
//	}
//}

uint8_t PinExtender::readRegister(uint8_t regAddr) {
	// read the current GPINTEN
	Wire.beginTransmission(_address);
	Wire.write(regAddr);
	Wire.endTransmission();
	//delay(10);
	Wire.requestFrom(_address, (uint8_t)1);
	return Wire.read();
}

void PinExtender::writeRegister(uint8_t regAddr, uint8_t regValue) {
	// Write the register
	Wire.beginTransmission(_address);
	Wire.write(regAddr);
	//delay(10);
	Wire.write(regValue);
	//delay(10);
	Wire.endTransmission();
}

/**
 * Helper to update a single bit of an A/B register.
 * - Reads the current register value
 * - Writes the new register value
 */
void PinExtender::updateRegisterBit(uint8_t pin, uint8_t pValue, uint8_t portAaddr, uint8_t portBaddr) {
	uint8_t regValue;
	uint8_t bit = pin%8;
	if (pin < 8) {
		regValue = readRegister(portAaddr);
		bitWrite(regValue, bit, pValue);
		writeRegister(portAaddr, regValue);
	}
	else {
		regValue = readRegister(portBaddr);
		bitWrite(regValue, bit, pValue);
		writeRegister(portBaddr, regValue);
	}
}


void PinExtender::pullUp(uint8_t p, uint8_t d) {
	updateRegisterBit(p, d, GPPUA, GPPUB);
}

uint8_t PinExtender::digRead(uint8_t pin) {
	if (pin < 100) {
		return digitalRead(pin);
	}
	else 
	{
		uint8_t bit = (pin-100) % 8;
		return (readRegister(pin < 108 ? GPIOA : GPIOB) >> bit) & 0x1;
	}
	
}

void PinExtender::setPinMode(uint8_t pin ,uint8_t state) {
	if (pin < 100) {
		pinMode(pin, state);
	}
	else
	{
		updateRegisterBit(pin - 100, (state==INPUT), IODIRA , IODIRB);
	}
}

void PinExtender::digWrite(uint8_t pin, uint8_t d) {
	if (pin < 100) {
		digitalWrite(pin, d);
	}
	else {
		pin -= 100;
		uint8_t gpio = readRegister(pin < 8 ? OLATA : OLATB);
		uint8_t bit = pin % 8;
		bitWrite(gpio, bit, d);
		writeRegister(pin < 8 ? GPIOA : GPIOB, gpio);
	}
	
}

/**
 * OLD
 */

//void PinExtender::setPinMode(int8_t pin, uint8_t mode)
//{
//	if (pin < 0 || pin >= 100) return;
//	pinMode(pin, mode);
//}
//
//void PinExtender::setup(uint8_t ST_CP, uint8_t SH_CP, uint8_t DS)
//{
//	latchPin = ST_CP;
//	clockPin = SH_CP;
//	dataPin = DS;
//	pinMode(latchPin, OUTPUT);
//	pinMode(dataPin, OUTPUT);
//	pinMode(clockPin, OUTPUT);
//	setAll(0);
//}
//
//void PinExtender::setAll(uint16_t bitsToSend) {
//	// дл¤ хранени¤ 16 битов используем unsigned int
//	data = bitsToSend;
//	// выключаем на врем¤ передачи битов
//	digitalWrite(latchPin, LOW);
//	//delay(100);
//	// разбиваем наши 16 бит на два байта
//	// дл¤ записи в первый и второй регистр
//	// "проталкиваем" байты в регистры
//	shiftOut(dataPin, clockPin, MSBFIRST, lowByte(data));
//	shiftOut(dataPin, clockPin, MSBFIRST, highByte(data));
//
//	// "защелкиваем" регистр, чтобы биты по¤вились на выходах регистра
//	digitalWrite(latchPin, HIGH);
//}
//
//
//void PinExtender::registerWrite(int8_t whichPin, uint8_t whichState) {
//	if (whichPin < 0)  return;
//	//logg.logging("Set pin " + String(whichPin) + " to " + String(whichState));
//	if (whichPin < 100) {
//		digitalWrite(whichPin, whichState);
//		return;
//	}
//
//	// дл¤ хранени¤ 16 битов используем unsigned int
//	uint16_t bitsToSend = data;
//	// устанавливаем HIGH в соответствующий бит
//	bitWrite(bitsToSend, whichPin-100, whichState);
//	//”∆≈ ”—“јЌќ¬Ћ≈Ќќ
//	if (bitsToSend == data) return;
//
//	setAll(bitsToSend);
//}
//
//
//boolean PinExtender::getPin(int8_t whichPin) {
//	if (whichPin < 0) return false;
//	if (whichPin < 100) return digitalRead(whichPin);
//	return  bitRead(data, whichPin-100);
//}
//
//uint16_t PinExtender::getAll() {
//	return data;
//}
