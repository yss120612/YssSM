// Manual.h

#ifndef _MANUAL_h
#define _MANUAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Mode.h"
#include "Workmodes.h"

class Manual : public Mode
{
public:
	Manual(Aggregates * a, Hardware *h);
	~Manual();
	String getData(uint w);
	void showState();
	void process(long ms);
	void makeMenu();
	void command(MenuCommand * id);
	void stopAll();
	void initParams(MenuParameter * mp);
	void acceptParams(MenuParameter * mp);
protected:
	MenuItem * mKran,* mHeater,* mPump, *mTest;
};


#endif

