// Mode.h


#ifndef _MODE_h
#define _MODE_h



#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include  "Hardware.h"

#include "Heater.h"
#include "Cooler.h"

#include  "Menu.h"
#include  "MenuItem.h"

class Mode
{
public:
	Mode(Hardware * h);
	virtual void draw() = 0;
	virtual void drawImm();
	virtual void left() = 0;
	virtual void right() = 0;
	virtual void press() = 0;
	virtual void long_press() = 0;
	virtual void makeMenu() = 0;
	virtual void command(uint8_t id) = 0;
	virtual void params(uint8_t id) = 0;
protected:
	boolean drawImmed;
	Mode * parent;
	Hardware * hardware;
	Menu * menu;
};

#endif

