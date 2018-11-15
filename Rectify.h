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
	void setData(uint w, String ds);
	void initDraw();
protected:
	void showState();
	void process(long ms);
	void makeMenu();
	void command(MenuCommand * id);
	void stop(uint8_t reason);
	void start();
	void initParams(MenuParameter * mp);
	void acceptParams(MenuParameter * mp);
	void next();
	MenuCommand * mcmd;
	MenuCommand *cont;
	bool head_collected;
	bool stop_defined;
	//float tcube;
	//float ttsa;
	//float tdef;
	boolean checkLowTSA;
	boolean getTail;
	//long TSAchecked;
	//long TSAcheckedCold;
	uint8_t coldBeginCheck;
	//long workSelf;
	uint8_t tsa_alarms;
	
};


#endif

