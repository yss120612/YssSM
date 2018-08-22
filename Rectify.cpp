#include "Rectify.h"

Rectify::Rectify(Aggregates * a, Hardware *h) : Mode(a, h)
{
	MyName = "Rectify";
	makeMenu();
}

Rectify::~Rectify()
{
	delete mcmd;
}

String Rectify::getData(uint w)
{

	if (w > DS_RECTSTART && w < DS_RECTEND) {
		switch (w) {
		case DS_RECTSTATE:
			switch (work_mode) {
			case PROC_OFF:
				return "OFF";
				break;
			case PROC_FORSAJ:
				return "FORSAJ";
				break;
			case PROC_WORK:
				return "WORKING";
				break;
			}

			//	break;
			//case DS_TTSA:
			//	return String(hardware->getTTSA()->getTemp(), 1);
			//	break;
		default:
			return "";
			break;
		}

	}
	else
	return Mode::getData(w);
}


void Rectify::showState()
{
}

void Rectify::process(long ms)
{
}

void Rectify::makeMenu()
{
	menu = new Menu();
	menu->setActive(true);
	mcmd = new MenuCommand("Start", 1);
	menu->add(mcmd);
	menu->add(new MenuCommand("Hide menu", 2));
	menu->add(new MenuCommand("Return", 3));
	Menu * setup = new Menu();
	setup->setParent(menu);
	setup->setActive(true);
	MenuIParameter * tFor = new MenuIParameter("T Forsaj", setup, 12);
	MenuFParameter * tEnd = new MenuFParameter("T End", setup, 13);
	MenuIParameter * pwWork = new MenuIParameter("WorkPower", setup, 14);
	MenuFParameter * pwKran = new MenuFParameter("OpenKran", setup, 15);
	setup->add(tFor);
	setup->add(tEnd);
	setup->add(pwWork);
	setup->add(pwKran);
	menu->add(new MenuSubmenu("Setup", setup));
}

void Rectify::command(MenuCommand * id)
{
	switch (id->getId()) {
	case 1:
		if (work_mode == PROC_OFF) {
			menu->setActive(false);
			start();
		}
		else {
			stop(PROCEND_MANUAL);
		}
		break;
	case 2:
		menu->setActive(false);
		break;
	case 3:
		if (work_mode != PROC_OFF)
		{
			stop(PROCEND_MANUAL);
		}
		workMode.setCurrent(MODE_MAIN);
		break;
	}
}

void Rectify::stop(uint8_t reason)
{
}

void Rectify::start()
{
}

void Rectify::initParams(MenuParameter * mp)
{
}

void Rectify::acceptParams(MenuParameter * mp)
{
}
