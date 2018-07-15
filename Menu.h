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
	boolean setActive(boolean acc) { active = acc; }
	MenuItem * current();
	void add(MenuItem * mi);
	void next();
	void prev();
	void display(SSD1306Wire *d);
	void setParent(Menu *m);
	Menu * getParent();
	void setEditParams(QList<MenuParameter> * ep);
	int8_t currenntParams() { if (edit_param && edit_param->size() > 0) return curr_edit; }
	QList<MenuParameter> * getEditParams();
protected:
	QList<MenuItem *> items;
	int8_t curr;
	Menu * parent;
	boolean active;
	QList<MenuParameter> * edit_param;
	int8_t curr_edit;
};




#endif

