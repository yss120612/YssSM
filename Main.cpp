// 
// 
// 

#include "Main.h"

Main::Main(Hardware * h):Mode(h)
{
}


void Main::draw() {
	hardware->getDisplay()->getDisplay()-> clear();
	hardware->getDisplay()->getDisplay()->drawString(0, 0, String(hardware->getTKube()->getTemp()));
	hardware->getDisplay()->getDisplay()->drawString(0, 14, String(hardware->getHeater()->getPower()));
	hardware->getDisplay()->getDisplay()->drawString(0, 28, "HeaterOn=" + String(hardware->getHeater()->isON()));
	hardware->getDisplay()->getDisplay()->display();

	
}

void Main::drawImm() {
	if (!drawImmed) return;
	draw();
	drawImmed = false;
}

void Main::left() {
#ifdef _SERIAL
	Serial.println("left in main");
#endif
	hardware->getHeater()->setPower(hardware->getHeater()->getPower() - 1);
	drawImmed = true;
}
void Main::right() {
#ifdef _SERIAL
	Serial.println("right in main");
#endif
	hardware->getHeater()->setPower(hardware->getHeater()->getPower() + 1);
	drawImmed = true;
}
void Main::press() {
#ifdef _SERIAL
	Serial.println("press in main");
#endif
	if (!hardware->getHeater()->isON()) {
		//hardware->getHeater()->start();
	}
	else {
		//hardware->getHeater()->stop();
	}
	//hardware->getBeeper()->beep(1000, 500);
	drawImmed = true;
	hardware->getExtender()->setAll(0xFFFF);
}
void Main::long_press() {
#ifdef _SERIAL
	Serial.println("long_press in main");
#endif
	drawImmed = true;
}