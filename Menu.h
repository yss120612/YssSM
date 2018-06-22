// Menu.h

#ifndef _MENU_h
#define _MENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
extern class MenuItem;

class Menu
{
public:
	Menu(MenuItem * mi);
	~Menu();
	boolean isActive();
	void next();
	void prev();
	
private:
	MenuItem * items;
	MenuItem * choised;
	MenuItem * first;
	Mode * myMode;
	boolean active;
};




#endif

