// Config.h

#ifndef _CONFIG_h
#define _CONFIG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "AT24C32.h"

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

	void setTriakCoolerTemp(uint8_t st);
	void setTriakCoolerGist(uint8_t st);

	void setDistWorkPower(uint8_t st);
	void setDistStopTemp(float st);
	void setDistKranOpened(float st);
	void setDistForsajTemp(uint8_t st);
	
	void setTSAmin(uint8_t st);
	void setTSAmax(uint8_t st);
	void setTSAcritical(uint8_t st);

	const String getHttpU();
	const String getHttpP();
	const String getWiFiN();
	const String getWiFiP();
	const int getScrSavMin();

	const int getSuvidMin();
	const uint8_t getSuvidTemp();

	const uint8_t getDistWorkPower();
	const float getDistStopTemp();
	const float getDistKranOpened();
	const uint8_t getDistForsajTemp();

	const uint8_t getTriakCoolerTemp();
	const uint8_t getTriakCoolerGist();

	const uint8_t getTSAmin();
	const uint8_t getTSAmax();
	const uint8_t getTSAcritical();
	void setMem(AT24C32 * mem) { at24mem = mem; }
	void write();
	void read();

private:
	uint16_t length;
	uint16_t calcLength();
	boolean changed;
	AT24C32 * at24mem;

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
};

extern Config CONF;

#endif

