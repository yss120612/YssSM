// 
// 
// 

#include "Log.h"
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

void Config::setTriakCoolerTemp(uint8_t st)
{
	if (triakCoolerTemp != st) changed = true;
	triakCoolerTemp = st;
}

void Config::setTriakCoolerGist(uint8_t st)
{
	if (triakCoolerGist != st) changed = true;
	triakCoolerGist = st;
}

void Config::setDistWorkPower(uint8_t st)
{
	if (distWorkPower != st) changed = true;
	distWorkPower = st;
}

void Config::setDistStopTemp(float st)
{
	if (distStopTemp != st) changed = true;
	distStopTemp = st;
}

void Config::setDistKranOpened(float st)
{
	if (distKranOpened != st) changed = true;
	distKranOpened = st;
}

void Config::setTSAmin(uint8_t st)
{
	if (TSAmin != st) changed = true;
	TSAmin = st;
}

void Config::setTSAmax(uint8_t st)
{
	if (TSAmax != st) changed = true;
	TSAmax = st;
}

void Config::setTSAcritical(uint8_t st)
{
	if (TSAcritical != st) changed = true;
	TSAcritical = st;
}

void Config::setDistForsajTemp(uint8_t st)
{
	if (distForsajTemp != st) changed = true;
	distForsajTemp = st;
}



const String Config::getHttpU() { return www_username; };
const String Config::getHttpP() { return www_password; };
const String Config::getWiFiN() { return wifi_ssid; };
const String Config::getWiFiP() { return wifi_password; }
const int Config::getScrSavMin(){ return scrSaverMin;}
const int Config::getSuvidMin(){ return suvidMin;}
const uint8_t Config::getSuvidTemp(){return suvidTemp;}
const uint8_t Config::getDistWorkPower(){ return distWorkPower;}
const float Config::getDistStopTemp() { return distStopTemp;}
const float Config::getDistKranOpened(){	return distKranOpened;}
const uint8_t Config::getTSAmin() { return TSAmin; }
const uint8_t Config::getTSAmax(){	return TSAmax;}
const uint8_t Config::getTSAcritical(){	return TSAcritical;}

const uint8_t Config::getDistForsajTemp(){	return distForsajTemp;}
const uint8_t Config::getTriakCoolerTemp(){	return triakCoolerTemp;}
const uint8_t Config::getTriakCoolerGist(){	return triakCoolerGist;}


void Config::write()
{
	calcLength();
	uint8_t * buff = new uint8_t [length];
	uint16_t idx = 0;

	union FLOAT {
		float f;
		uint8_t a[sizeof(float)];
	};
	union INT {
		int i;
		uint8_t a[sizeof(int)];
	};

	uint8_t i;
	FLOAT _float;
	INT _int;

	_float.f = distStopTemp;for (i = 0; i < sizeof(float); i++) *(buff + idx++) = _float.a[i];
	_float.f = distKranOpened; for (i = 0; i < sizeof(float); i++) *(buff + idx++) = _float.a[i];
	_int.i = scrSaverMin; for (i = 0; i < sizeof(int); i++) *(buff + idx++) = _int.a[i];
	_int.i = suvidTemp; for (i = 0; i < sizeof(int); i++) *(buff + idx++) = _int.a[i];
	*(buff + idx++) = distWorkPower;
	*(buff + idx++) = distForsajTemp;
	*(buff + idx++) = TSAmin;
	*(buff + idx++) = TSAmax;
	*(buff + idx++) = TSAcritical;
	*(buff + idx++) = triakCoolerTemp;
	*(buff + idx++) = triakCoolerGist;
	for (i = 0; i < wifi_ssid.length(); i++) { *(buff + idx++) = wifi_ssid.charAt(i); }			*(buff + idx++) = 0;
	for (i = 0; i < wifi_password.length(); i++) { *(buff + idx++) = wifi_password.charAt(i); } *(buff + idx++) = 0;
	for (i = 0; i < www_username.length(); i++) { *(buff + idx++) = www_username.charAt(i); }	*(buff + idx++) = 0;
	for (i = 0; i < www_password.length(); i++) { *(buff + idx++) = www_password.charAt(i); }	*(buff + idx) = 0;
	at24mem->write(0, buff, length);
	logg.logging("CONFIG saved ("+String(idx)+" bytes)!");
	changed = false;
	delete buff;
}

void Config::read()
{
	calcLength();
	length += 100;
	uint8_t * buff = new uint8_t[length];
	at24mem->read(0, buff, length);
	uint16_t idx = 0;
	
	distStopTemp = *reinterpret_cast<float *>(buff + idx); idx += sizeof(float);
	distKranOpened = *reinterpret_cast<float *>(buff + idx); idx += sizeof(float);
	scrSaverMin = *reinterpret_cast<int *>(buff + idx); idx += sizeof(int);
	suvidMin = *reinterpret_cast<int *>(buff + idx); idx += sizeof(int);
	suvidTemp = *reinterpret_cast<uint8_t *>(buff + idx); idx += sizeof(uint8_t);
	distWorkPower = *reinterpret_cast<uint8_t *>(buff + idx); idx += sizeof(uint8_t);
	distForsajTemp = *reinterpret_cast<uint8_t *>(buff + idx); idx += sizeof(uint8_t);
	TSAmin = *reinterpret_cast<uint8_t *>(buff + idx); idx += sizeof(uint8_t);
	TSAmax = *reinterpret_cast<uint8_t *>(buff + idx); idx += sizeof(uint8_t);
	TSAcritical = *reinterpret_cast<uint8_t *>(buff + idx); idx += sizeof(uint8_t);
	triakCoolerTemp = *reinterpret_cast<uint8_t *>(buff + idx); idx += sizeof(uint8_t);
	triakCoolerGist = *reinterpret_cast<uint8_t *>(buff + idx); idx += sizeof(uint8_t);
	wifi_ssid = "";while (*(buff + idx) != 0) {wifi_ssid += *(buff + idx++);}idx++;
	wifi_password = ""; while (*(buff + idx) != 0) { wifi_password += *(buff + idx++); }idx++;
	www_username = ""; while (*(buff + idx) != 0) { www_username += *(buff + idx++); }idx++;
	www_password = ""; while (*(buff + idx) != 0) { www_password += *(buff + idx++); }
	logg.logging("CONFIG loaded (" + String(idx) + " bytes)!");
	changed = false;
	delete buff;

	/*
	String wifi_ssid;
	String wifi_password;
	String www_username;
	String www_password;

	int scrSaverMin;
	int suvidMin;
	uint8_t suvidTemp;

	uint8_t distWorkPower;
	float distStopTemp;
	float distKranOpened;
	uint8_t distForsajTemp;

	uint8_t TSAmin;
	uint8_t TSAmax;
	uint8_t TSAcritical;

	uint8_t triakCoolerTemp;
	uint8_t triakCoolerGist;
	*/

}

uint16_t Config::calcLength()
{
	length = sizeof(int) * 2 + sizeof(float)*2 + sizeof(uint8_t) * 8 + wifi_ssid.length() + 1 + wifi_password.length() + 1 + www_username.length() + 1 + www_password.length() + 1;
	return length;
}



Config CONF;
