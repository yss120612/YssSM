#include "Main.h"


Main::Main(Aggregates * a,Hardware * h):Mode(a,h)
{
	makeMenu();
}



void Main::initDraw() {
	hardware->getDisplay()->init();
	//hardware->getDisplay()->flipScreenVertically();
	hardware->getDisplay()->setFont(ArialMT_Plain_16);
	hardware->getDisplay()->flipScreenVertically();
	last_action = millis();
	ss_active = false;
}

void Main::draw(long m) {
	hardware->getDisplay()->clear();
	readTime();//update tim 
	hardware->getDisplay()->setTextAlignment(TEXT_ALIGN_LEFT);
	if (ss_active || m - last_action > CONF.getScrSavMin()*60000) {
		ss_active = true;
		//int x = rand() % (hardware->getDisplay()->width() - 10);
		//int y = 13 + rand() % (hardware->getDisplay()->height() - 26);
		hardware->getDisplay()->drawString(rand() % (80), 0, "Main...");
		hardware->getDisplay()->drawString(rand() % (65), 13 + rand() % (hardware->getDisplay()->height() - 27), tim);
	}//SCREEN SAVER
	else 
	{
	hardware->getDisplay()->drawString(0, 0, String(hardware->getTTSA()->getTemp()));
	hardware->getDisplay()->drawString(60, 0, tim);
	
	
	
	if (menu != NULL && menu->isActive()) {
		if (menu->isEditMode()) {
			hardware->getDisplay()->drawString(0, hardware->getDisplay()->getHeight() / 2, menu->getEditParams()->getMyName() + " : " + menu->getEditParams()->getStCurr());
		}
		else {
			menu->display(hardware->getDisplay());
		}
	}
		

	}//NOT SCREEN SAVER

	hardware->getDisplay()->display();
}

void Main::showState() {

}

void Main::makeMenu()
{
	menu = new Menu();
	menu->setActive(true);
	//menu->add(new MenuCommand("Suvid",1));
	menu->add(new MenuCommand("Brewing",2));
	menu->add(new MenuCommand("Distill",3));
	menu->add(new MenuCommand("Rectify",4));
	menu->add(new MenuCommand("Manual", 5));
	menu->add(new MenuCommand("Beep1", 6));
	menu->add(new MenuCommand("Beep2", 7));
		Menu * setup = new Menu();
		setup->setParent(menu);
		setup->setActive(true);

		MenuIParameter * iDay = new MenuIParameter("Date;Day", setup, 40);
		MenuIParameter * iMon = new MenuIParameter("Month", setup, 41);
		MenuIParameter * iYe = new MenuIParameter("Year", setup, 42);
		iDay->setNext(iMon);
		iMon->setNext(iYe);
		setup->add(iDay);

		setup->add(new MenuCommand("1Wire dev", 11));
		setup->add(new MenuCommand("i2c dev", 12));
		
		MenuIParameter * iHour = new MenuIParameter("Time;Hour", setup, 30);
		MenuIParameter * iMin = new MenuIParameter("Min", setup, 31);
		MenuIParameter * iSec = new MenuIParameter("Sec", setup, 32);
		iHour->setNext(iMin);
		iMin->setNext(iSec);
		setup->add(iHour);

		setup->add(new MenuCommand("T Cube", 13));

		MenuIParameter * iTemp = new MenuIParameter("Triak;Temperature", setup, 21);
		MenuIParameter * iGis = new MenuIParameter("Gisteresis", setup, 22);
		iTemp->setNext(iGis);
		setup->add(iTemp);

		MenuIParameter * miTsa = new MenuIParameter("TSA;Minimum", setup, 23);
		MenuIParameter * maTsa = new MenuIParameter("Maximum", setup, 24);
		MenuIParameter * cTsa = new MenuIParameter("Critical", setup, 25);
		miTsa->setNext(maTsa);
		maTsa->setNext(cTsa);
		setup->add(miTsa);
			//Menu * triak = new Menu();
			//triak->setParent(setup);
			//triak->setActive(true);
			

		//triak->add(new MenuCommand("Gisteresis", 22));
		//setup->add(new MenuSubmenu("Triak", triak));
	menu->add(new MenuSubmenu("Setup", setup));
}


