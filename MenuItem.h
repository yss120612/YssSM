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
	uint8_t getId() { return id; }
protected:
	String name;
	uint8_t kind;
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

class MenuCommand : public MenuItem
{
public:
	MenuCommand(String na, uint8_t i);
	Menu * select();
protected:

};

class MenuParameter : public MenuItem {
public:
	MenuParameter(String na, Menu * par, int id);
	void setParent(Menu * m) { parent = m; }
	Menu * getParent() { return parent; }
	Menu * select() { return parent; }
	
	virtual String getStCurr() = 0;
	virtual void up() = 0;
	virtual void down() = 0;
	virtual boolean next() = 0;
	void addSubName(String s) { sub_names.push_back(s); }
protected:
	Menu * parent;
	QList <String> sub_names;
	uint8_t counter;
	uint8_t	select_counter;
};

class MenuIParameter : public MenuParameter {
public:
	MenuIParameter(String na, Menu * par, int id, int sm);
	int getCurrent() { return current; };
	void setup(uint8_t st, int m_i, int m_a, uint8_t sc=1) { step = st; ma = m_a; mi = m_i; counter = 0; select_counter = sc; }
	String getStCurr() { return String(current); };
	void up() { current + step>ma?ma:current+=step; }
	void down() { current - step<mi ? mi : current -= step; }
	boolean next() { counter++; if (counter > select_counter) return true; return false; };
protected:
	int current;
	uint8_t step;
	int mi;
	int ma;
};
#endif

