// 
// 
// 

#include "Log.h"
#include "Config.h"

Config::Config()
{
	changed = false;
	version = 2;
}

Config::~Config()
{
}

void Config::loadDefaults() {
	seWiFi("Yss_GIGA", "bqt3bqt3");
	seHttp("admin", "esp");
	seScrSavMin(1);
	seSuvidMin(60);
	seSuvidTemp(60);

	seDistKranOpened(21.2);
	seDistStopTemp(98.8);
	seDistWorkPower(42);
	seDistForsajTemp(57);

	seManualKranOpened(19.5);
	seManualWorkPower(42);

	seRectWorkSelf(20);
	seRectKranOpened(21.5);
	seRectHeadKranOpened(21.5);
	seRectStopTemp(80.8);
	seRectHeadPower(32);
	seRectWorkPower(32);
	seRectForsajTemp(57);

	setTSAmin(28);
	setTSAmax(50);
	seTSAcritical(90);

	setTriakCoolerTemp(50);
	seTriakCoolerGist(10);
}

boolean Config::checkVersion()
{
	uint8_t v = at24mem->read(0);
	return v == version;
}

void Config::setHttp(const String n, const  String p) {
	if (!www_username.equals(n) || !www_password.equals(p)) changed = true;
	www_username=n;
	www_password=p;
	write();
}

void Config::seHttp(const String n, const  String p) {
	if (!www_username.equals(n) || !www_password.equals(p)) changed = true;
	www_username = n;
	www_password = p;
}
void Config::setWiFi(const String n, const String p) {
	if (!wifi_ssid.equals(n) || !wifi_password.equals(p)) changed = true;
	wifi_ssid = n;
	wifi_password = p;
	write();
}

void Config::seWiFi(const String n, const String p) {
	if (!wifi_ssid.equals(n) || !wifi_password.equals(p)) changed = true;
	wifi_ssid = n;
	wifi_password = p;
}


void Config::setScrSavMin(int ss)
{
	if (scrSaverMin != ss) changed = true;
	scrSaverMin = ss;
	write();
}

void Config::seScrSavMin(int ss)
{
	if (scrSaverMin != ss) changed = true;
	scrSaverMin = ss;
}


void Config::setSuvidMin(int sm)
{
	if (suvidMin != sm) changed = true;
	suvidMin = sm;
	write();
}

void Config::seSuvidMin(int sm)
{
	if (suvidMin != sm) changed = true;
	suvidMin = sm;
}


void Config::setSuvidTemp(uint8_t st)
{
	if (suvidTemp != st) changed = true;
	suvidTemp = st;
	write();
}

void Config::seSuvidTemp(uint8_t st)
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
	write();
}

void Config::seTriakCoolerGist(uint8_t st)
{
	if (triakCoolerGist != st) changed = true;
	triakCoolerGist = st;
}


void Config::setRectWorkPower(uint8_t st)
{
	if (rectWorkPower != st) changed = true;
	rectWorkPower = st;
	write();
}

void Config::seRectWorkPower(uint8_t st)
{
	if (rectWorkPower != st) changed = true;
	rectWorkPower = st;
}


void Config::setRectWorkSelf(uint8_t st)
{
	if (rectWorkSlf != st) changed = true;
	rectWorkSlf = st;
	write();
}

void Config::seRectWorkSelf(uint8_t st)
{
	if (rectWorkSlf != st) changed = true;
	rectWorkSlf = st;
}

void Config::setRectHeadPower(uint8_t st)
{
	if (rectHeadPower != st) changed = true;
	rectHeadPower = st;
	write();
}

void Config::seRectHeadPower(uint8_t st)
{
	if (rectHeadPower != st) changed = true;
	rectHeadPower = st;
}


void Config::setRectStopTemp(float st)
{
	if (rectStopTemp != st) changed = true;
	rectStopTemp = st;
	write();
}

void Config::seRectStopTemp(float st)
{
	if (rectStopTemp != st) changed = true;
	rectStopTemp = st;
}




void Config::setRectKranOpened(float st)
{
	if (rectKranOpened != st) changed = true;
	rectKranOpened = st;
	write();
}

void Config::seRectKranOpened(float st)
{
	if (rectKranOpened != st) changed = true;
	rectKranOpened = st;
}


