// Suvid.h

#ifndef _SUVID_h
#define _SUVID_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "Heater.h"
#include "DallasTerm.h"
#include "Beeper.h"
#include "Display.h"
#include "Mode.h"
#include "Termopause.h"
#include "Workmodes.h"




class Suvid : public Mode {
public:
	Suvid(Aggregates * a, Hardware *h);
	void start();
	void stop(uint8_t reason);
	String getData(uint w) { return Mode::getData(w); }
	
	void process(long ms);
	//int getHeaterPower() { return hardware->getHeater()->getPower(); };
protected:
	
	void armAlarm();
	void timeLeft();
	TermoPause tpause;
	long last_time;
	
	//long time;
	void error(uint8_t);
	void draw(long m);
	void showState();
	void initDraw();
	void left();
	void right();
	void press();
	void long_press();
	void makeMenu();
	void command(MenuCommand * id);
	void initParams(MenuParameter * mp);
	void acceptParams(MenuParameter * mp);
};


#endif

