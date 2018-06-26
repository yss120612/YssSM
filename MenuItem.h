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
//typedef void(Mode::*tCommand)();

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
	uint8_t kind;
	
};

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
	~MenuSubmenu();
	Menu * select();
protected:
	Menu * submenu;
};


class MenuParameter : public MenuItem {
public:
	MenuParameter(String na, int id);
	void setParent(Menu * m) { parent = m; }
	Menu * getParent() { return parent; }
	uint8_t getId() { return id; }
protected:
	Menu * parent;
	uint8_t id;
};



class MenuIParameter : public MenuParameter {
public:
	MenuIParameter(String na, int id, int sm);
	Menu * select() { return parent; }
	int getCurrent() { return current; }
	void setCurrent(int c) { current = c; }
protected:
	int current;
	int step;
};


#endif

