// 
// 
// 

#include "Log.h"
#include "Config.h"

Config::Config()
{
	changed = false;
	version = 8;
}

Config::~Config()
{
}

void Config::loadDefaults() {

	wifi_ssid = "Yss_GIGA";
	wifi_password = "bqt3bqt3";
	//wifi_ssid = "ROSTELEKOM-42";
	//wifi_password = "123qweasdzxc";
	www_username = "admin";
	www_password = "esp";
	scrSaverMin = 1;
	suvidMin = 60;
	suvidTemp = 60;
	
	brewingMin1 = 60;
	brewingTemp1 = 90;
	//brewingMin2 =20;//из рецепта
	brewingMin2 = 0;
	brewingTemp2 = 75;
	//brewingMin3 = 10;
	brewingMin3 = 0;
	brewingTemp3 = 88;
	//brewingMin4 = 10;
	brewingMin4 = 0;
	brewingTemp4 = 96;
	
	breCoolingTemp = 25;
	breKranOpened = 21.0f;

	distKranOpened = 21.1f;
	distStopTemp = 98.8f;
	distWorkPower = 42;
	distForsajTemp = 57;
	
	manualKranOpened = 19.5f;
	manualWorkPower = 42;
	
	rectWorkSlf = 20;
	rectKranOpened = 20.7f;
	rectHeadKranOpened = 21.0f;
	rectStopTemp = 82.8f;
	rectWorkPower=32;
	rectHeadPower = 32;
	rectForsajTemp = 41;
	
	TSAmin = 28;
	TSAmax = 50;
	TSAcritical = 90;
	
	triakCoolerTemp = 50;
	triakCoolerGist = 10;
}

boolean Config::checkVersion()
{
	uint8_t v =
#ifndef HAVE_AT24C32
		0;
#else
		at24mem->read(0);
#endif
	return v == version;
}

void Config::setHttp(const String n, const  String p) {
	if (!www_username.equals(n) || !www_password.equals(p)) changed = true;
	www_username=n;
	www_password=p;
	write();
}


void Config::setWiFi(const String n, const String p) {
	if (!wifi_ssid.equals(n) || !wifi_password.equals(p)) changed = true;
	wifi_ssid = n;
	wifi_password = p;
	write();
}



void Config::setScrSavMin(int ss)
{
	if (scrSaverMin != ss) changed = true;
	scrSaverMin = ss;
	write();
}

void Config::setSuvidMin(int sm)
{
	if (suvidMin != sm) changed = true;
	suvidMin = sm;
	write();
}


void Config::setSuvidTemp(uint8_t st)
{
	if (suvidTemp != st) changed = true;
	suvidTemp = st;
	write();
}


void Config::setBrewingMin1(int sm)
{
	if (brewingMin1 != sm) changed = true;
	brewingMin1 = sm;
	write();
}


void Config::setBrewingTemp1(uint8_t st)
{
	if (brewingTemp1 != st) changed = true;
	brewingTemp1 = st;
	write();
}

void Config::setBrewingMin2(int sm)
{
	if (brewingMin2 != sm) changed = true;
	brewingMin2 = sm;
	write();
}


void Config::setBrewingTemp2(uint8_t st)
{
	if (brewingTemp2 != st) changed = true;
	brewingTemp2 = st;
	write();
}

void Config::setBrewingMin3(int sm)
{
	if (brewingMin3 != sm) changed = true;
	brewingMin3 = sm;
	write();
}


void Config::setBrewingTemp3(uint8_t st)
{
	if (brewingTemp3 != st) changed = true;
	brewingTemp3 = st;
	write();
}

void Config::setBrewingMin4(int sm)
{
	if (brewingMin4 != sm) changed = true;
	brewingMin4 = sm;
	write();
}


void Config::setBrewingTemp4(uint8_t st)
{
	if (brewingTemp4 != st) changed = true;
	brewingTemp4 = st;
	write();
}

