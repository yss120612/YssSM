// Rectify.h

#ifndef _RECTIFY_h
#define _RECTIFY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Mode.h"
#include "Workmodes.h"

class Rectify : public Mode
{
public:
	Rectify(Aggregates * a, Hardware *h);
	~Rectify();
	String getData(uint w);
protected:
	void showState();
	void process(long ms);
	void makeMenu();
	void command(MenuCommand * id);
	void stop(uint8_t reason);
	void start();
	void initParams(MenuParameter * mp);
	void acceptParams(MenuParameter * mp);
	MenuCommand * mcmd;
	float tcube;
	float ttsa;
	float tdef;
	long TSAchecked;
	long TSAcheckedCold;
	long coldBeginCheck;
	uint8_t tsa_alarms;
};


#endif

