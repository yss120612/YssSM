// Hardware.h

#ifndef _HARDWARE_h
#define _HARDWARE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <DS1302.h>
#include <MD_DS3231.h>
#include "Extender.h"
#include "DallasTerm.h"
#include "Display.h"
#include "WiFiHelper.h"
#include "Httphelper.h"
#include "Config.h"
#include "Beeper.h"
//#include "Cooler.h"

class Cooler;
class Heater;


class Hardware
{
public:
	Hardware();
	~Hardware();
	Heater * getHeater();
	Display * getDisplay();
	DallasTerm * getTKube();
	DallasTerm * getTTsarga();
	DallasTerm * getTWater();
	DallasTerm * getTTriak();
	HttpHelper * getHttpHelper();
	Config * getConfig();
	Beeper * getBeeper();
	PinExtender * getExtender();
	MD_DS3231 * getClock();
	Cooler * getTCooler();
	SSD1306Wire * getDisp();

	void setHeater(Heater * h);
	void setDisplay(Display * d);
	void setTKube(DallasTerm * k);
	void setTTsarga(DallasTerm * t);
	void setTWater(DallasTerm * w);
	void setTTriak(DallasTerm * w);
	void setHttpHelper(HttpHelper * h);
	void setConfig(Config * c);
	void setBeeper(Beeper * b);
	void setExtender(PinExtender * p);
	void setClock(MD_DS3231 * cl);
	void setTCooler(Cooler * cl);



private:
	Heater * heater;
	Display * display;
	DallasTerm * t_kube;
	DallasTerm * t_tsarga;
	DallasTerm * t_water;
	DallasTerm * t_triak;
	HttpHelper * httpHelper;
	Beeper * beeper;
	Config * config;
	PinExtender * pinExtender;
	MD_DS3231 * clock;
	Cooler * tcooler;
};



#endif

