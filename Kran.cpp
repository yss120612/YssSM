#include "Kran.h"

void Kran::close() {
	//if (!inProgress && measureState()) {
	if (!inProgress) {
		inProgress = true;
		progress_time = millis();
		hard->getExtender()->digWrite(close_pin, HIGH);
	}
}

void Kran::forceClose() {
	inProgress = true;
	progress_time = millis();
	hard->getExtender()->digWrite(close_pin, HIGH);
}

void Kran::openQuantum(float oq)
{ //min==17 max==87
	inQuantum = true;
	forceClose();
	quantum = oq;
	state = oq;
}

void Kran::shiftQuantum(float oq)
{
	if (state + oq > 100)
	{
		oq = 100 - state;
	}
	if (state + oq < 0) {
		oq = -state;
	}
	if (oq==0) return;
	inQuantum = true;
	progress_time = millis();
	state += oq;
	if (oq < 0) {
		quantum = -oq;
		hard->getExtender()->digWrite(close_pin, HIGH);
	}
	else {
		quantum = oq;
		hard->getExtender()->digWrite(open_pin, HIGH);
	}
}

void Kran::process(long ms) {
	if (!inProgress && !inQuantum) return;
	if (inProgress) {
		if (ms - progress_time > switch_time) {
			if (hard->getExtender()->digRead(open_pin) == HIGH) {
				state = 100;
			}
			else {
				state = 0;
			}
			hard->getExtender()->digWrite(open_pin, LOW);
			hard->getExtender()->digWrite(close_pin, LOW);
			inProgress = false;
			if (quantum > 0) {
				state = quantum;
				hard->getExtender()->digWrite(open_pin, HIGH);
				progress_time = ms;
			}
		}
	}
	else {
		if (ms - progress_time > quantum*quantumT) {
			hard->getExtender()->digWrite(open_pin, LOW);
			hard->getExtender()->digWrite(close_pin, LOW);
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
		hard->getExtender()->digWrite(open_pin, HIGH);
	}
}

boolean Kran::measureState() {
	if (measure_pin < 0 || relay_pin < 0) return false;
	hard->getExtender()->digWrite(relay_pin, HIGH);
	delay(200);
	boolean result = analogRead(measure_pin)<100;
	//int result= analogRead(measure_pin);
	hard->getExtender()->digWrite(relay_pin, LOW);
	delay(200);
	return result;
}

void Kran::setup(Hardware * h, uint8_t c_pin, uint8_t o_pin, int8_t m_pin, int8_t r_pin) {
	close_pin = c_pin;
	open_pin = o_pin;
	measure_pin = m_pin;
	relay_pin = r_pin;
	hard = h;

	hard->getExtender()->setPinMode(open_pin, OUTPUT);
	hard->getExtender()->setPinMode(close_pin, OUTPUT);
	hard->getExtender()->digWrite(close_pin, LOW);
	hard->getExtender()->digWrite(open_pin, LOW);

	if (m_pin >= 0 && r_pin >= 0)
	{
		hard->getExtender()->setPinMode(relay_pin, OUTPUT);
		hard->getExtender()->digWrite(relay_pin, LOW);
		hard->getExtender()->setPinMode(measure_pin, INPUT);
	}
	inProgress = false;
	inQuantum = false;
	quantum = 0;
	state = 0;
	progress_time = 0;
}



