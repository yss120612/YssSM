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

void Main::draw() {
	hardware->getDisplay()->clear();
	hardware->getDisplay()->setTextAlignment(TEXT_ALIGN_LEFT);
	hardware->getDisplay()->drawString(0, 0, String(hardware->getTKube()->getTemp()));
	hardware->getClock()->readTime();
	sprintf(tim, "%02d:%02d:%02d", hardware->getClock()->h, hardware->getClock()->m, hardware->getClock()->s);
	hardware->getDisplay()->drawString(60, 0, tim);
	
	if (menu != NULL)
	{
	
	if (menu->isActive()) {
		if (menu->isEditMode()) {
			hardware->getDisplay()->drawString(0, hardware->getDisplay()->getHeight() / 2, menu->getEditParams()->getName() + " : " + menu->getEditParams()->getStCurr());
		}
		else {
			menu->display(hardware->getDisplay());
		}
	}

	//else{
	//	
	//	//hardware->getDisplay()->getDisplay()->drawString(0, 14, String(counter));

		//hardware->getDisplay()->getDisplay()->drawString(0, 14, String(hardware->getHeater()->getPower()));
	//	//hardware->getDisplay()->getDisplay()->drawString(20, 14, "Dummy="+String(hardware->getHeater()->dummy));
	}	
	//hardware->getDisplay()->getDisplay()->drawString(20, 14, "Counter="+String(counter));
	//	hardware->getDisplay()->getDisplay()->drawString(0, 28, "HeaterOn=" + String(hardware->getHeater()->isON()));
	//	hardware->getDisplay()->getDisplay()->drawString(0, 42, "Extender=" + String(hardware->getExtender()->getAll()));
	//	

	//}
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

		MenuIParameter * iDay = new MenuIParameter("Day", setup, 40);
		iDay->setup(1, 1, 1, 31);
		MenuIParameter * iMon = new MenuIParameter("Month", setup, 41);
		iMon->setup(1, 1, 1, 12);
		MenuIParameter * iYe = new MenuIParameter("Year", setup, 42);
		iYe->setup(2010, 1, 2010, 2050);
		iDay->setNext(iMon);
		iMon->setNext(iYe);
		setup->add(iDay);

		//setup->add(new MenuCommand("Date", 11));
		
		MenuIParameter * iHour = new MenuIParameter("Hour", setup, 30);
		iHour->setup(0, 1, 0, 23);
		MenuIParameter * iMin = new MenuIParameter("Min", setup, 31);
		iMin->setup(0, 1, 0, 59);
		MenuIParameter * iSec = new MenuIParameter("Sec", setup, 32);
		iSec->setup(0, 1, 0, 59);
		iHour->setNext(iMin);
		iMin->setNext(iSec);
		setup->add(iHour);

		setup->add(new MenuCommand("T Cube", 13));
			Menu * triak = new Menu();
			triak->setParent(setup);
			triak->setActive(true);
			MenuIParameter * iPar = new MenuIParameter("Temperature", triak, 21);
			iPar->setup(30, 1, 20, 100);
			triak->add(iPar);
			triak->add(new MenuCommand("Gisteresis", 22));
		setup->add(new MenuSubmenu("Triak", triak));
	menu->add(new MenuSubmenu("Setup", setup));
}

void Main::left() {
	logg.logging("left in main");

	//agg->getHeater()->setPower(agg->getHeater()->getPower() - 1);
	//agg->getKran()->shiftQuantum(-1);
	
	if (menu->isActive())
	{
		if (menu->isEditMode()) {
			menu->getEditParams()->down();
		}
		else {
			menu->prev();
		}
	}
	else
	{// MENU IS NOT ACTIVE
		//hardware->getHeater()->setPower(hardware->getHeater()->getPower() - 1);
	}
	drawImmed = true;
}

void Main::right() {
	logg.logging("right in main");
	//agg->getHeater()->setPower(agg->getHeater()->getPower() + 1);
	//agg->getKran()->shiftQuantum(1);
	
	if (menu->isActive())
	{
		if (menu->isEditMode()) {
			menu->getEditParams()->up();
		}
		else {
			menu->next();
		}
	}
	else {//MENU IS NOT ACTIVE

		//hardware->getHeater()->setPower(hardware->getHeater()->getPower() + 1);
	}
	drawImmed = true;
}

void Main::press() {
	logg.logging("press in main");
	MenuParameter * mp;
	if (menu->isActive())
	{
		if (menu->current()->getKind() == COMMAND) {
			command(((MenuCommand *)(menu->current()))->getId());
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
						switch (mp->getId())
						{
						case 21:
							agg->getTCooler()->setParams(((MenuIParameter *)mp)->getCurrent(), 1);
							break;
						case 22:
							break;
						case 30:
							RTC.readTime();
							RTC.h = ((MenuIParameter *)mp)->getCurrent();
							break;
						case 31:
							RTC.m = ((MenuIParameter *)mp)->getCurrent();
							break;
						case 32:
							RTC.s = ((MenuIParameter *)mp)->getCurrent();
							RTC.writeTime();
							break;
						case 40:
							RTC.readTime();
							RTC.dd = ((MenuIParameter *)mp)->getCurrent();
							break;
						case 41:
							RTC.mm = ((MenuIParameter *)mp)->getCurrent();
							break;
						case 42:
							RTC.yyyy = ((MenuIParameter *)mp)->getCurrent();
							RTC.writeTime();
							break;
						default:
							break;
						}
						mp = mp->getPrev();
					}
				}
				menu->setEditParams(menu->getEditParams()->getNext());
			}
			else 
			{
				menu->setEditParams((MenuParameter *)(menu->current()));
			}
			
		}
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
			
}

void Main::long_press() {
	logg.logging("long press in main");
	counter = 0;
	if (menu->isActive())
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
	else{
		menu->setActive(true);
	}
	drawImmed = true;
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

void Main::params(uint8_t id)
{
	
	if (id == 21) {

	}
	/*if (id != 3) return;
	if (!hardware->getHeater()->isON()) {
	hardware->getHeater()->start();
	}
	else {
	hardware->getHeater()->stop();
	}*/

	drawImmed = true;
}

