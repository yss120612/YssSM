// Mode.h


#ifndef _MODE_h
#define _MODE_h



#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include  "Log.h"

#include  "Hardware.h"

#include  "Aggregates.h"

#include  "Menu.h"

#include  "MenuItem.h"


class Mode
{
public:
	Mode( Aggregates * a, Hardware *h);
	virtual void draw() = 0;
	virtual void initDraw() = 0;
	virtual void drawImm();
	virtual void makeMenu() = 0;
	virtual void command(uint8_t id) = 0;
	virtual void params(uint8_t id) = 0;
protected:
	boolean drawImmed;
	Mode * parent;
	Hardware * hardware;
	Aggregates * agg;
	Menu * menu;
};

#endif

