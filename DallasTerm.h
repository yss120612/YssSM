// DallasTerm.h


#include <OneWire.h>
#ifndef _DALLASTERM_h
#define _DALLASTERM_h



#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif



//const uint8_t dim = 5;
//const uint16_t interval = 1000;
const float FILTER_K=0.2f;


class DallasTerm
{
public:
	DallasTerm(const uint8_t addr[], OneWire *d, float del = 0);

	float getTemp();
	void process(long ms);
	void set12bit();
	
private:
	OneWire * ds;
	uint8_t address[8];
	boolean meajured;
	//float temp[dim];
	float delta;
	uint8_t counter;
	boolean changed;
	volatile float temperature;
};

#endif

