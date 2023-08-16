#include "Mode.h"

void Mode::left()
{
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
#ifdef ENCODER_LOG
	logg.logging("Distillation left");
#endif
	if (menu->isActive())
	{
		processMenuChange(false);
	}
	else {//MENU IS NOT ACTIVE
		left_nomenu();
		  //hardware->getHeater()->setPower(hardware->getHeater()->getPower() + 1);
	}
	drawImmed = true;
}

void Mode::right()
{
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
#ifdef ENCODER_LOG
	logg.logging("Distillation right");
#endif

	if (menu->isActive())
	{
		processMenuChange(true);
	}
	else {//MENU IS NOT ACTIVE

		right_nomenu();
	}
	drawImmed = true;
}

void Mode::press()
{
	if (hardware->getBeeper()->isOn()) hardware->getBeeper()->stop();
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
#ifdef ENCODER_LOG
	logg.logging("Distillation press");
#endif

	if (menu->isActive())
	{
		processMenuPress();
	}
	else {//MENU IS NOT ACTIVE
		press_nomenu();

	}
	drawImmed = true;
}

void Mode::long_press()
{
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
#ifdef ENCODER_LOG
	logg.logging("Distillation long_press");
#endif
	if (menu->isActive()) {
		processMenuLong();
	}
	else {
		menu->setActive(true);
	}
}

Mode::Mode(Aggregates * a,Hardware * h)
{
	parent = NULL;
	agg = a;
	hardware = h;
}

Mode::~Mode()
{
	delete menu;
}

void Mode::draw(long m)
{
	hardware->getDisplay()->clear();
	hardware->getDisplay()->setTextAlignment(TEXT_ALIGN_LEFT);

	if (ss_active || m - last_action > CONF.getScrSavMin() * 60000) //активный савер
	{
		ss_active = true;
		showState();
	}
	else
	{
		if (menu != NULL && menu->isActive()) {
			hardware->getDisplay()->drawString(0, 0, MyName);
			if (menu->isEditMode()) {
				hardware->getDisplay()->drawString(0, hardware->getDisplay()->getHeight() / 2, menu->getEditParams()->getMyName() + " : " + menu->getEditParams()->getStCurr());
			}
			else {
				menu->display(hardware->getDisplay());
			}
		}
		else
		{
			showState();
		}
	}
	hardware->getDisplay()->display();
}

void Mode::initDraw()
{
	last_action = millis();
	ss_active = false;
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

String Mode::getTimeStr() {
	readTime();
	return String(tim);
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
		if (menu->isEditMode()) initParams(menu->getEditParams());
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
	case DS_WSUROVEN:
		return String(hardware->getUrovenWS()->getValue());
		break;
	case DS_WSFLOOD:
		return String(hardware->getFloodWS()->getValue());
		break;
	default:
		return "NO DATA";
		break;
	}
}

void Mode::setData(uint w, String ds)
{
}
