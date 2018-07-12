
//#include "Aggregates.h"


//#include "Const.h"
//#include "AT24C32.h"

#include "Config.h"

#include "RTCmemory.h"
#include <EEPROM.h>

#include <QList.h>

#include "Mode.h"

#include "Main.h"
#include "Suvid.h"

long scrLoop = 0;

HttpHelper httph;
WiFiHelper wifih;

//PinExtender extender;
//DallasTerm kube_temp(tkube, &ds, 2.5);
//SSD1306Wire display(0x3C, SDA, SCL);

Hardware hard;
Aggregates agg(&hard);
//Cooler cool;
Mode * md = new Main(&agg,&hard);

void setup() {
	hard.init();
	agg.init();
	

#ifdef _SERIAL
	Serial.begin(115200);
	logg.logging("_SERIAL is defined");
#else
	logg.logging("_SERIAL is NOT defined");
#endif

	CONF.setWiFi("ROSTELEKOM-42", "123qweasdzxc");
	//conf.setWiFi("Yss_GIGA","bqt3bqt3");
	CONF.setHttp("admin", "esp");
	
	wifih.setup();
	httph.setup();
	
	hard.getEncoder()->setHandler(md);
	
	attachInterrupt(ENC_A_PIN, A, CHANGE); // Настраиваем обработчик прерываний по изменению сигнала на линии A 
	attachInterrupt(ENC_BTN_PIN, Button, CHANGE); // Настраиваем обработчик прерываний по изменению сигнала нажатия кнопки

	attachInterrupt(HEAT_NUL_PIN, nulAC, RISING); // Настраиваем обработчик прерываний проходу через 0
	
	/*RTC.yyyy = 2018;
	RTC.dd = 22;
	RTC.mm = 6;
	RTC.h = 23;
	RTC.m = 53;
	RTC.s = 0;
	RTC.dow = 4;*/
	//RTC.readRAM
	//RTC.writeTime();
	md->initDraw();
	logg.logging("Open http://"+ WiFi.localIP().toString()+ "/ in your browser to see it working");
}

void nulAC() {
	agg.getHeater()->processHeater();
}

void A() {
	hard.getEncoder()->A();
}

void Button() {
	hard.getEncoder()->Button();
}



long mls;

void loop() {
	mls = millis();
	httph.clientHandle();
	hard.process(mls);
	agg.process(mls);
	md->drawImm();

	if (scrLoop + 1000 - mls < 0) {
		hard.timed_process(mls);
		agg.timed_process(mls);
		md->draw();
		scrLoop = millis();
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
