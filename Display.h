// Display.h

#ifndef _DISPLAY_h
#define _DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SSD1306Wire.h"



class Display
{
public:
	Display(uint8_t addr);
	~Display();
	void setup();
	void draw1(String s);
	void drawXY(uint8_t x, uint8_t y, String s);
	SSD1306Wire * getDisplay();
private:
	SSD1306Wire * display;
};


#endif

