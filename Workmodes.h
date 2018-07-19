// Workmodes.h

#ifndef _WORKMODES_h
#define _WORKMODES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Mode.h";



class WorkModes
{
public:
	WorkModes();
	~WorkModes();
	void addMode(Mode * m);
	void setup(Encoder * enc);
	void setCurrent(uint8_t i);
	Mode * getCurrent();
private:
	Mode * current;
	QList <Mode *> _modes;
	Encoder * encoder;
};

extern WorkModes workMode;

#endif

