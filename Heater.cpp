#include "Log.h"
#include "Heater.h"


Heater::Heater() {
	have_relay = false;
	relay_is_on = false;
	heater_stopped = true;
	cy = false;
};

//static int k = 0;

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

void Heater::setup(Hardware * h, uint8_t hp, int8_t rp) {
	hard = h;
	heater_pin = hp;
	pinMode(heater_pin, OUTPUT);
	have_relay = rp >= 0;
	relay_pin = rp;
	hard->getExtender()->setPinMode(relay_pin, OUTPUT);
	/*kp = kc * 0.6;
	ki = 2 * kc * 0.6 / (test_time / 1000);
	kd = kc * 0.6 * (test_time / 1000) / 8;*/
	kp = 70.0f;
	//ki = 600;
	kd = 3.0f;
	ki = 10.0f;
}

void Heater::switchRelay(boolean on) {
	if (have_relay)
	{
		relay_is_on = on;
		boolean hs = heater_stopped;
		heater_stopped = true;
		delay(50);
		hard->getExtender()->digWrite(relay_pin, on ? HIGH : LOW);
	}
	heater_stopped = !on;
}

//реле включено если его нет вообще или оно есть и включено
boolean Heater::relayIsOn() {
	return !have_relay || relay_is_on;
}

boolean Heater::isON() {
	return !heater_stopped;
}

void Heater::shiftPower(int8_t sh)
{
	if (power + sh > max_power) {
		power = max_power;
	}
	else if (power + sh < 0) {
		power = 0;
	}
	else {
		power += sh;
	}
}

void Heater::setPID(float inp, float targetT)
{
	/*kp = kc * 0.6;
	ki = 2 * kc * 0.6 / (test_time / 1000);
	kd = kc * 0.6 * (test_time / 1000) / 8;*/
		float err = targetT-inp;
		float dErr = err - lasterr;
		float output;

		outsumm += (ki * err);
		
		outsumm = _min(_max(outsumm, 0), 100);

		//пропорциональный, интегральный, дифференциальный
		output = kp * err + outsumm + kd * dErr;

		output = _min(_max(output, 0), 100);
				
		lasterr = err;

		setPower(output);
}

void Heater::start() {
	switchRelay(true);
	
}

void Heater::stop() {
	switchRelay(false);
	
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

