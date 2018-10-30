// Brewing.h

#ifndef _BREWING_h
#define _BREWING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Mode.h"


class Brewing : public Mode {
public:
	Brewing(Aggregates * a, Hardware *h);
	~Brewing() { delete mcmd; };
	void start();
	void stop(uint8_t reason, String text = "");
	void process(long ms);
	String getData(uint w);
protected:
	uint8_t phase;
	MenuCommand * mcmd;
	void showState();
	uint8_t getTarget();
	int getTimeLeft();
	void initDraw();
	void makeMenu();
	boolean have_chiller;
	void command(MenuCommand * id);
	void initParams(MenuParameter * mp);
	void acceptParams(MenuParameter * mp);
};

#endif

