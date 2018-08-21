#include "Log.h"
#include "Heater.h"


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
	//dummy++;
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

void Heater::setup(Hardware * h, uint8_t hp, int8_t rp) {
	hard = h;
	heater_pin = hp;
	pinMode(heater_pin, OUTPUT);
	have_relay = rp >= 0;
	relay_pin = rp;
	hard->getExtender()->setPinMode(relay_pin, OUTPUT);
}

void Heater::switchRelay(boolean on) {
	if (have_relay)
	{
		boolean hs = heater_stopped;
		heater_stopped = true;
		delay(50);
		hard->getExtender()->registerWrite(relay_pin, on ? HIGH : LOW);
		heater_stopped = hs;
		//logg.logging("relay is "+String(on));
	}
}

//реле включено если его нет вообще или оно есть и включено
boolean Heater::relayIsOn() {
	return !have_relay || hard->getExtender()->getPin(relay_pin) == HIGH;
	/*if (relay_pin >= 100) {
		return extd->getPin(relay_pin - 100);
	}
	else {
		return !have_relay || extd->getPin(relay_pin - 100) == HIGH;
	}*/
}

boolean Heater::isON() {
	return !heater_stopped;
}

void Heater::shiftPower(int8_t sh)
{
	if (power + sh <= max_power && power + sh>=0) power += sh;
}

void Heater::setPID(float inp, float targetT)
{
	
		bool pOnE = true;
		float err = targetT - inp;
		float dInput = inp - lastinput;
		

		float output;
		outsumm += (ki * err);
		if (!pOnE) outsumm -= (kp * dInput);
		if (outsumm > 100) outsumm = 100;
		else if (outsumm < 0) outsumm = 0;

		if (pOnE) output = kp * err;
		else output = 0;
				
		output += outsumm - kd * dInput;

		if (output > 100) output = 100;
		else if (output < 0) output = 0;
		
		lastinput = inp;

		setPower(output);
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
	power = _max(_min(pw, max_power), 0);
	
	curr = max_power / 2;
	heater_stopped = hs;
}

