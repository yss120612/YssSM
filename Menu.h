// Menu.h

#ifndef _MENU_h
#define _MENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
//#include "Mode.h"
#include "Display.h"
#include <QList.h>

const int8_t DISP_LINES = 4;
const int8_t DELTA_Y = 12;
const int8_t SHIFT_X = 2;
const int8_t SHIFT_Y = 16;

class MenuItem;

class Menu
{
public:
	Menu();
	~Menu();
	boolean isActive();
	boolean setActive(boolean acc) { active = acc; }
	MenuItem * current();
	void add(MenuItem * mi);
	void next();
	void prev();
	void display(Display *d);
	void setParent(Menu *m);
	Menu * getParent();
	void setEditParams(uint8_t ep);
	uint8_t getEditParams();
protected:
	QList<MenuItem *> items;
	int8_t curr;
	Menu * parent;
	boolean active;
	uint8_t edit_param;
};




#endif

