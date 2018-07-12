// Config.h

#ifndef _CONFIG_h
#define _CONFIG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Config
{
public:
	Config();
	~Config();
	void setHttp(const String n, const  String p);
	void setWiFi(const String n, const  String p);
	const String getHttpU();
	const String getHttpP();
	const String getWiFiN();
	const String getWiFiP();
private:
	String wifi_ssid;
	String wifi_password;
	String www_username;
	String www_password;
};

extern Config CONF;

#endif

