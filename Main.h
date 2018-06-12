// Main.h

#ifndef _MAIN_h
#define _MAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Mode.h"

class Main: public Mode {
public:
	Main(Hardware * h);

	void draw();
	void drawImm();
	void left();
	void right();
	void press();
	void long_press();
private:

};





#endif