void Config::setRectHeadKranOpened(float st)
{
	if (rectHeadKranOpened != st) changed = true;
	rectHeadKranOpened = st;
	write();
}


void Config::seRectHeadKranOpened(float st)
{
	if (rectHeadKranOpened != st) changed = true;
	rectHeadKranOpened = st;
}

void Config::setRectForsajTemp(uint8_t st)
{
	if (rectForsajTemp != st) changed = true;
	rectForsajTemp = st;
	write();
}

void Config::seRectForsajTemp(uint8_t st)
{
	if (rectForsajTemp != st) changed = true;
	rectForsajTemp = st;
}


void Config::setDistWorkPower(uint8_t st)
{
	if (distWorkPower != st) changed = true;
	distWorkPower = st;
	write();
}

void Config::seDistWorkPower(uint8_t st)
{
	if (distWorkPower != st) changed = true;
	distWorkPower = st;
}


void Config::setDistStopTemp(float st)
{
	if (distStopTemp != st) changed = true;
	distStopTemp = st;
	write();
}

void Config::seDistStopTemp(float st)
{
	if (distStopTemp != st) changed = true;
	distStopTemp = st;
}


void Config::setDistKranOpened(float st)
{
	if (distKranOpened != st) changed = true;
	distKranOpened = st;
	write();
}

void Config::seDistKranOpened(float st)
{
	if (distKranOpened != st) changed = true;
	distKranOpened = st;
}

void Config::setDistForsajTemp(uint8_t st)
{
	if (distForsajTemp != st) changed = true;
	distForsajTemp = st;
	write();
}

void Config::seDistForsajTemp(uint8_t st)
{
	if (distForsajTemp != st) changed = true;
	distForsajTemp = st;
}

void Config::setManualWorkPower(uint8_t st)
{
	if (manualWorkPower != st) changed = true;
	manualWorkPower = st;
	write();
}

void Config::seManualWorkPower(uint8_t st)
{
	if (manualWorkPower != st) changed = true;
	manualWorkPower = st;
}

void Config::setManualKranOpened(float st)
{
	if (manualKranOpened != st) changed = true;
	manualKranOpened = st;
	write();
}

void Config::seManualKranOpened(float st)
{
	if (manualKranOpened != st) changed = true;
	manualKranOpened = st;
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
	write();
}


