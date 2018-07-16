
#include "Menu.h"
#include "MenuItem.h"


Menu::Menu()
{
	curr = -1;
	edit_param = NULL;
}

Menu::~Menu()
{
	for (uint8_t i = 0; i < items.size(); i++) {
		delete items.get(i);
	}
}

void Menu::setEditParams(MenuParameter * ep) {
	edit_param = ep;
}

MenuParameter * Menu::getEditParams()
{
	return edit_param;
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
	items.push_back(mi);
	curr = 0;
}

void Menu::next()
{
	if (items.size() > 0)
	{
		if (curr >= items.size()-1) {
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

void Menu::display(SSD1306Wire *d)
{
	if (curr < 0) return;
	
	int8_t first = (curr / DISP_LINES) * DISP_LINES;
	d->setTextAlignment(TEXT_ALIGN_LEFT);
	for (uint8_t i = 0; i < DISP_LINES && first+i < items.size(); i++) {
		
		if (curr == first+i) {
			//d->getDisplay()->drawRect(SHIFT_X, SHIFT_Y + DELTA_Y*i, d->getDisplay()->getWidth() - SHIFT_X * 2, DELTA_Y);
			d->drawString(0, SHIFT_Y+DELTA_Y*i,">"+items.get(first+i)->getName());
		}
		else {
			
			d->drawString(SHIFT_X, SHIFT_Y + DELTA_Y*i, items.get(first + i)->getName());
		}

	}
	d->setTextAlignment(TEXT_ALIGN_RIGHT);
	if (first > 0)
	{
		d->drawString(d->getWidth() , SHIFT_Y, "/\\");
	}
	if (first + DISP_LINES < items.size()) {
		d->drawString(d->getWidth(), SHIFT_Y+DELTA_Y*(DISP_LINES-1), "\\/");
	}
}

void Menu::setParent(Menu * m)
{
	parent = m;
}

Menu * Menu::getParent()
{
	return parent;
}
