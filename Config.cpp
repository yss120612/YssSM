// 
// 
// 

#include "Config.h"

Config::Config()
{
	changed = false;
}

Config::~Config()
{
}

void Config::setHttp(const String n, const  String p) {
	if (!www_username.equals(n) || !www_password.equals(p)) changed = true;
	www_username=n;
	www_password=p;
}
void Config::setWiFi(const String n, const String p) {
	if (!wifi_ssid.equals(n) || !wifi_password.equals(p)) changed = true;
	wifi_ssid = n;
	wifi_password = p;
}

void Config::setScrSavMin(int ss)
{
	if (scrSaverMin != ss) changed = true;
	scrSaverMin = ss;
}

void Config::setSuvidMin(int sm)
{
	if (suvidMin != sm) changed = true;
	suvidMin = sm;
}

void Config::setSuvidTemp(uint8_t st)
{
	if (suvidTemp != st) changed = true;
	suvidTemp = st;
}

void Config::setDistWorkPower(uint8_t st)
{
	if (distWorkPower != st) changed = true;
	distWorkPower = st;
}

void Config::setDistStopTemp(uint8_t st)
{
	if (distStopTemp != st) changed = true;
	distStopTemp = st;
}

void Config::setDistKranOpened(uint8_t st)
{
	if (distKranOpened != st) changed = true;
	distKranOpened = st;
}


const String Config::getHttpU() { return www_username; };
const String Config::getHttpP() { return www_password; };
const String Config::getWiFiN() { return wifi_ssid; };
const String Config::getWiFiP() { return wifi_password; }
const int Config::getScrSavMin(){ return scrSaverMin;}
const int Config::getSuvidMin(){ return suvidMin;}
const uint8_t Config::getSuvidTemp(){return suvidTemp;}
const uint8_t Config::getDistWorkPower(){ return distWorkPower;}
const uint8_t Config::getDistStopTemp() { return distStopTemp;}
const uint8_t Config::getDistKranOpened(){	return distKranOpened;}

Config CONF;
