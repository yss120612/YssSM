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
	is_on = false;
}


void Beeper::beep(uint16_t freq, uint16_t dur) {
	if (freq == 0 || dur == 0) return;
	tone_time = 2 * freq * dur / 1000;
	timer1_disable();
	timer1_isr_init();
	timer1_attachInterrupt(t1IntHandler);
	timer1_enable(TIM_DIV1, TIM_EDGE, TIM_LOOP);
	timer1_write((clockCyclesPerMicrosecond() * 500000) / freq);
	is_on = true;
}

void Beeper::process() {
	if (tone_time > 0) {
		// toggle the pin
		digitalWrite(beeper_pin, tone_time % 2);
		tone_time -- ;
	}
	else {
		stop();
	}
}

void Beeper::stop()
{
	timer1_disable();
	digitalWrite(beeper_pin, LOW);
	is_on = false;
}


