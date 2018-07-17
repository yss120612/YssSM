// 
// 
// 

#include "Config.h"

Config::Config()
{
}

Config::~Config()
{
}

void Config::setHttp(const String n, const  String p) {
	www_username=n;
	www_password=p;
}
void Config::setWiFi(const String n, const String p) {
	wifi_ssid = n;
	wifi_password = p;
}

void Config::setScrSavMin(int ss)
{
	scrSaverMin = ss;
}


const String Config::getHttpU() { return www_username; };
const String Config::getHttpP() { return www_password; };
const String Config::getWiFiN() { return wifi_ssid; };
const String Config::getWiFiP() { return wifi_password; }
const int Config::getScrSavMin(){ return scrSaverMin;}

Config CONF;
