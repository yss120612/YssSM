// 
// 
// 

#include "Distillation.h"


Distillation::Distillation(Aggregates * a, Hardware *h) : Mode(a,h)
{
	makeMenu();
}

Distillation::~Distillation()
{
}

void Distillation::draw(long m)
{
	hardware->getDisplay()->clear();
	hardware->getDisplay()->setTextAlignment(TEXT_ALIGN_LEFT);
	if (ss_active || m - last_action > CONF.getScrSavMin() * 60000) {
		ss_active = true;
		showState();
	}
	else {

		if (menu != NULL && menu->isActive()) {
			hardware->getDisplay()->drawString(0, 0, "Distillation");
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

void Distillation::initDraw()
{
	last_action = millis();
	ss_active = false;
}

void Distillation::showState()
{
	uint8_t x;
	uint8_t y;
	if (ss_active) {
		x = rand()%40;
		y = 0;
	}
	else {
		x = 0;
		y = 0;
	}
	hardware->getDisplay()->drawString(x, 0, "Distill");

	hardware->getDisplay()->drawString(x, y+13, "TSA="+String(hardware->getTTSA()->getTemp()));
	hardware->getDisplay()->drawString(x, y+29, "DEF=" + String(hardware->getTTsarga()->getTemp()));
	hardware->getDisplay()->drawString(x, y+45, "KUB=" + String(hardware->getTKube()->getTemp()));
	
}

void Distillation::process(long ms) {

}

void Distillation::left()
{
	Mode::left();
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

		  //hardware->getHeater()->setPower(hardware->getHeater()->getPower() + 1);
	}
	drawImmed = true;
}

void Distillation::right()
{
	Mode::right();
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

		  //hardware->getHeater()->setPower(hardware->getHeater()->getPower() + 1);
	}
	drawImmed = true;
}

void Distillation::press()
{
	Mode::press();
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


	}
	drawImmed = true;
}

void Distillation::long_press()
{
	Mode::long_press();
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

void Distillation::makeMenu()
{
	menu = new Menu();
	menu->setActive(true);
	menu->add(new MenuCommand("Start", 1));
	menu->add(new MenuCommand("Stop", 2));
	menu->add(new MenuCommand("Return", 3));
	Menu * setup = new Menu();
	setup->setParent(menu);
	setup->setActive(true);
	MenuIParameter * iHo = new MenuIParameter("Duration;Hours", setup, 10);
	MenuIParameter * iMi = new MenuIParameter("Minutes", setup, 11);
	iHo->setNext(iMi);
	setup->add(iHo);
	MenuIParameter * iTm = new MenuIParameter("Temp-ra;Temperature", setup, 12);
	setup->add(iTm);
	menu->add(new MenuSubmenu("Setup", setup));
}

void Distillation::command(uint8_t id)
{
	switch (id) {
	case 1:
		if (work_mode != PROC_OFF) return;
		menu->setActive(false);
		start();
		break;
	case 2:
		if (work_mode == PROC_OFF) return;
		stop(PROCEND_MANUAL);
		break;
	case 3:
		stop(PROCEND_MANUAL);
		workMode.setCurrent(MODE_MAIN);
		break;
	}
}

void Distillation::stop(uint8_t reason) {

}

void Distillation::start() {

}

void Distillation::initParams(MenuParameter * mp)
{
}

void Distillation::acceptParams(MenuParameter * mp)
{
}
