
#include "Menu.h"
#include "MenuItem.h"


Menu::Menu()
{
	curr = -1;
}

Menu::~Menu()
{
}

boolean Menu::isActive()
{
	return active;
}

MenuItem * Menu::current()
{
	if (curr < 0) return NULL;
	return items.get(curr);

}

void Menu::add(MenuItem * mi)
{
	items.push_front(mi);
	curr = 0;
}

void Menu::next()
{
	if (items.size() > 0)
	{
		if (curr >= items.size()) {
			curr = 0;
		}
		else {
			curr++;
		}
	}
	else {
		curr = -1;
	}
}

void Menu::prev()
{
	if (items.size() > 0)
	{
		if (curr == 0) {
			curr = items.size()-1;
		}
		else {
			curr--;
		}
	}
	else {
		curr = -1;
	}
}
const int8_t DISP_LINES = 4;
const int8_t DELTA_Y = 12;
const int8_t SHIFT_X = 2;
const int8_t SHIFT_Y = 16;
void Menu::display(Display *d)
{
	if (curr < 0) return;
	int8_t first = (curr / 4+1) * 4;

	for (uint8_t i = 0; i < 4 && i < items.size(); i++) {
		
		if (curr == i) {
			d->drawXY(SHIFT_X*2, SHIFT_Y+DELTA_Y*i, items.get(i)->getName());
		}
		else {
			d->drawXY(SHIFT_X, SHIFT_Y + DELTA_Y*i, items.get(i)->getName());
		}
	}
	
}
