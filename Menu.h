// Menu.h

#ifndef _MENU_h
#define _MENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
//#include "Mode.h"

#include <QList.h>
#include <SSD1306Wire.h>

const int8_t DISP_LINES = 3;
const int8_t DELTA_Y = 15;
const int8_t SHIFT_X = 9;
const int8_t SHIFT_Y = 15;

class MenuItem;
class MenuParameter;

class Menu
{
public:
	Menu();
	~Menu();
	boolean isActive();
	boolean isEditMode() { return edit_param != NULL; }
	boolean setActive(boolean acc) { active = acc;return acc; }
	MenuItem * current();
	void add(MenuItem * mi);
	void next();
	void prev();
	void display(SSD1306Wire *d);
	void setParent(Menu *m);
	Menu * getParent();
	void setEditParams(MenuParameter * ep);
	MenuParameter * getEditParams();
protected:
	
	void _prev();
	void _next();
	int8_t curr;
	QList<MenuItem *> items;
	QList<MenuItem *> vitems;
	Menu * parent;
	boolean active;
	MenuParameter * edit_param;
};




#endif

