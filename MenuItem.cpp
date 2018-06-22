#include "MenuItem.h"

MenuItem::MenuItem(String nm)
{
	name = nm;
	kind = 0;
}

MenuItem::~MenuItem()
{
}

MenuCommand::MenuCommand(String nm, void(*func) ()):MenuItem(nm)
{
	selectFunc = func;
	kind = 1;
}

Menu * MenuCommand::select()
{
	if (selectFunc) selectFunc();
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