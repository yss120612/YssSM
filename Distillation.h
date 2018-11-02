// Distillation.h

#ifndef _DISTILLATION_h
#define _DISTILLATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Mode.h"
#include "Workmodes.h"



class Distillation : public Mode
{
public:
	Distillation(Aggregates * a, Hardware *h);
	~Distillation();
	String getData(uint w);

	void setData(uint w, String ds);
	
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
	boolean cold_check;
	uint8_t check_count;
	uint8_t tsa_alarms;
};



#endif

