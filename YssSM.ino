
#include "Brewing.h"
#include "Manual.h"
#include "Pump.h"
#include "Multiplexor.h"
#include "Rectify.h"
#include "WaterSensor.h"
#include "ESP8266WepSpiffsUpdater.h"
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266WebServer.h>
#include "Config.h"

#include "Mode.h"
#include "Main.h"
//#include "Suvid.h"
#include "Distillation.h"
#include "Workmodes.h"

long scrLoop = 0;
long mls;

HttpHelper httph;

Hardware hard;
Aggregates agg(&hard);

Mode * _main = new Main(&agg, &hard);
//Mode * suvid = new Suvid(&agg, &hard);
Mode * distill = new Distillation(&agg, &hard);
Mode * rectify = new Rectify(&agg, &hard);
Mode * brewing = new Brewing(&agg, &hard);
Mode * manual = new Manual(&agg, &hard);

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

	CONF.loadDefaults();

	httph.setup();
	
	attachInterrupt(ENC_A_PIN, A, CHANGE); // Настраиваем обработчик прерываний по изменению сигнала на линии A 

	attachInterrupt(ENC_BTN_PIN, Button, CHANGE); // Настраиваем обработчик прерываний по изменению сигнала нажатия кнопки

	attachInterrupt(HEAT_NUL_PIN, nulAC, RISING); // Настраиваем обработчик прерываний проходу через 0
	
	workMode.setup(hard.getEncoder());
	workMode.addMode(_main);
	//workMode.addMode(suvid);
	workMode.addMode(brewing);
	workMode.addMode(distill);
	workMode.addMode(rectify);
	workMode.addMode(manual);
	workMode.setCurrent(MODE_MAIN);
	httph.setDataSource(&workMode);
	logg.logging("Open http://"+ WiFi.localIP().toString()+ "/ in your browser to see it working");

	if (CONF.checkVersion()) {
		CONF.read();
	}
	else {
		CONF.write();
	}
	
	logg.logging("ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000="+String((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000));
	logg.logging("ESP.getFreeSketchSpace()=" + String(ESP.getFreeSketchSpace()));
	logg.logging("ESP.getFlashChipRealSize()=" + String(ESP.getFlashChipRealSize()));
	logg.logging("ESP.getFreeSketchSpace()=" + String(ESP.getFreeSketchSpace()));
	logg.logging("ESP.getFreeSketchSpace()=" + String(ESP.getFreeSketchSpace()));
	logg.logging(hard.i2cDevices());
	logg.logging(hard.owDevices());
	logg.logging("End of init");

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

ICACHE_RAM_ATTR void t1IntHandler() {
	hard.getBeeper()->process();
}

void loop() {
	mls = millis();
	httph.clientHandle();
	hard.process(mls);
	agg.process(mls);
	workMode.getCurrent()->drawImm(mls);

	if (scrLoop - mls + 1500 < 0) {
		hard.timed_process(mls);
		agg.timed_process(mls);
		workMode.getCurrent()->process(mls);
		workMode.getCurrent()->draw(mls);
		scrLoop = millis();
	}
}
