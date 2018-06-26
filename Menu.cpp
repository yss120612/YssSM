
#include "Menu.h"
#include "MenuItem.h"


Menu::Menu()
{
	curr = -1;
}

Menu::~Menu()
{
	for (uint8_t i; i < items.size(); i++) {
		delete items.get(i);
	}
	items.clear();
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

void Menu::display(Display *d)
{
	if (curr < 0) return;
	int8_t first = (curr / DISP_LINES) * DISP_LINES;

	for (uint8_t i = 0; i < DISP_LINES && first + i < items.size(); i++) {

		if (curr == i) {
			d->drawXY(SHIFT_X * 2, SHIFT_Y + DELTA_Y * i, items.get(first + i)->getName());
		}
		else {
			d->drawXY(SHIFT_X, SHIFT_Y + DELTA_Y * i, items.get(first + i)->getName());
		}
	}

}
