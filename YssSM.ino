
#include "Rectify.h"
#include "WaterSensor.h"
#include "ESP8266WepSpiffsUpdater.h"
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266WebServer.h>
#include "Termopause.h"
#include "Config.h"
//#include "DataSource.h"

#include "Mode.h"
#include "Main.h"
#include "Suvid.h"
#include "Distillation.h"
#include "Workmodes.h"

long scrLoop = 0;
long mls;



HttpHelper httph;


Hardware hard;
Aggregates agg(&hard);

Mode * main = new Main(&agg, &hard);
Mode * suvid = new Suvid(&agg, &hard);
Mode * distill = new Distillation(&agg, &hard);
Mode * rectify = new Rectify(&agg, &hard);


void setup() {
#ifdef _SERIAL
	Serial.begin(74880);
	logg.logging("_SERIAL is defined");
#else
	logg.logging("_SERIAL is NOT defined");
#endif

	hard.init();
	agg.init();
	
	

	CONF.setMem(hard.getAT24mem());
	

	//CONF.setWiFi("ROSTELEKOM-42", "123qweasdzxc");
	CONF.seWiFi("Yss_GIGA","bqt3bqt3");
	CONF.seHttp("admin", "esp");
	CONF.seScrSavMin(1);
	CONF.seSuvidMin(60);
	CONF.seSuvidTemp(60);

	CONF.seDistKranOpened(19.5);
	CONF.seDistStopTemp(98.8);
	CONF.seDistWorkPower(42);
	CONF.seDistForsajTemp(57);
	
	CONF.seRectKranOpened(21.5);
	CONF.seRectHeadKranOpened(21.5);
	CONF.seRectStopTemp(80.8);
	CONF.seRectHeadPower(35);
	CONF.seRectWorkPower(35);
	CONF.seRectForsajTemp(57);

	CONF.setTSAmin(28);
	CONF.setTSAmax(50);
	CONF.seTSAcritical(90);

	CONF.setTriakCoolerTemp(50);
	CONF.seTriakCoolerGist(10);
	
	httph.setup();
	
	logg.logging(" Temp= " + String(CONF.getDistStopTemp()) + " Kran= " + String(CONF.getDistKranOpened()) + " Suvid Temp(50)= " + String(CONF.getSuvidTemp()) + " WiFi name=" + CONF.getWiFiN() + " WiFi Pass=" + CONF.getWiFiP());
	
	attachInterrupt(ENC_A_PIN, A, CHANGE); // Настраиваем обработчик прерываний по изменению сигнала на линии A 

	attachInterrupt(ENC_BTN_PIN, Button, CHANGE); // Настраиваем обработчик прерываний по изменению сигнала нажатия кнопки

	attachInterrupt(HEAT_NUL_PIN, nulAC, RISING); // Настраиваем обработчик прерываний проходу через 0
	
	workMode.setup(hard.getEncoder());
	workMode.addMode(main);
	workMode.addMode(suvid);
	workMode.addMode(distill);
	workMode.addMode(rectify);
	workMode.setCurrent(MODE_MAIN);
	httph.setDataSource(&workMode);
	logg.logging("Open http://"+ WiFi.localIP().toString()+ "/ in your browser to see it working");

	/*CONF.write();
	if (CONF.checkVersion()) {
		CONF.read();
	}
	else {
		CONF.write();
	}*/

	logg.logging("ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000="+String((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000));
	logg.logging("ESP.getFreeSketchSpace()=" + String(ESP.getFreeSketchSpace()));
	logg.logging("ESP.getFlashChipRealSize()=" + String(ESP.getFlashChipRealSize()));
	logg.logging("ESP.getFreeSketchSpace()=" + String(ESP.getFreeSketchSpace()));
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


//int i = 0;
void loop() {
	mls = millis();
	httph.clientHandle();
	hard.process(mls);
	agg.process(mls);
	workMode.getCurrent()->drawImm(mls);

	if (scrLoop + 1000 - mls < 0) {
		hard.timed_process(mls);
		agg.timed_process(mls);
		workMode.getCurrent()->process(mls);
		workMode.getCurrent()->draw(mls);
		scrLoop = millis();
		//i++;
		//logg.logging("Event " + String(i) + " Length=" + logg.length());
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
