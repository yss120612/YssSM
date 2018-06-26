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
}

Menu * MenuSubmenu::select()
{
	return submenu;
}

MenuSubmenu::~MenuSubmenu()
{
	delete submenu;
}

MenuParameter::MenuParameter(String nm, int i) :MenuItem(nm)
{
	current = sm;
	id = i;
	kind = 3;
}



MenuIParameter::MenuIParameter(String nm,int i, int sm) :MenuItem(nm)
{
	current = sm;
	id = i;
	kind = 3;
}

Menu * MenuIParameter::select()
{
	return parent;
}
