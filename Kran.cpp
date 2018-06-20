#include "Kran.h"

void Kran::close() {
	//if (!inProgress && measureState()) {
	if (!inProgress) {
		inProgress = true;
		progress_time = millis();
		pext->registerWrite(close_pin, HIGH);
	}
}

void Kran::forceClose() {
	inProgress = true;
	progress_time = millis();
	pext->registerWrite(close_pin, HIGH);
}

void Kran::openQuantum(int8_t oq)
{ //min==17 max==87
	inQuantum = true;
	forceClose();
	quantum = oq;
	state = oq;
}

void Kran::shiftQuantum(int8_t oq)
{
	if (state + oq > 100 || state + oq < 0) return;
	inQuantum = true;
	progress_time = millis();
	state += oq;
	if (oq < 0) {
		quantum = -oq;
		pext->registerWrite(close_pin, HIGH);
	}
	else {
		quantum = oq;
		pext->registerWrite(open_pin, HIGH);
	}
}

void Kran::process(long ms) {
	if (!inProgress && !inQuantum) return;
	if (inProgress) {
		if (ms - progress_time > switch_time) {
			if (pext->getPin(open_pin) == HIGH) {
				state = 100;
			}
			else {
				state = 0;
			}
			pext->registerWrite(open_pin, LOW);
			pext->registerWrite(close_pin, LOW);
			inProgress = false;
			if (quantum > 0) {
				pext->registerWrite(open_pin, HIGH);
				progress_time = ms;
			}
		}
	}
	else {
		if (ms - progress_time > quantum*quantumT) {
			pext->registerWrite(open_pin, LOW);
			pext->registerWrite(close_pin, LOW);
			inQuantum = false;
			quantum = 0;
		}
	}

}

void Kran::open() {
	//if (!inProgress && !measureState()) {
	if (!inProgress) {
		inProgress = true;
		progress_time = millis();
		pext->registerWrite(open_pin, HIGH);
	}
}

boolean Kran::measureState() {
	if (measure_pin < 0 || relay_pin < 0) return false;
	pext->registerWrite(relay_pin, HIGH);
	delay(200);
	boolean result = analogRead(measure_pin)<100;
	//int result= analogRead(measure_pin);
	pext->registerWrite(relay_pin, LOW);
	delay(200);
	return result;
}

void Kran::setup(PinExtender * pex, uint8_t c_pin, uint8_t o_pin, int8_t m_pin, int8_t r_pin) {
	close_pin = c_pin;
	open_pin = o_pin;
	measure_pin = m_pin;
	relay_pin = r_pin;
	pext = pex;

	pext->setPinMode(open_pin, OUTPUT);
	pext->setPinMode(close_pin, OUTPUT);
	pext->registerWrite(close_pin, LOW);
	pext->registerWrite(open_pin, LOW);

	pext->setPinMode(relay_pin, OUTPUT);
	pext->registerWrite(relay_pin, LOW);
	pext->setPinMode(measure_pin, INPUT);

	inProgress = false;
	inQuantum = false;
	quantum = 0;
	state = 0;
	progress_time = 0;
}



