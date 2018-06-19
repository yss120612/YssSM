
#define _SERIAL

#include "Cooler.h"
#include "Mode.h"
#include "Main.h"
#include "Encoder.h"

#include "Suvid.h"

#include "Kran.h"

#include <OneWire.h>
#include <Wire.h>  

//#define MODE_MAIN 0
//#define MODE_SUVID 1
//#define MODE_DISCIL 2
//#define MODE_RECTIFY 3
//#define MODE_SETUP 99

const uint8_t EX_PIN0 = 100;
const uint8_t EX_PIN1 = 101;
const uint8_t EX_PIN2 = 102;
const uint8_t EX_PIN3 = 103;
const uint8_t EX_PIN4 = 104;
const uint8_t EX_PIN5 = 105;
const uint8_t EX_PIN6 = 106;
const uint8_t EX_PIN7 = 107;

const uint8_t EX_PIN8 = 108;
const uint8_t EX_PIN9 = 109;
const uint8_t EX_PIN10 = 110;
const uint8_t EX_PIN11 = 111;
const uint8_t EX_PIN12 = 112;
const uint8_t EX_PIN13 = 113;
const uint8_t EX_PIN14 = 114;
const uint8_t EX_PIN15 = 115;



const uint8_t TEMPERATURE_PIN = D3;
///const uint8_t BEEPER_PIN = D10;

const uint8_t ENC_A_PIN = D4;
const uint8_t ENC_B_PIN = D0;
const uint8_t ENC_BTN_PIN = D5;



const uint8_t EXT_CLC =  D7;
const uint8_t EXT_LOCK = D6;
const uint8_t EXT_DATA = D8;

const uint8_t HEAT_NUL_PIN = D9;
const uint8_t HEAT_REL_PIN = EX_PIN15;
const uint8_t HEAT_DRV_PIN = D10;

const uint8_t TRIAC_COOL_PIN = EX_PIN0;

#define NOSERIAL
#define NOBLED

Config conf;


//uint8_t mode;//Режим работы устройства в данный момент

long scrLoop = 0;

HttpHelper httph(&conf);
WiFiHelper wifih(&conf);

OneWire ds(TEMPERATURE_PIN);
uint8_t  tkube[]	= { 0x28, 0xFF, 0x73, 0x37, 0x67, 0x14, 0x02, 0x11};
uint8_t  t1[]		= { 0x28, 0xFF, 0x10, 0x5C, 0x50, 0x17, 0x04, 0x66};
uint8_t  t2[]		= { 0x28, 0xFF, 0xC1, 0x57, 0x50, 0x17, 0x04, 0x61};
uint8_t  t3[]		= { 0x28, 0xFF, 0x66, 0x5A, 0x50, 0x17, 0x04, 0x9E};
uint8_t  t4[]		= { 0x28, 0xFF, 0xBC, 0x96, 0x50, 0x17, 0x04, 0x56};
uint8_t  t5[]		= { 0x28, 0xFF, 0x75, 0x98, 0x50, 0x17, 0x04, 0x92};

PinExtender extender;
DallasTerm kube_temp(tkube, &ds, 2.5);
Display disp(0x3C);
//Beeper beeper(BEEPER_PIN);
Encoder encoder;
Heater heater;

Hardware hard;
Cooler cool(&hard);
Mode * md = new Main(&hard);

void setup() {
	extender.setup(EXT_LOCK, EXT_CLC, EXT_DATA);

	hard.setConfig(&conf);
	hard.setDisplay(&disp);
	hard.setHeater(&heater);
	heater.setExtender(&extender);
	hard.setTKube(&kube_temp);
	hard.setTTriak(&kube_temp);
	hard.setHttpHelper(&httph);
	//hard.setBeeper(&beeper);
	hard.setExtender(&extender);


	conf.setWiFi("Yss_GIGA","bqt3bqt3");
	conf.setHttp("admin", "esp");

	wifih.setup();
	httph.setup();
	disp.setup();
	//beeper.setup();

	//mode = MODE_MAIN;
	cool.setup(TRIAC_COOL_PIN);
	cool.setTemperature(30, 1);
	encoder.setup(ENC_A_PIN,ENC_B_PIN,ENC_BTN_PIN);

	attachInterrupt(ENC_A_PIN, A, CHANGE); // Настраиваем обработчик прерываний по изменению сигнала на линии A 
	attachInterrupt(ENC_BTN_PIN, Button, CHANGE); // Настраиваем обработчик прерываний по изменению сигнала нажатия кнопки
	encoder.setHandler(md);

	//heater.setup(HEAT_DRV_PIN, HEAT_REL_PIN);
	attachInterrupt(HEAT_NUL_PIN, nulAC, RISING); // Настраиваем обработчик прерываний по изменению сигнала на линии A 

#ifdef _SERIAL
	Serial.begin(115200);
	Serial.print("Open http://");
	Serial.print(WiFi.localIP());
	Serial.println("/ in your browser to see it working");
#endif

}

void nulAC() {
	heater.processHeater();
}

void A() {
	encoder.A();
}

void Button() {
	encoder.Button();
}



long mls;
void loop() {
	mls = millis();
	httph.clientHandle();
	encoder.process(mls);
	cool.process(mls);
	md->drawImm();

	

	if (scrLoop + 1000 - mls < 0) {
		kube_temp.process(mls);
		md->draw();
	}

	
}


//void draw(void) {
//	//switch (mode)
//	//{
//	//case MODE_MAIN:
//	//	break;
//	/*default:
//		break;
//	}*/
//		
//	//disp.draw1(String(kube_temp.getTemp()));
//	}



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
