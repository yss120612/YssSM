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
	void setScrSavMin(int ss);
	void setSuvidMin(int sm);
	void setSuvidTemp(uint8_t st);
	const String getHttpU();
	const String getHttpP();
	const String getWiFiN();
	const String getWiFiP();
	const int getScrSavMin();
	const int getSuvidMin();
	const uint8_t getSuvidTemp();
private:
	String wifi_ssid;
	String wifi_password;
	String www_username;
	String www_password;
	int scrSaverMin;
	int suvidMin;
	uint8_t suvidTemp;
	boolean changed;
};

extern Config CONF;

#endif

