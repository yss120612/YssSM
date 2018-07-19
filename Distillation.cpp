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
}

void Distillation::initDraw()
{
}

void Distillation::left()
{
}

void Distillation::right()
{
}

void Distillation::press()
{
}

void Distillation::long_press()
{
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
