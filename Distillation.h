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

protected:
	void draw(long m);
	void initDraw();
	void left();
	void right();
	void press();
	void long_press();
	void makeMenu();
	void command(uint8_t id);
	void stop(uint8_t reason);
	void start();
	void initParams(MenuParameter * mp);
	void acceptParams(MenuParameter * mp);
	
};



#endif

