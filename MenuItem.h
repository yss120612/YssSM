// MenuItem.h

#ifndef _MENUITEM_h
#define _MENUITEM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Menu.h"

class MenuItem
{
public:
	MenuItem(String nm);
	~MenuItem();
	virtual Menu * select()=0;
	uint8_t getKind() { return kind; }
	String getName() { return name; }
protected:
	String name;
	Menu * child_menu;
	uint8_t kind;
	
};

class MenuCommand : public MenuItem
{
public:
	MenuCommand(String na, void(*func) ());
	Menu * select();
protected:
	void(*selectFunc)();
};

class MenuSubmenu : public MenuItem
{
public:
	MenuSubmenu(String na, Menu * sm);
	Menu * select();
protected:
	Menu * submenu;

};



#endif

