// Mode.h


#ifndef _MODE_h
#define _MODE_h



#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include  "Log.h"

#include  "Hardware.h"

#include  "Aggregates.h"

#include  "Menu.h"

#include  "MenuItem.h"


class Mode : public ModeBase
{
public:
	Mode( Aggregates * a, Hardware *h);
	virtual void draw(long m) = 0;
	virtual void initDraw() = 0;
	virtual void drawImm(long m);
	virtual void makeMenu() = 0;
	virtual void command(uint8_t id) = 0;
	virtual void initParams(MenuParameter * mp)=0;
	virtual void acceptParams(MenuParameter * mp)=0;
	virtual void processMenuPress();
	virtual void processMenuChange(boolean isUp);
	virtual void processMenuLong();
	virtual void process(long ms) = 0;

protected:
	char tim[9];
	char tleft[9];
	boolean drawImmed;
	Mode * parent;
	Hardware * hardware;
	Aggregates * agg;
	Menu * menu;
	int8_t work_mode;
	int8_t end_reason;
	int8_t err;
};

#endif

