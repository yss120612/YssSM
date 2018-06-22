// 
// 
// 

#include "Main.h"

Main::Main(Hardware * h):Mode(h)
{
}

char tim[9];
void Main::draw() {
	hardware->getClock()->readTime();
	sprintf(tim, "%02d:%02d:%02d", hardware->getClock()->h, hardware->getClock()->m, hardware->getClock()->s);
	hardware->getDisplay()->getDisplay()-> clear();
	hardware->getDisplay()->getDisplay()->drawString(0, 0, String(hardware->getTKube()->getTemp()));
	//hardware->getDisplay()->getDisplay()->drawString(0, 14, String(counter));
	hardware->getDisplay()->getDisplay()->drawString(60, 0, tim);
	//hardware->getDisplay()->getDisplay()->drawString(0, 14, String(hardware->getHeater()->getPower()));
	hardware->getDisplay()->getDisplay()->drawString(20, 14, "Dummy="+String(hardware->getHeater()->dummy));
	hardware->getDisplay()->getDisplay()->drawString(0, 28, "HeaterOn=" + String(hardware->getHeater()->isON()));
	hardware->getDisplay()->getDisplay()->drawString(0, 42, "Extender=" + String(hardware->getExtender()->getAll()));
	hardware->getDisplay()->getDisplay()->display();

	
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
	hardware->getHeater()->setPower(hardware->getHeater()->getPower() - 1);
	counter--;
	drawImmed = true;
}
void Main::right() {
#ifdef _SERIAL
	Serial.println("right in main");
#endif
	hardware->getHeater()->setPower(hardware->getHeater()->getPower() + 1);
	counter++;
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
	counter = 100;
	drawImmed = true;
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