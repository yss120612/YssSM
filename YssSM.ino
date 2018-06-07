
#include "Beeper.h"
#include "Display.h"
#include "Mode.h"
#include "Suvid.h"
#include "Config.h"
#include "WiFiHelper.h"
#include "Httphelper.h"
#include "Kran.h"
#include "Heater.h"

#include <OneWire.h>
#include <Wire.h>  

#include "DallasTerm.h"
#include "images.h"


#define MODE_MAIN 0
#define MODE_SUVID 1
#define MODE_DISCIL 2
#define MODE_RECTIFY 3
#define MODE_SETUP 99

Config conf;

uint8_t mode;//Режим работы устройства в данный момент
long scrLoop = 0;


HttpHelper httph(&conf);
WiFiHelper wifih(&conf);

//const uint8_t COOLER_PIN = 3;
//const uint8_t LEFT_BTN_PIN = 4;
//const uint8_t WATER_OPEN_PIN = 5;
//const uint8_t WATER_CLOSE_PIN = 6;
//const uint8_t CENTER_BTN_PIN = 7;
//const uint8_t RIGHT_BTN_PIN = 8;
//const uint8_t RELAY_PIN = 9;
//const uint8_t HEATER_PIN = 9;
const uint8_t TEMPERATURE_PIN = D3;
//const uint8_t UROVEN_VCC_PIN = 11;
const uint8_t BEEPER_PIN = D4;

//const uint8_t CLOCK_RST_PIN = 3;
//const uint8_t CLOCK_DAT_PIN = 5;
//const uint8_t CLOCK_CLK_PIN = 6;

//const uint8_t TERMISTOR_PIN = A0;
//const uint8_t WATER_MEASURE_PIN = 11;
//const uint8_t UROVEN_PIN = D0;



OneWire ds(TEMPERATURE_PIN);
uint8_t  tkube[] = { 0x28,0xFF,0x73,0x37,0x67,0x14,0x02,0x11 };
uint8_t  t1[] = { 0x28, 0xFF, 0x10, 0x5C, 0x50, 0x17, 0x04, 0x66 };
uint8_t  t2[] = { 0x28, 0xFF, 0xC1, 0x57, 0x50, 0x17, 0x04, 0x61};
uint8_t  t3[] = { 0x28, 0xFF, 0x66, 0x5A, 0x50, 0x17, 0x04, 0x9E};

DallasTerm kube_temp(t3, &ds, 2.5);
Display disp(0x3C);
Beeper beeper(D4);



void setup() {
	//pinMode(D0, OUTPUT);
	//digitalWrite(D0, LOW);

	Serial.begin(115200);
	conf.setWiFi("Yss_GIGA","bqt3bqt3");
	conf.setHttp("admin", "esp");

	wifih.setup();
	httph.setup();
	disp.setup();
	beeper.setup();
	//pinMode(BEEPER_PIN, OUTPUT);

	

	mode = MODE_MAIN;
	//pinMode(FUNC_GPIO10,OUTPUT);

	Serial.print("Open http://");
	Serial.print(WiFi.localIP());
	Serial.println("/ in your browser to see it working");
}

long mls;
void loop() {
	httph.clientHandle();

	mls = millis();
	if (scrLoop + 1000 - mls < 0) {
		kube_temp.process(mls);
		draw();
	}
}


void draw(void) {
	switch (mode)
	{
	case MODE_MAIN:
		break;
	default:
		break;
	}
		
	disp.draw1(String(kube_temp.getTemp()));
	}


//void drawFontFaceDemo() {
//	// Font Demo1
//	// create more fonts at http://oleddisplay.squix.ch/
//	display.setTextAlignment(TEXT_ALIGN_LEFT);
//	display.setFont(ArialMT_Plain_10);
//	display.drawString(0, 0, "Hello world");
//	display.setFont(ArialMT_Plain_16);
//	display.drawString(0, 10, "Hello world");
//	display.setFont(ArialMT_Plain_24);
//	display.drawString(0, 26, "Hello world");
//}
//
//void drawTextFlowDemo() {
//	display.setFont(ArialMT_Plain_10);
//	display.setTextAlignment(TEXT_ALIGN_LEFT);
//	display.drawStringMaxWidth(0, 0, 128,
//		"Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore.");
//}
//
//void drawTextAlignmentDemo() {
//	// Text alignment demo
//	display.setFont(ArialMT_Plain_10);
//
//	// The coordinates define the left starting point of the text
//	display.setTextAlignment(TEXT_ALIGN_LEFT);
//	display.drawString(0, 10, "Left aligned (0,10)");
//
//	// The coordinates define the center of the text
//	display.setTextAlignment(TEXT_ALIGN_CENTER);
//	display.drawString(64, 22, "Center aligned (64,22)");
//
//	// The coordinates define the right end of the text
//	display.setTextAlignment(TEXT_ALIGN_RIGHT);
//	display.drawString(128, 33, "Right aligned (128,33)");
//}
//
//void drawRectDemo() {
//	// Draw a pixel at given position
//	for (int i = 0; i < 10; i++) {
//		display.setPixel(i, i);
//		display.setPixel(10 - i, i);
//	}
//	display.drawRect(12, 12, 20, 20);
//
//	// Fill the rectangle
//	display.fillRect(14, 14, 17, 17);
//
//	// Draw a line horizontally
//	display.drawHorizontalLine(0, 40, 20);
//
//	// Draw a line horizontally
//	display.drawVerticalLine(40, 0, 20);
//}
//
//void drawCircleDemo() {
//	for (int i = 1; i < 8; i++) {
//		display.setColor(WHITE);
//		display.drawCircle(32, 32, i * 3);
//		if (i % 2 == 0) {
//			display.setColor(BLACK);
//		}
//		display.fillCircle(96, 32, 32 - i * 3);
//	}
//}
//
//void drawProgressBarDemo() {
//	int progress = (10 / 5) % 100;
//	// draw the progress bar
//	display.drawProgressBar(0, 32, 120, 10, progress);
//
//	// draw the percentage as String
//	display.setTextAlignment(TEXT_ALIGN_CENTER);
//	display.drawString(64, 15, String(progress) + "%");
//}
//
//void drawImageDemo() {
//	// see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
//	// on how to create xbm files
//	display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
//}
//
//
//
