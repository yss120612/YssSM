#include "MenuItem.h"

MenuItem::MenuItem(String nm)
{
	name = nm;
	kind = 0;
}

MenuItem::~MenuItem()
{
}

MenuCommand::MenuCommand(String nm, uint8_t i):MenuItem(nm)
{
	id = i;
	kind = 1;
}

Menu * MenuCommand::select()
{
	//if (selectFunc)  selectFunc();
	return NULL;
}

MenuSubmenu::MenuSubmenu(String nm, Menu * sub) :MenuItem(nm)
{
	submenu = sub;
	kind = 2;
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
}


MenuIParameter::MenuIParameter(String nm, Menu * par, int i, int sm) : MenuParameter(nm,par,i)
{
	current = sm;
	kind = 3;
	step = 1;
}


