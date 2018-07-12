// WiFiHelper.h

#ifndef _WIFIHELPER_h
#define _WIFIHELPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>


class WiFiHelper
{
public:
	WiFiHelper();
	~WiFiHelper();
	void setup();
	void reconnect();
	boolean isConnected();
private:
	//Config *conf;
};






#endif

