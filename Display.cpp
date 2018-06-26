
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
	display->setFont(ArialMT_Plain_16);
	display->flipScreenVertically();
}

void Display::draw1(String s) {
	//display->clear();
	display->drawString(0, 0, s);
	//display->display();
}

void Display::drawXY(uint8_t x, uint8_t y, String s) {
	//display->clear();
	display->drawString(x, y, s);
	//display->display();
}

SSD1306Wire * Display::getDisplay() {
	return display;
}