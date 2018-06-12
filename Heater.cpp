#include "Heater.h"

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

Heater::Heater() {
	have_relay = false;
	heater_stopped = true;
	cy = false;
};


void Heater::processHeater() {
	if (heater_stopped) {
		if (digitalRead(heater_pin) == HIGH) digitalWrite(heater_pin, LOW);
		return;
	}
	if (!relayIsOn()) return;

	cy = !cy;

	if (!cy) return;

	curr -= power;

	if (curr < 0) {
		curr += max_power;
		digitalWrite(heater_pin, HIGH);
	}
	else
	{
		digitalWrite(heater_pin, LOW);
	}
}

void Heater::setup(uint8_t hp, int8_t rp) {
	heater_pin = hp;
	pinMode(heater_pin, OUTPUT);
	if (rp < 0) {
		have_relay = false;
	}
	else
	{
		have_relay = true;
		relay_pin = rp;
		pinMode(relay_pin, OUTPUT);
	}
}

void Heater::switchRelay(boolean on) {
	if (have_relay)
	{
		boolean hs = heater_stopped;
		heater_stopped = true;
		delay(50);
		digitalWrite(relay_pin, (on ? HIGH : LOW));
		heater_stopped = hs;
	}
}

//реле включено если его нет вообще или оно есть и включено
boolean Heater::relayIsOn() {
	return !have_relay || digitalRead(relay_pin) == HIGH;
}

boolean Heater::isON() {
	return !heater_stopped;
}

void Heater::start() {
	switchRelay(true);
	heater_stopped = false;
}

void Heater::stop() {
	switchRelay(false);
	heater_stopped = true;
}

uint8_t Heater::getPower()
{
	return power;
}


void Heater::setPower(int pw) {
	if (pw == power) return;
	boolean hs = heater_stopped;
	heater_stopped = true;
	power = MAX(MIN(pw, max_power), 0);
	curr = max_power / 2;
	heater_stopped = hs;
}

