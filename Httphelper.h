// Httphelper.h

#ifndef _HTTPHELPER_h
#define _HTTPHELPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

#include "Config.h"


class HttpHelper
{
public:
	HttpHelper();
	~HttpHelper();

	void clientHandle();
	void setup();
	boolean isConnected();
	/*void setMode(Mode * m);
	Mode * getMode();*/

private:
	void handleUpdate();
	
	void WiFiconnect();
	void WiFiReconnect();
	void handleLog();
	//Config * conf;
	ESP8266WebServer * server;
	ESP8266HTTPUpdateServer * httpUpdater;
	//Mode * currentMode;
	//std::function<void(void)>  root;
	//std::function<void(void)>  page1;
	//boolean handleFileRead(String path);
};

#endif


