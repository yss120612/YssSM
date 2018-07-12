// 
// 
// 

#include "Beeper.h"

Beeper::Beeper() {
	
}


void Beeper::setup(uint8_t pin)
{
	beeper_pin = pin;
	pinMode(beeper_pin, OUTPUT);
	tone_time = 0;
}


void Beeper::beep(uint16_t freq, uint16_t dur) {
	tone(beeper_pin, freq); // включаем звук 
	tone_time = millis() + dur;
}

void Beeper::process(long ms) {
	if (tone_time > 0 && tone_time - ms < 0)
	{
		tone_time = 0;
		noTone(beeper_pin); // выключаем звук
	}
}
