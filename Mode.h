// Mode.h

#ifndef _MODE_h
#define _MODE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif



#include  "Display.h"

class Mode
{
public:
	Mode(Display * d);
	virtual void draw() = 0;

private:
	Mode * parent;
	Display * display;
};

#endif

