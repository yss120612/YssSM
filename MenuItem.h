// MenuItem.h

#ifndef _MENUITEM_h
#define _MENUITEM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Menu.h"

enum MI_Kind {
	ABSTRACT,
	SUBMENU,
	COMMAND,
	PARAMETRINT,
	PARAMETRFLOAT,
	PARAMETRBOOL,
	PARAMETRSTR
};


class MenuItem
{
public:
	MenuItem(String nm);
	~MenuItem();
	virtual Menu * select()=0;
	uint8_t getKind() { return kind; }
	String getName() { return name.indexOf(';')<0?name:name.substring(0, name.indexOf(';')); }
	String getMyName() { return name.indexOf(';')<0 ? name : name.substring(name.indexOf(';')+1); }
	uint8_t getId() { return id; }
	String getRAWName() {return name; }
	void setName(String s) { name=s; }
	void setId(uint8_t i) { id=i; }
	void setVisible(boolean v) { visible = v; }
	boolean isVisible() { return visible; }
protected:
	String name;
	uint8_t kind;
	uint8_t id;
	boolean visible;
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

	void setNext(MenuParameter * _n) { _next = _n; _n->setPrev(this); }
	MenuParameter * getNext() { return _next; }
	void setPrev(MenuParameter * _p) { _prev = _p; }
	MenuParameter * getPrev() { return _prev; }

	Menu * getParent() { return parent; }
	Menu * select() { return parent;}
	virtual String getStCurr() = 0;
	virtual void up() = 0;
	virtual void down() = 0;
protected:
	MenuParameter * _next;
	MenuParameter * _prev;
	Menu * parent;
};

class MenuIParameter : public MenuParameter {
public:
	MenuIParameter(String nm, Menu * par, int i);
	int getCurrent() { return current; };
	void setup(int curr, uint8_t st, int m_i, int m_a) {current=curr, step = st; ma = m_a; mi = m_i;}
	String getStCurr() { return String(current); };
	void up() { current + step>ma?ma:current+=step; }
	void down() { current - step<mi ? mi : current -= step; }
protected:
	
	int current;
	uint8_t step;
	int mi;
	int ma;
};

class MenuFParameter : public MenuParameter {
public:
	MenuFParameter(String nm, Menu * par, int i);
	float getCurrent() { return current; };
	void setup(float curr, float st, float m_i, float m_a) { current = curr, step = st; ma = m_a; mi = m_i; }
	String getStCurr() { return String(current,1); };
	void up() { current + step>ma ? ma : current += step; }
	void down() { current - step<mi ? mi : current -= step; }
protected:

	float current;
	float step;
	float mi;
	float ma;
};

class MenuBParameter : public MenuParameter {
public:
	MenuBParameter(String nm, Menu * par, int i);
	bool getCurrent() { return current; };
	void setup(bool curr) { current = curr; }
	String getStCurr() { return current ? "YES" : "NO"; };
	void up() { current = !current; }
	void down() { up(); }
protected:
	bool current;
};

#endif

