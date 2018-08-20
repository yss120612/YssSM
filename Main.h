// Main.h

#ifndef _MAIN_h
#define _MAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Mode.h"
#include "Workmodes.h"

class Main: public Mode {
public:
	Main(Aggregates * a,Hardware * h);

	void draw(long m);
	void showState();
	void initDraw();
	void makeMenu();
	void command(MenuCommand * id);
	void initParams(MenuParameter * mp);
	void acceptParams(MenuParameter * mp);
	void process(long ms) {};
	String getData(uint w) { return Mode::getData(w); }
private:
	
	int counter;
};





#endif

