// Heater.h

#ifndef _HEATER_h
#define _HEATER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Hardware.h"

class Heater
{
public:
	Heater();
	~Heater() {};
	void processHeater();//вызываем при проходе через 0
	void setPower(int pw);
	uint8_t  getPower();
	void start();
	void stop();
	void setup(Hardware * h, uint8_t hp, int8_t rp);
	boolean isON();
	void shiftPower(uint8_t sh);
	
private:
	boolean cy;
	uint8_t heater_pin;
	uint8_t relay_pin;
	int8_t power;
	const int8_t max_power = 100;
	int16_t curr;
	volatile boolean heater_stopped;
	boolean have_relay;
	void switchRelay(boolean on);
	boolean relayIsOn();
	Hardware * hard;
};
#endif


