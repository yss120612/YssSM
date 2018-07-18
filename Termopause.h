// Termopause.h

#ifndef _TERMOPAUSE_h
#define _TERMOPAUSE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class TermoPause
{
public:
	TermoPause();
	~TermoPause();
	void setup(int p, uint8_t t);
	int getTime() { return _minutes; }
	uint8_t getTemp() { return _temperature; }
	void setTime( int m) { _minutes=m; }
	void setTemp(uint8_t t) { _temperature=t; }
private:
	int _minutes;
	uint8_t _temperature;
};



#endif

