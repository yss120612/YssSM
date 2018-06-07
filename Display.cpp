// 
// 
// 

#include "Display.h"

Display::Display(uint8_t addr)
{
	display = new SSD1306Wire(addr, SDA, SCL);
}

Display::~Display()
{
	delete display;
}

void Display::setup()
{
	display->init();
	display->flipScreenVertically();
	display->setFont(ArialMT_Plain_10);
	display->flipScreenVertically();
}

void Display::draw1(String s) {
	display->clear();
	display->drawString(0, 0, s);
	display->display();
}
