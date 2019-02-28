// 
// 
// 

#include "Manual.h"


Manual::Manual(Aggregates * a, Hardware *h):Mode(a,h)
{
	MyName = "Manual";
	work_mode = PROC_OFF;
	makeMenu();
}

Manual::~Manual()
{
}

String Manual::getData(uint w)
{
	return Mode::getData(w);
}

void Manual::showState()
{
	uint8_t x;
	uint8_t y;
	if (ss_active) {
		x = rand() % 40;
		y = 0;
	}
	else {
		x = 0;
		y = 0;
	}
	hardware->getDisplay()->drawString(x, 0, "Manual"+String(work_mode==PROC_OFF?"-":"+"));
	//hardware->getDisplay()->drawString(x, y + 13, "Kran=" + String(agg->getKran()->getState(),1));
	hardware->getDisplay()->drawString(x, y + 13, "Tk=" + String(hardware->getTKube()->getTemp(), 1));
	hardware->getDisplay()->drawString(x, y + 29, "PUMP=" + String(hardware->getPump()->isWorking()?"ON":"OFF"));
	hardware->getDisplay()->drawString(x, y+45, "PW=" + String(agg->getHeater()->getPower()));
}

void Manual::process(long ms)
{
	if (work_mode == PROC_OFF) return;
	if (last_time + test_time - ms > 0) return;
	last_time = ms;
	volatile float tcube = hardware->getTKube()->getTemp();
	if (tcube > 31) {
		work_mode = PROC_OFF;
		mTest->setName("Test on");
		hardware->getBeeper()->beep(1000, 5000);
		logg.logging("Test complete on temperature T="+String(hardware->getTKube()->getTemp(),2) +" Tv="+ String(tcube, 2));
	}
	else {
		logg.logging("Test on progress on temperature T=" + String(hardware->getTKube()->getTemp(), 2) + " Tv=" + String(tcube, 2));
	}

}

void Manual::makeMenu()
{
	menu = new Menu();
	menu->setActive(true);
	mKran = new MenuCommand("Kran open", 1);
	menu->add(mKran);
	mHeater = new MenuCommand("Heater On", 2);
	menu->add(mHeater);
	mPump = new MenuCommand("Pump On", 3);
	menu->add(mPump);
	mTest= new MenuCommand("Test On", 4);
	menu->add(mTest);
	menu->add(new MenuCommand("Return", 100));
	Menu * setup = new Menu();
		setup->setParent(menu);
		setup->setActive(true);
		MenuIParameter * pwWork = new MenuIParameter("Power", setup, 10);
		MenuFParameter * pwKran = new MenuFParameter("Kran", setup, 11);
		setup->add(pwWork);
		setup->add(pwKran);
		menu->add(new MenuSubmenu("Setup", setup));
}

void Manual::command(MenuCommand * id)
{
	float tsa;
	switch (id->getId()) {
	case 1:
		if (agg->getKran()->getState() > 0) {
			agg->getKran()->close();
			mKran->setName("Kran open");
		}
		else {
			agg->getKran()->openQuantum(CONF.getManualKranOpened());
			mKran->setName("Kran close");
			menu->setActive(false);
		}
		break;
	case 2:
		if (agg->getHeater()->isON()) {
			agg->getHeater()->stop();
			mHeater->setName("Heater on");
		}
		else {
			agg->getHeater()->start();
			agg->getHeater()->setPower(CONF.getManualWorkPower());
			mHeater->setName("Heater off");
			menu->setActive(false);
		}
		break;
	case 3:
		if (hardware->getPump()->isWorking()) {
			hardware->getPump()->stop();
			mPump->setName("Pump on");
		}
		else {
			hardware->getPump()->start();
			mPump->setName("Pump off");
			menu->setActive(false);
		}
		break;
	case 4:
		if (work_mode == PROC_OFF) {
			work_mode = PROC_TEST;
			mTest->setName("Test off");
		}
		else {
			work_mode = PROC_OFF;
			mTest->setName("Test on");
		}
		menu->setActive(false);
		break;
	case 100:
		stopAll();
		workMode.setCurrent(MODE_MAIN);
		break;
	}

}


void Manual::stopAll() {
	hardware->getPump()->stop();
	agg->getHeater()->setPower(0);
	agg->getHeater()->stop();
	agg->getKran()->forceClose();
	work_mode = PROC_OFF;

}

void Manual::initParams(MenuParameter * mp)
{
	if (mp == NULL) return;
	switch (mp->getId()) {
	case 10:
		((MenuIParameter *)mp)->setup(CONF.getManualWorkPower(), 1, 20, 100);
		break;
	case 11:
		((MenuFParameter *)mp)->setup(CONF.getManualKranOpened(), 0.2, 15, 80);
		break;
	
	}
}

void Manual::acceptParams(MenuParameter * mp)
{
	if (mp == NULL) return;
	switch (mp->getId())
	{
	case 10:
		CONF.setManualWorkPower(((MenuIParameter *)mp)->getCurrent());
		if (agg->getHeater()->isON()) {
			agg->getHeater()->setPower(CONF.getManualWorkPower());
		}
		break;
	case 11:
		CONF.setManualKranOpened(((MenuFParameter *)mp)->getCurrent());
		if ((agg->getKran()->getState() > 0)) {
			agg->getKran()->openQuantum(CONF.getManualKranOpened());
		}
		break;
	}
}
