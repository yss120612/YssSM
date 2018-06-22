// Hardware.h

#ifndef _HARDWARE_h
#define _HARDWARE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Extender.h"
#include "Heater.h"
#include "DallasTerm.h"
#include "Display.h"
#include "WiFiHelper.h"
#include "Httphelper.h"
#include "Config.h"
#include "Beeper.h"


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
};



#endif

