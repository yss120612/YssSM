// MenuItem.h

#ifndef _MENUITEM_h
#define _MENUITEM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Menu.h"

//class Mode;

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

//typedef void(Mode::*tCommand)();

class MenuCommand : public MenuItem
{
public:
	MenuCommand(String na, uint8_t i);
	uint8_t getId() { return id; }
	Menu * select();
protected:
	//tCommand selectFunc;
	uint8_t id;
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

