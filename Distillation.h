// Distillation.h

#ifndef _DISTILLATION_h
#define _DISTILLATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Mode.h"
#include "Workmodes.h"

class Distillation : public Mode
{
public:
	Distillation(Aggregates * a, Hardware *h);
	~Distillation();
	String getData(uint w) { return Mode::getData(w); }
protected:
	long last_time;

	void draw(long m);
	void initDraw();
	void showState();
	void process(long ms);
	void left();
	void right();
	void press();
	void long_press();
	void makeMenu();
	void command(MenuCommand * id);
	void stop(uint8_t reason);
	void start();
	void initParams(MenuParameter * mp);
	void acceptParams(MenuParameter * mp);
	MenuCommand * mcmd;
	float tcube;
	float ttsa;
};



#endif

