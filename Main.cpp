#include "Main.h"

Main::Main(Hardware * h):Mode(h)
{
	makeMenu();
}

char tim[9];

void Main::draw() {
	hardware->getDisplay()->getDisplay()->clear();
	hardware->getDisp()->setTextAlignment(TEXT_ALIGN_LEFT);
	hardware->getDisplay()->getDisplay()->drawString(0, 0, String(hardware->getTKube()->getTemp()));
	hardware->getClock()->readTime();
	sprintf(tim, "%02d:%02d:%02d", hardware->getClock()->h, hardware->getClock()->m, hardware->getClock()->s);
	hardware->getDisplay()->getDisplay()->drawString(60, 0, tim);
	
	if (menu != NULL)
	{
	
	if (menu->isActive()) {
		menu->display(hardware->getDisplay());
	}
	else if (menu->getEditParams() != NULL) {
		hardware->getDisp()->drawString(0, hardware->getDisp()->getHeight()/2, menu->getEditParams()->getName()+" : "+menu->getEditParams()->getStCurr());
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
	hardware->getDisplay()->getDisplay()->display();
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
		setup->add(new MenuCommand("Date/Time", 11));
		setup->add(new MenuCommand("T Cube", 12));
			Menu * triak = new Menu();
			triak->setParent(setup);
			triak->setActive(true);
			MenuIParameter * iPar = new MenuIParameter("Temperature", triak, 21, 30);
			iPar->setup(1, 20, 100);
			triak->add(iPar);
			triak->add(new MenuCommand("Gisteresis", 22));
		setup->add(new MenuSubmenu("Triak", triak));
	menu->add(new MenuSubmenu("Setup", setup));
}

void Main::left() {
#ifdef _SERIAL
	Serial.println("left in main");
#endif
	hardware->getHeater()->setPower(hardware->getHeater()->getPower() - 1);
	hardware->getKran()->shiftQuantum(-1);
	return;
	if (menu->isActive())
	{
		menu->prev();
	}
	else if (menu->getEditParams() != NULL) {
		menu->getEditParams()->down();
	}
	else
	{
		//hardware->getHeater()->setPower(hardware->getHeater()->getPower() - 1);
	}
	//counter--;
	drawImmed = true;
}

void Main::right() {
#ifdef _SERIAL
	Serial.println("right in main");
#endif
	hardware->getHeater()->setPower(hardware->getHeater()->getPower() + 1);
	hardware->getKran()->shiftQuantum(1);
	return;
	if (menu->isActive())
	{
		menu->next();
	}
	else if (menu->getEditParams() != NULL) {
		menu->getEditParams()->up();
	}
	else {

		//hardware->getHeater()->setPower(hardware->getHeater()->getPower() + 1);
	}
	//counter++;
	drawImmed = true;
}

void Main::press() {
#ifdef _SERIAL
	Serial.println("press in main");
#endif
	if (!hardware->getHeater()->isON()) {
		hardware->getHeater()->start();
	}	else {
		hardware->getHeater()->stop();
	}
	//hardware->getBeeper()->beep(1000, 500);
	//counter = 100;
	drawImmed = true;
	hardware->getKran()->close();
	return;
	if (menu->isActive())
	{
		if (menu->current()->getKind() == 1) {
			command(((MenuCommand *)(menu->current()))->getId());
		}
		else if (menu->current()->getKind() == 2) {
			menu = menu->current()->select();
		}
		else if (menu->current()->getKind() == 3) {
			

			menu->setActive(false);
			//params(((MenuIParameter *)(menu->current()))->getId());
			menu->setEditParams((MenuParameter *)(menu->current()));
		}
	}
	else if (menu->getEditParams()!=NULL) {
		switch (menu->getEditParams()->getId())
		{
			case 21:
				hardware->getTCooler()->setParams(((MenuIParameter *)menu->getEditParams())->getCurrent(), 1);
				break;
			case 22:
				break;
		}
		if (menu->getEditParams()->next())
		{
			menu->setActive(true);
		}
	}
	//digitalWrite(D6, !digitalRead(D6));
	//digitalWrite(D7, !digitalRead(D7));
	//digitalWrite(D8, !digitalRead(D8));
	//if (hardware->getExtender()->getAll() > 0)
	//{
		//hardware->getExtender()->setAll(0);
	//}
	//else {
		//hardware->getExtender()->setAll(0xFFFF);
	//}
	
	
}

void Main::long_press() {
#ifdef _SERIAL
	Serial.println("long_press in main");
#endif
	counter = 0;
	if (menu->isActive())
	{
		if (menu->getParent() != NULL) menu = menu->getParent();
	}
	else if (menu->current()->getKind() == 3) {
		menu->setActive(true);
		//params(((MenuIParameter *)(menu->current()))->getId());
		//menu->setEditParams((MenuParameter *)(menu->current()));
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

