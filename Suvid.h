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


const uint16_t test_time = 5000;//5 ������

class Suvid : public Mode {
public:
	Suvid(Aggregates * a, Hardware *h);
	void start();
	void stop(uint8_t reason);

	
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
	void initDraw();
	void left();
	void right();
	void press();
	void long_press();
	void makeMenu();
	void command(uint8_t id);
	void initParams(MenuParameter * mp);
	void acceptParams(MenuParameter * mp);
};


#endif