void Main::initParams(MenuParameter * mp) {
	if (mp == NULL) return;
	switch (mp->getId()) {
	case 21:
		((MenuIParameter *)mp)->setup(CONF.getTriakCoolerTemp(), 1, 10, 100);
		break;
	case 22:
		((MenuIParameter *)mp)->setup(CONF.getTriakCoolerGist(), 1, 0, 20);
		break;
	case 23:
		((MenuIParameter *)mp)->setup(CONF.getTSAmin(), 1, 20, 50);
		break;
	case 24:
		((MenuIParameter *)mp)->setup(CONF.getTSAmax(), 1, 20, 80);
		break;
	case 25:
		((MenuIParameter *)mp)->setup(CONF.getTSAcritical(), 1, 40, 99);
		break;
	
	case 30:
		RTC.readTime();
		((MenuIParameter *)mp)->setup(RTC.h, 1, 0, 23);
		break;
	case 31:
		RTC.readTime();
		((MenuIParameter *)mp)->setup(RTC.m, 1, 0, 59);
		break;
	case 32:
		RTC.readTime();
		((MenuIParameter *)mp)->setup(RTC.s, 1, 0, 59);
		break;
	case 40:
		RTC.readTime();
		((MenuIParameter *)mp)->setup(RTC.dd, 1, 1, 31);
		break;
	case 41:
		RTC.readTime();
		((MenuIParameter *)mp)->setup(RTC.mm, 1, 1, 12);
		break;
	case 42:
		RTC.readTime();
		((MenuIParameter *)mp)->setup(RTC.yyyy, 1, 2010, 2030);
		break;

	}
}

void Main::acceptParams(MenuParameter * mp) {
	if (mp == NULL) return;
	switch (mp->getId())
	{
	case 21:
		break;
	case 22:
		CONF.setTriakCoolerTemp(((MenuIParameter *)mp->getPrev())->getCurrent());
		CONF.setTriakCoolerGist(((MenuIParameter *)mp)->getCurrent());
		break;
	case 23:
		break;
	case 24:
		break;
	case 25:
		CONF.setTSAmin(((MenuIParameter *)mp->getPrev()->getPrev())->getCurrent());
		CONF.setTSAmax(((MenuIParameter *)mp->getPrev())->getCurrent());
		CONF.setTSAcritical(((MenuIParameter *)mp)->getCurrent());
		break;

	case 30:
		break;
	case 31:
		break;
	case 32:
		RTC.readTime();
		RTC.h = ((MenuIParameter *)mp->getPrev()->getPrev())->getCurrent();
		RTC.m = ((MenuIParameter *)mp->getPrev())->getCurrent();
		RTC.s = ((MenuIParameter *)mp)->getCurrent();
		RTC.writeTime();
		break;
	case 40:
		break;
	case 41:
		break;
	case 42:
		RTC.readTime();
		RTC.dd = ((MenuIParameter *)mp->getPrev()->getPrev())->getCurrent();
		RTC.mm = ((MenuIParameter *)mp->getPrev())->getCurrent();
		RTC.yyyy = ((MenuIParameter *)mp)->getCurrent();
		RTC.writeTime();
		break;
	default:
		break;
	}
}

void Main::command(MenuCommand * id)
{
	String result = "";
	uint8_t i;
	switch (id->getId()) {
	//case 1:
		//workMode.setCurrent(MODE_SUVID);
	//	break;
	case 2:
		workMode.setCurrent(MODE_BREWING);
		break;
	case 3:
		workMode.setCurrent(MODE_DISTILL);
		break;
	case 4:
		workMode.setCurrent(MODE_RECTIFY);
		break;
	case 5:
		workMode.setCurrent(MODE_MANUAL);
		break;
	case 6:
		hardware->getBeeper()->beep(1000, 5000);
		break;
	case 7:
		hardware->getBeeper()->beep(3000, 5000);
		break;
	case 11:
		logg.logging("begin of OneWire devices");
		logg.logging(hardware->owDevices());
		logg.logging("end of OneWire devices");
		break;
	case 12:
		logg.logging("begin of i2c devices");
		logg.logging(hardware->i2cDevices());
		logg.logging("end of i2c devices");
		break;
	}

	drawImmed = true;
}



