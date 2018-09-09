#include "MenuItem.h"

MenuItem::MenuItem(String nm)
{
	name = nm;
	kind = ABSTRACT;
	visible = true;
}

MenuItem::~MenuItem()
{
}

MenuCommand::MenuCommand(String nm, uint8_t i):MenuItem(nm)
{
	id = i;
	kind = COMMAND;
}

Menu * MenuCommand::select()
{
	//if (selectFunc)  selectFunc();
	return NULL;
}

MenuSubmenu::MenuSubmenu(String nm, Menu * sub) :MenuItem(nm)
{
	submenu = sub;
	kind = SUBMENU;
	id = 0;
}

Menu * MenuSubmenu::select()
{
	return submenu;
}

MenuSubmenu::~MenuSubmenu()
{
	delete submenu;
}

MenuParameter::MenuParameter(String nm, Menu * par, int i) :MenuItem(nm)
{
	id = i;
	parent = par;
	_next = NULL;
	_prev = NULL;
}

MenuBParameter::MenuBParameter(String nm, Menu * par, int i) : MenuParameter(nm, par, i)
{
	kind = PARAMETRBOOL;
}

MenuIParameter::MenuIParameter(String nm, Menu * par, int i) : MenuParameter(nm,par,i)
{
	kind = PARAMETRINT;
}

MenuFParameter::MenuFParameter(String nm, Menu * par, int i) : MenuParameter(nm, par, i)
{
	kind = PARAMETRFLOAT;
}


