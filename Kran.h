// Kran.h

#ifndef _KRAN_h
#define _KRAN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Hardware.h"

const uint16_t switch_time = 7000;
const uint8_t quantumT = 70;

class Kran {
public:
	Kran() {
	};

	void forceClose();
	void openQuantum(float oq);
	void shiftQuantum(float oq);
	void process(long ms);
	boolean measureState();
	void setup(Hardware * h, uint8_t c_pin, uint8_t o_pin, int8_t m_pin = -1, int8_t r_pin = -1);
	void close();
	void open();
	float getState() { return state; }
private:
	Hardware * hard;
	boolean inQuantum;
	boolean inProgress;
	long progress_time;
	uint8_t close_pin;
	uint8_t open_pin;
	int8_t measure_pin;
	int8_t relay_pin;
	float state;
	float quantum;

};

#endif


