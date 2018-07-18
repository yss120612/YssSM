// 
// 
// 

#include "Mode.h"


Mode::Mode(Aggregates * a,Hardware * h)
{
	parent = NULL;
	agg = a;
	hardware = h;
	last_action = millis();
	ss_active = false;
}

void Mode::drawImm(long m)
{
	if (!drawImmed) return;
	draw(m);
	drawImmed = false;
}

void Mode::processMenuPress()
{
	MenuParameter * mp;
	if (menu->current()->getKind() == COMMAND) {
		command(menu->current()->getId());
	}
	else if (menu->current()->getKind() == SUBMENU) {
		menu = menu->current()->select();
	}
	else if (menu->current()->getKind() >= PARAMETRINT && menu->current()->getKind() <= PARAMETRSTR) {
		if (menu->isEditMode())
		{
			if (menu->getEditParams()->getNext() == NULL) {//следующего параметра нет. запоминаем...
				mp = menu->getEditParams();
				while (mp != NULL)
				{
					acceptParams(mp);
					mp = mp->getPrev();
				}
			}
			menu->setEditParams(menu->getEditParams()->getNext());
		}
		else
		{
			menu->setEditParams((MenuParameter *)(menu->current()));
		}
		initParams(menu->getEditParams());
	}
}

void Mode::processMenuChange(boolean isUp)
{
	if (menu->isEditMode()) {
		if (isUp)
		{
			menu->getEditParams()->up();
		}
		else {
			menu->getEditParams()->down();
		}
	}
	else {
		if (isUp) {
			menu->next();
		}
		else {
			menu->prev();
		}
	}
}

void Mode::processMenuLong()
{
	if (menu->isEditMode()) {
		menu->setEditParams(NULL);
	}
	else if (menu->getParent() != NULL) {
		menu = menu->getParent();
	}
	else {
		menu->setActive(false);
	}
}
