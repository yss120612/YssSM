// Httphelper.h

#ifndef _HTTPHELPER_h
#define _HTTPHELPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include "Config.h"


class HttpHelper
{
public:
	HttpHelper(Config *c);
	~HttpHelper();

	void clientHandle();
	void setup();
private:
	static Config * conf;
	static ESP8266WebServer * server;
	static void root();
	static void page1();
};

#endif


