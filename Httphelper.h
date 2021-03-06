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
//#include <ESP8266HTTPUpdateServer.h>
#include "ESP8266WepSpiffsUpdater.h"

#include "Config.h"
#include "DataSrc.h"

class HttpHelper
{
public:
	HttpHelper();
	~HttpHelper();

	void clientHandle();
	boolean handleFileRead(String path);
	void setup();
	void setDataSource(DataSrc * d) { ds = d; };
	boolean isConnected();
	void handleRoot();
	/*void setMode(Mode * m);
	Mode * getMode();*/

private:
	void handleUpdate();
	
	void WiFiconnect();
	void WiFiReconnect();
	void handleLog();
	void handleDistill();
	void handleDistillSet();
	void handleRectify();
	void handleRectifySet();
	//void handleSuvid();
	//void handleSuvidSet();
	void handleBrewingSet();
	void handleBrewing();
	//void handleSuvidChart();
	//Config * conf;
	ESP8266WebServer * server;
	//ESP8266HTTPUpdateServer * httpUpdater;
	ESP8266WebSpiffsUpdater * httpSpiffsUpdater;
	DataSrc * ds;
	//Hardware * hard;
	//Aggregates * agg;
	//Mode * currentMode;
	//std::function<void(void)>  root;
	//std::function<void(void)>  page1;
	//boolean handleFileRead(String path);
};

#endif


