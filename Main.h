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
	Main(Aggregates * a,Hardware * h);

	void draw(long m);
	void initDraw();
	void makeMenu();
	void left();
	void right();
	void press();
	void long_press();
	void command(uint8_t id);
	void initParams(MenuParameter * mp);
	void acceptParams(MenuParameter * mp);
private:
	int counter;
};





#endif

