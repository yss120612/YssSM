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
	~Mode();
	virtual void draw(long m);
	virtual void initDraw();
	virtual void showState() = 0;
	virtual void drawImm(long m);
	void readTime();
	String getTimeStr();
	virtual void makeMenu() = 0;
	virtual void command(MenuCommand * id) = 0;
	virtual void initParams(MenuParameter * mp)=0;
	virtual void acceptParams(MenuParameter * mp)=0;
	virtual void processMenuPress();
	virtual void processMenuChange(boolean isUp);
	virtual void processMenuLong();
	virtual void process(long ms) = 0;
	virtual String getData(uint w);
	virtual void setData(uint w,String ds);
	virtual void left();
	virtual void right();
	virtual void press();
	virtual void long_press();
	virtual void left_nomenu() {};
	virtual void right_nomenu() {};
	virtual void press_nomenu() {};
	long last_time;
protected:
	String MyName;
	char tim[9];
	char tleft[9];
	boolean drawImmed;
	Mode * parent;
	Hardware * hardware;
	Aggregates * agg;
	Menu * menu;
	int8_t work_mode;
	int8_t end_reason;
	//int8_t err;
};

#endif

