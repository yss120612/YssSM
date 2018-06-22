
#include "Menu.h"


Menu::Menu(MenuItem *  mi)
{
	items = mi;
}

Menu::~Menu()
{
}

boolean Menu::isActive()
{
	return active;
}

void Menu::next()
{
}

void Menu::prev()
{
}
