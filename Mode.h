// Mode.h


#ifndef _MODE_h
#define _MODE_h
#define _SERIAL


#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif



#include  "Hardware.h"

class Mode
{
public:
	Mode(Hardware * h);
	virtual void draw() = 0;
	virtual void drawImm() = 0;
	virtual void left() = 0;
	virtual void right() = 0;
	virtual void press() = 0;
	virtual void long_press() = 0;
protected:
	boolean drawImmed;
	Mode * parent;
	Hardware * hardware;
};

#endif

