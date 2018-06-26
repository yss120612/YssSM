// 
// 
// 

#include "Main.h"

Main::Main(Hardware * h):Mode(h)
{
	makeMenu();
	menu.setActive(true);
}

char tim[9];
void Main::draw() {
	hardware->getDisplay()->getDisplay()->setTextAlignment(TEXT_ALIGN_LEFT);
	hardware->getDisplay()->getDisplay()->clear();
	hardware->getDisplay()->getDisplay()->drawString(0, 0, String(hardware->getTKube()->getTemp()));
	hardware->getClock()->readTime();
	sprintf(tim, "%02d:%02d:%02d", hardware->getClock()->h, hardware->getClock()->m, hardware->getClock()->s);
	hardware->getDisplay()->getDisplay()->drawString(60, 0, tim);

	if (menu.isActive()) {
		menu.display(hardware->getDisplay());
	}
	else {
		
		//hardware->getDisplay()->getDisplay()->drawString(0, 14, String(counter));

		hardware->getDisplay()->getDisplay()->drawString(0, 14, String(hardware->getHeater()->getPower()));
		//hardware->getDisplay()->getDisplay()->drawString(20, 14, "Dummy="+String(hardware->getHeater()->dummy));
		hardware->getDisplay()->getDisplay()->drawString(0, 28, "HeaterOn=" + String(hardware->getHeater()->isON()));
		hardware->getDisplay()->getDisplay()->drawString(0, 42, "Extender=" + String(hardware->getExtender()->getAll()));
		

	}
	hardware->getDisplay()->getDisplay()->display();
}


void Main::makeMenu()
{
	
	menu.add(new MenuCommand("Item0",3));
	menu.add(new MenuSubmenu("Item1", NULL));
	menu.add(new MenuSubmenu("Item2", NULL));
	menu.add(new MenuSubmenu("Item3", NULL));
	menu.add(new MenuSubmenu("Item4", NULL));
	menu.add(new MenuSubmenu("Item5", NULL));
	menu.add(new MenuSubmenu("Item6", NULL));
	menu.add(new MenuSubmenu("Item7", NULL));
	menu.add(new MenuSubmenu("Item8", NULL));
	menu.add(new MenuSubmenu("Item9", NULL));
}


//void Main::drawImm() {
//	if (!drawImmed) return;
//	draw();
//	drawImmed = false;
//}

void Main::left() {
#ifdef _SERIAL
	Serial.println("left in main");
#endif
	if (menu.isActive())
	{
		menu.prev();
	}
	else
	{
		hardware->getHeater()->setPower(hardware->getHeater()->getPower() - 1);
	}
	counter--;
	drawImmed = true;
}
void Main::right() {
#ifdef _SERIAL
	Serial.println("right in main");
#endif
	if (menu.isActive())
	{
		menu.next();
	}
	else {

		hardware->getHeater()->setPower(hardware->getHeater()->getPower() + 1);
	}
	counter++;
	drawImmed = true;
}

void Main::press() {
#ifdef _SERIAL
	Serial.println("press in main");
#endif
	/*if (!hardware->getHeater()->isON()) {
		hardware->getHeater()->start();
	}	else {
		hardware->getHeater()->stop();
	}*/
	//hardware->getBeeper()->beep(1000, 500);
	counter = 100;
	drawImmed = true;
	if (menu.isActive() && menu.current()->getKind() == 1) {
		
		command(((MenuCommand *)(menu.current()))->getId());

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
	drawImmed = true;
}

void Main::command(uint8_t id)
{
	if (id != 3) return;
	if (!hardware->getHeater()->isON()) {
		hardware->getHeater()->start();
	}
	else {
		hardware->getHeater()->stop();
	}
	drawImmed = true;
}
