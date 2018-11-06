// Suvid.h

#ifndef _SUVID_h
#define _SUVID_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


//#include "Heater.h"
//#include "DallasTerm.h"
//#include "Beeper.h"
//#include "Display.h"
#include "Mode.h"
#include "Workmodes.h"
//#include "Termopause.h"
//#include "Workmodes.h"




class Suvid : public Mode {
public:
	Suvid(Aggregates * a, Hardware *h);
	~Suvid() { delete mcmd; };
	void start();
	void stop(uint8_t reason,String text="");
	void process(long ms);
	String getData(uint w);
	void setData(uint w, String ds);
protected:
	MenuCommand * mcmd;
	void showState();
	void initDraw();
	void makeMenu();
	void command(MenuCommand * id);
	void initParams(MenuParameter * mp);
	void acceptParams(MenuParameter * mp);
};


#endif

