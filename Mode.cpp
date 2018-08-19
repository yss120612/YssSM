// 
// 
// 

#include "Mode.h"


Mode::Mode(Aggregates * a,Hardware * h)
{
	parent = NULL;
	agg = a;
	hardware = h;
	
}

void Mode::drawImm(long m)
{
	if (!drawImmed) return;
	draw(m);
	drawImmed = false;
}

void Mode::readTime() {
	hardware->getClock()->readTime();
	sprintf(tim, "%02d:%02d:%02d", hardware->getClock()->h, hardware->getClock()->m, hardware->getClock()->s);
}

void Mode::processMenuPress()
{
	MenuParameter * mp;
	if (menu->current()->getKind() == COMMAND) {
		command((MenuCommand *)menu->current());
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

String Mode::getData(uint w)
{
	switch (w) {
	case DS_TKUBE:
		return String(hardware->getTKube()->getTemp(), 1);
		break;
	case DS_TTSA:
		return String(hardware->getTTSA()->getTemp(), 1);
		break;
	case DS_TTSARGA:
		return String(hardware->getTTsarga()->getTemp(), 1);
		break;
	case DS_TTRIAK:
		return String(hardware->getTTriak()->getTemp(), 1);
	break;
	case DS_HPOWER:
		return String(agg->getHeater()->getPower());
	break;
	case DS_KRANSTATE:
		return String(agg->getKran()->getState(),1);
	break;
	default:
		return "NO DATA";
		break;
	}
}
