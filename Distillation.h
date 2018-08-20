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

const long checkTSA = 1000 * 60 * 3;//����� 3 ������ ��������� TSA

class Distillation : public Mode
{
public:
	Distillation(Aggregates * a, Hardware *h);
	~Distillation();
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