void Config::seTSAcritical(uint8_t st)
{
	if (TSAcritical != st) changed = true;
	TSAcritical = st;

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
const uint8_t Config::getDistForsajTemp() { return distForsajTemp; }

const float Config::getManualKranOpened(){	return manualKranOpened;}
const uint8_t Config::getManualWorkPower(){	return manualWorkPower;}

const uint8_t Config::getRectWorkSelf() { return rectWorkSlf; }
const uint8_t Config::getRectHeadPower() { return rectHeadPower; }
const uint8_t Config::getRectWorkPower() { return rectWorkPower; }
const float Config::getRectKranOpened() { return rectKranOpened; }
const float Config::getRectHeadKranOpened() { return rectHeadKranOpened; }
const uint8_t Config::getRectForsajTemp() { return rectForsajTemp; }
const float Config::getRectStopTemp() { return rectStopTemp; }

const uint8_t Config::getTSAmin() { return TSAmin; }
const uint8_t Config::getTSAmax(){	return TSAmax;}
const uint8_t Config::getTSAcritical(){	return TSAcritical;}



const uint8_t Config::getTriakCoolerTemp(){	return triakCoolerTemp;}
const uint8_t Config::getTriakCoolerGist(){	return triakCoolerGist;}


void Config::write()
{
#ifndef HAVE_AT24C32
	return;
#endif
	if (!changed) return;
	calcLength();
	uint8_t * buff = new uint8_t [length];
	uint16_t idx = 0;
	uint8_t i;

	*(buff + idx++) = version;

	memcpy((buff + idx), &distStopTemp,		sizeof(float)); idx += sizeof(float);
	memcpy((buff + idx), &distKranOpened,	sizeof(float)); idx += sizeof(float);
	memcpy((buff + idx), &rectStopTemp,		sizeof(float)); idx += sizeof(float);
	memcpy((buff + idx), &rectKranOpened,	sizeof(float)); idx += sizeof(float);
	memcpy((buff + idx), &rectHeadKranOpened,	sizeof(float)); idx += sizeof(float);
	memcpy((buff + idx), &manualKranOpened, sizeof(float)); idx += sizeof(float);

	memcpy((buff + idx), &scrSaverMin,		sizeof(int));	idx += sizeof(int);
	memcpy((buff + idx), &suvidMin,			sizeof(int));	idx += sizeof(int);

	*(buff + idx++) = suvidTemp;
	*(buff + idx++) = distWorkPower;
	*(buff + idx++) = distForsajTemp;
	*(buff + idx++) = manualWorkPower;
	*(buff + idx++) = rectWorkSlf;
	*(buff + idx++) = rectWorkPower;
	*(buff + idx++) = rectHeadPower;
	*(buff + idx++) = rectForsajTemp;
	*(buff + idx++) = TSAmin;
	*(buff + idx++) = TSAmax;
	*(buff + idx++) = TSAcritical;
	*(buff + idx++) = triakCoolerTemp;
	*(buff + idx++) = triakCoolerGist;

	wifi_ssid.getBytes(buff + idx, wifi_ssid.length() + 1); idx += wifi_ssid.length()+1;
	wifi_password.getBytes(buff + idx, wifi_password.length() + 1); idx += wifi_password.length() + 1;
	www_username.getBytes(buff + idx, www_username.length() + 1); idx += www_username.length() + 1;
	www_password.getBytes(buff + idx, www_password.length() + 1); idx += www_password.length()+1;
	
	at24mem->write(0, buff, length);
	logg.logging("CONFIG saved ("+String(idx)+" bytes)!");
	changed = false;
	delete buff;
}

void Config::read()
{
#ifndef HAVE_AT24C32
	return;
#endif
	calcLength();
	length += 100;
	uint8_t * buff = new uint8_t[length];
	at24mem->read(0, buff, length);
	uint16_t idx = 1;
	
	distStopTemp =			 static_cast<float>(*(buff + idx)); idx += sizeof(float);
	distKranOpened = static_cast<float>(*(buff + idx)); idx += sizeof(float);
	rectStopTemp = static_cast<float>(*(buff + idx)); idx += sizeof(float);
	rectKranOpened = static_cast<float>(*(buff + idx)); idx += sizeof(float);
	rectHeadKranOpened = static_cast<float>(*(buff + idx)); idx += sizeof(float);
	manualKranOpened	= static_cast<float>(*(buff + idx)); idx += sizeof(float);

	scrSaverMin =		static_cast<int>(*(buff + idx)); idx += sizeof(int);
	suvidMin = static_cast<int>(*(buff + idx)); idx += sizeof(int);

	
	suvidTemp =			static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	distWorkPower = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	distForsajTemp = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	manualWorkPower = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	rectWorkSlf = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	rectWorkPower = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	rectHeadPower = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	rectForsajTemp = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	TSAmin = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	TSAmax = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	TSAcritical = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	triakCoolerTemp = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	triakCoolerGist = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	
	//logg.logging("0 loaded idx=(" + String(idx) + " bytes)!");
	wifi_ssid = "";		while (*(buff + idx) != 0) { wifi_ssid += static_cast<char>(*(buff + idx)); idx += sizeof(char); }; idx += sizeof(char);
	//logg.logging("1 loaded idx=(" + String(idx) + " bytes)! wifi_ssid=" + wifi_ssid);
	wifi_password = ""; while (*(buff + idx) != 0) { wifi_password += static_cast<char>(*(buff + idx)); idx += sizeof(char); }; idx += sizeof(char);
	//logg.logging("2 loaded idx=(" + String(idx) + " bytes)! wifi_password=" + wifi_password);
	www_username = "";	while (*(buff + idx) != 0) { www_username += static_cast<char>(*(buff + idx)); idx += sizeof(char); }; idx += sizeof(char);
	//logg.logging("3 loaded idx=(" + String(idx) + " bytes)! www_username=" + www_username);
	www_password = "";	while (static_cast<uint8_t>(*(buff + idx)) != 0) { www_password += static_cast<char>(*(buff + idx)); idx += sizeof(char); }; idx += sizeof(char);

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
	length =	sizeof(int) * 2 + 
				sizeof(float) * 6 + 
				sizeof(uint8_t) * 14 + 
				wifi_ssid.length() + 1 + 
				wifi_password.length() + 1 + 
				www_username.length() + 1 + 
				www_password.length() + 1;
	return length;
}



Config CONF;