void Config::setBrewingCoolingTemp(uint8_t st)
{
	if (breCoolingTemp != st) changed = true;
	breCoolingTemp = st;
	write();
}


void Config::setBrewingKran(float st)
{
	if (breKranOpened != st) changed = true;
	breKranOpened = st;
	write();
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

void Config::setRectWorkPower(uint8_t st)
{
	if (rectWorkPower != st) changed = true;
	rectWorkPower = st;
	write();
}

void Config::setRectWorkSelf(uint8_t st)
{
	if (rectWorkSlf != st) changed = true;
	rectWorkSlf = st;
	write();
}

void Config::setRectHeadPower(uint8_t st)
{
	if (rectHeadPower != st) changed = true;
	rectHeadPower = st;
	write();
}

void Config::setRectStopTemp(float st)
{
	//if (rectStopTemp != st) changed = true;
	rectStopTemp = st;
	//write();
}

void Config::setRectKranOpened(float st)
{
	if (rectKranOpened != st) changed = true;
	rectKranOpened = st;
	write();
}

void Config::setRectHeadKranOpened(float st)
{
	if (rectHeadKranOpened != st) changed = true;
	rectHeadKranOpened = st;
	write();
}

void Config::setRectForsajTemp(uint8_t st)
{
	if (rectForsajTemp != st) changed = true;
	rectForsajTemp = st;
	write();
}

void Config::setDistWorkPower(uint8_t st)
{
	if (distWorkPower != st) changed = true;
	distWorkPower = st;
	write();
}

void Config::setDistStopTemp(float st)
{
	if (distStopTemp != st) changed = true;
	distStopTemp = st;
	write();
}

void Config::setDistKranOpened(float st)
{
	if (distKranOpened != st) changed = true;
	distKranOpened = st;
	write();
}

void Config::setDistForsajTemp(uint8_t st)
{
	if (distForsajTemp != st) changed = true;
	distForsajTemp = st;
	write();
}

void Config::setManualWorkPower(uint8_t st)
{
	if (manualWorkPower != st) changed = true;
	manualWorkPower = st;
	write();
}

void Config::setManualKranOpened(float st)
{
	if (manualKranOpened != st) changed = true;
	manualKranOpened = st;
	write();
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


const String Config::getHttpU() { return www_username; };
const String Config::getHttpP() { return www_password; };
const String Config::getWiFiN() { return wifi_ssid; };
const String Config::getWiFiP() { return wifi_password; }
const int Config::getScrSavMin(){ return scrSaverMin;}

const int Config::getSuvidMin(){ return suvidMin;}
const uint8_t Config::getSuvidTemp(){return suvidTemp;}


const int Config::getBrewingMin1() { return brewingMin1; }
const uint8_t Config::getBrewingTemp1() { return brewingTemp1; }
const int Config::getBrewingMin2() { return brewingMin2; }
const uint8_t Config::getBrewingTemp2() { return brewingTemp2; }
const int Config::getBrewingMin3() { return brewingMin3; }
const uint8_t Config::getBrewingTemp3() { return brewingTemp3; }
const int Config::getBrewingMin4() { return brewingMin4; }
const uint8_t Config::getBrewingTemp4() { return brewingTemp4; }
const float Config::getBrewingKran(){	return breKranOpened;}
const uint8_t Config::getBrewingCoolingTemp(){	return breCoolingTemp;}


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
	//memcpy((buff + idx), &rectStopTemp,		sizeof(float)); idx += sizeof(float);
	memcpy((buff + idx), &rectKranOpened,	sizeof(float)); idx += sizeof(float);
	memcpy((buff + idx), &rectHeadKranOpened,	sizeof(float)); idx += sizeof(float);
	memcpy((buff + idx), &manualKranOpened, sizeof(float)); idx += sizeof(float);
	memcpy((buff + idx), &breKranOpened, sizeof(float)); idx += sizeof(float);

	memcpy((buff + idx), &scrSaverMin,		sizeof(int));	idx += sizeof(int);
	memcpy((buff + idx), &suvidMin,			sizeof(int));	idx += sizeof(int);
	memcpy((buff + idx), &brewingMin1, sizeof(int));	idx += sizeof(int);
	memcpy((buff + idx), &brewingMin2, sizeof(int));	idx += sizeof(int);
	memcpy((buff + idx), &brewingMin3, sizeof(int));	idx += sizeof(int);
	memcpy((buff + idx), &brewingMin4, sizeof(int));	idx += sizeof(int);


	*(buff + idx++) = suvidTemp;
	*(buff + idx++) = brewingTemp1;
	*(buff + idx++) = brewingTemp2;
	*(buff + idx++) = brewingTemp3;
	*(buff + idx++) = brewingTemp4;
	*(buff + idx++) = breCoolingTemp;
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
	
	/*distStopTemp =			 static_cast<float>(*(buff + idx)); idx += sizeof(float);
	distKranOpened = static_cast<float>(*(buff + idx)); idx += sizeof(float);
	rectStopTemp = static_cast<float>(*(buff + idx)); idx += sizeof(float);
	rectKranOpened = static_cast<float>(*(buff + idx)); idx += sizeof(float);
	rectHeadKranOpened = static_cast<float>(*(buff + idx)); idx += sizeof(float);
	manualKranOpened	= static_cast<float>(*(buff + idx)); idx += sizeof(float);*/

	memcpy(&distStopTemp,(buff + idx),  sizeof(float)); idx += sizeof(float);
	memcpy(&distKranOpened, (buff + idx),  sizeof(float)); idx += sizeof(float);
	//memcpy(&rectStopTemp, (buff + idx), sizeof(float)); idx += sizeof(float);
	memcpy(&rectKranOpened, (buff + idx), sizeof(float)); idx += sizeof(float);
	memcpy(&rectHeadKranOpened, (buff + idx), sizeof(float)); idx += sizeof(float);
	memcpy(&manualKranOpened, (buff + idx),sizeof(float)); idx += sizeof(float);
	memcpy(&breKranOpened, (buff + idx), sizeof(float)); idx += sizeof(float);

	scrSaverMin =		static_cast<int>(*(buff + idx)); idx += sizeof(int);
	suvidMin = static_cast<int>(*(buff + idx)); idx += sizeof(int);
	brewingMin1 = static_cast<int>(*(buff + idx)); idx += sizeof(int);
	brewingMin2 = static_cast<int>(*(buff + idx)); idx += sizeof(int);
	brewingMin3 = static_cast<int>(*(buff + idx)); idx += sizeof(int);
	brewingMin4 = static_cast<int>(*(buff + idx)); idx += sizeof(int);
		
	suvidTemp =			static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	brewingTemp1 = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	brewingTemp2 = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	brewingTemp3 = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	brewingTemp4 = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);
	breCoolingTemp = static_cast<uint8_t>(*(buff + idx)); idx += sizeof(uint8_t);

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
	
	wifi_ssid = "";		while (*(buff + idx) != 0) { wifi_ssid += static_cast<char>(*(buff + idx)); idx += sizeof(char); }; idx += sizeof(char);
	wifi_password = ""; while (*(buff + idx) != 0) { wifi_password += static_cast<char>(*(buff + idx)); idx += sizeof(char); }; idx += sizeof(char);
	www_username = "";	while (*(buff + idx) != 0) { www_username += static_cast<char>(*(buff + idx)); idx += sizeof(char); }; idx += sizeof(char);
	www_password = "";	while (*(buff + idx) != 0) { www_password += static_cast<char>(*(buff + idx)); idx += sizeof(char); }; idx += sizeof(char);

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
	length =	sizeof(int) * 6 + 
				sizeof(float) * 6 + 
				sizeof(uint8_t) * 19 + 
				wifi_ssid.length() + 1 + 
				wifi_password.length() + 1 + 
				www_username.length() + 1 + 
				www_password.length() + 1;
	return length;
}



Config CONF;
