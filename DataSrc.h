// DataSource.h

#ifndef _DATASOURCE_h
#define _DATASOURCE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Const.h"

class DataSrc
{

public:
	DataSrc();
	virtual String getData(uint what) = 0;


private:

};





#endif

