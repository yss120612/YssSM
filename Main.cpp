#include "Main.h"


Main::Main(Aggregates * a,Hardware * h):Mode(a,h)
{
	makeMenu();
}

char tim[9];
void Main::initDraw() {
	hardware->getDisplay()->init();
	hardware->getDisplay()->flipScreenVertically();
	hardware->getDisplay()->setFont(ArialMT_Plain_16);
	hardware->getDisplay()->flipScreenVertically();
}

void Main::draw(long m) {
	hardware->getDisplay()->clear();
	hardware->getClock()->readTime();
	sprintf(tim, "%02d:%02d:%02d", hardware->getClock()->h, hardware->getClock()->m, hardware->getClock()->s);
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
	hardware->getDisplay()->drawString(0, 0, String(hardware->getTKube()->getTemp()));
	hardware->getDisplay()->drawString(60, 0, tim);
	
	if (menu != NULL)
	{
	
	if (menu->isActive()) {
		if (menu->isEditMode()) {
			hardware->getDisplay()->drawString(0, hardware->getDisplay()->getHeight() / 2, menu->getEditParams()->getMyName() + " : " + menu->getEditParams()->getStCurr());
		}
		else {
			menu->display(hardware->getDisplay());
		}
	}
	}	

	}//NOT SCREEN SAVER

	hardware->getDisplay()->display();
}

void Main::makeMenu()
{
	menu = new Menu();
	menu->setActive(true);
	menu->add(new MenuCommand("Suvid",1));
	menu->add(new MenuCommand("Brewing",2));
	menu->add(new MenuCommand("Distill",3));
	menu->add(new MenuCommand("Rectify",4));
		Menu * setup = new Menu();
		setup->setParent(menu);
		setup->setActive(true);

		MenuIParameter * iDay = new MenuIParameter("Date;Day", setup, 40);
		MenuIParameter * iMon = new MenuIParameter("Month", setup, 41);
		MenuIParameter * iYe = new MenuIParameter("Year", setup, 42);
		iDay->setNext(iMon);
		iMon->setNext(iYe);
		setup->add(iDay);

		//setup->add(new MenuCommand("Date", 11));
		
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
			//Menu * triak = new Menu();
			//triak->setParent(setup);
			//triak->setActive(true);
			

		//triak->add(new MenuCommand("Gisteresis", 22));
		//setup->add(new MenuSubmenu("Triak", triak));
	menu->add(new MenuSubmenu("Setup", setup));
}

void Main::left() {
	Mode::left();
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
	logg.logging("left in main");

	//agg->getHeater()->setPower(agg->getHeater()->getPower() - 1);
	//agg->getKran()->shiftQuantum(-1);
	
	if (menu->isActive())
	{
		processMenuChange(false);
	}
	else
	{// MENU IS NOT ACTIVE
		//hardware->getHeater()->setPower(hardware->getHeater()->getPower() - 1);
	}
	drawImmed = true;
}

void Main::right() {
	Mode::right();
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
	logg.logging("right in main");
	//agg->getHeater()->setPower(agg->getHeater()->getPower() + 1);
	//agg->getKran()->shiftQuantum(1);
	
	if (menu->isActive())
	{
		processMenuChange(true);
	}
	else {//MENU IS NOT ACTIVE

		//hardware->getHeater()->setPower(hardware->getHeater()->getPower() + 1);
	}
	drawImmed = true;
}

void Main::press() {
	Mode::press();
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
	logg.logging("press in main");
	
	if (menu->isActive())
	{
		processMenuPress();
	}
	else {//MENU IS NOT ACTIVE

		  //if (!agg->getHeater()->isON()) {
		  //	agg->getHeater()->start();
		  //}	else {
		  //	agg->getHeater()->stop();
		  //}
		  ////hardware->getBeeper()->beep(1000, 500);
		  ////counter = 100;
		  //drawImmed = true;
		  //agg->getKran()->close();
	}
	drawImmed = true;
}

void Main::long_press() {
	Mode::long_press();
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
	logg.logging("long press in main");
	
	if (menu->isActive())
	{
		processMenuLong();
	}
	else{
		menu->setActive(true);
	}
	drawImmed = true;
}

void Main::initParams(MenuParameter * mp) {
	if (mp == NULL) return;
	switch (mp->getId()) {
	case 21:
		((MenuIParameter *)mp)->setup(agg->getTCooler()->getTemperature(), 1,10,100);
		break;
	case 22:
		((MenuIParameter *)mp)->setup(agg->getTCooler()->getGesteresis(), 1, 0, 20);
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
		agg->getTCooler()->setParams(((MenuIParameter *)mp->getPrev())->getCurrent(), ((MenuIParameter *)mp)->getCurrent());
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

void Main::command(uint8_t id)
{


	/*if (id != 3) return;
	if (!hardware->getHeater()->isON()) {
		hardware->getHeater()->start();
	}
	else {
		hardware->getHeater()->stop();
	}*/

	drawImmed = true;
}



