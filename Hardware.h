// Hardware.h

#ifndef _HARDWARE_h
#define _HARDWARE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif



#include <OneWire.h>
#include <DS1302.h>
#include <MD_DS3231.h>
#include <Wire.h>
#include <SSD1306Wire.h>

#include "Extender.h"
#include "DallasTerm.h"
//#include "WiFiHelper.h"
#include "Httphelper.h"
#include "Config.h"
#include "Beeper.h"
#include "Encoder.h"
#include "AT24C32.h"
#include "RTCmemory.h"

class Hardware
{
public:
	Hardware();
	~Hardware();
	void init();
	void timed_process(long ms);
	void process(long ms);
	SSD1306Wire * getDisplay();
	DallasTerm * getTKube();
	DallasTerm * getTTsarga();
	DallasTerm * getTWater();
	DallasTerm * getTTriak();
	DallasTerm * getTTSA();
	//HttpHelper * getHttpHelper();
	Config * getConfig();
	Beeper * getBeeper();
	PinExtender * getExtender();
	MD_DS3231 * getClock();
	Encoder * getEncoder();
	AT24C32 * getAT24mem();
	RTCmemory * getRTCmem();
	OneWire * getOneWire() { return &ow; }
	

	//void setDisplay(SSD1306Wire * d);
	//void setTKube(DallasTerm * k);
	//void setTTsarga(DallasTerm * t);
	//void setTWater(DallasTerm * w);
	//void setTTriak(DallasTerm * w);
	//void setHttpHelper(HttpHelper * h);
	//void setConfig(Config * c);
	//void setBeeper(Beeper * b);
	//void setExtender(PinExtender * p);
	//void setClock(MD_DS3231 * cl);


protected:
	
	OneWire ow;
	DallasTerm t_tsarga;
	//DallasTerm t_water;
	DallasTerm t_triak;
	DallasTerm t_tsa;
	DallasTerm t_kube;
	//HttpHelper httpHelper;
	Beeper beeper;
	Config config;
	PinExtender pinExtender;
	
	SSD1306Wire display;
	
	Encoder encoder;
	AT24C32 at24mem;
	RTCmemory RTCmem;

	//OneWire ow(TEMPERATURE_PIN);
	//SSD1306Wire display(0x3C, SDA, SCL);
	//DallasTerm t_kube(tkube, &ow, 2.5);
	//MD_DS3231 clock;
};



#endif

