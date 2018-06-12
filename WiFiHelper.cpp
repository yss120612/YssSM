#include "WiFiHelper.h"

WiFiHelper::WiFiHelper(Config *c)
{
	conf = c;
}

WiFiHelper::~WiFiHelper()
{
}

void WiFiHelper::setup()
{
	
	WiFi.disconnect();
	//IPAddress apIP(192, 168, 0, 100);
	WiFi.mode(WIFI_STA);
	//WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
	//WiFi.softAP(conf->getWiFiN().c_str(), conf->getWiFiP().c_str());
	uint8_t modeWiFi = 0;
	int n_network = WiFi.scanNetworks(); // запрос количества доступных сетей
	for (int i = 0; i < n_network; ++i) {
		if (WiFi.SSID(i) == conf->getWiFiN().c_str()) modeWiFi = 1; // наша сеть присутствует
	}

if (modeWiFi == 1) {
		// пробуем подключиться
#ifdef _SERIAL
		Serial.printf("Connecting to %s\n", conf->getWiFiN().c_str());
#endif
		WiFi.disconnect(true);
		WiFi.begin(conf->getWiFiN().c_str(), conf->getWiFiP().c_str());
		// ждем N кол-во попыток, если нет, то AP Mode
		byte tmp_while = 0;
		while (WiFi.waitForConnectResult() != WL_CONNECTED) {
			delay(1000);
#ifdef _SERIAL
			Serial.print(".");
#endif
			if (tmp_while < 5) tmp_while++;
			else {
				modeWiFi = 0;
#ifdef _SERIAL
				Serial.printf("Connection to %s failed!\n", conf->getWiFiN().c_str());
#endif
				break;
			}
		}
	}
}

void WiFiHelper::reconnect()
{
	if (isConnected()) {
		return;
	}

	WiFi.reconnect();
#ifdef _SERIAL
	Serial.println("reconnect");
#endif
	// При потери связи с базовой станцией переходим в режим точки доступа и пробуем переподключиться
	/*if (conf->getWiFiN().length() && tCnt >= setRestartWiFi && !WiFi.softAPgetStationNum()) {
		WiFi.reconnect();
		Serial.println("reconnect");
	}*/
}

boolean WiFiHelper::isConnected()
{
	return WiFi.status() == WL_CONNECTED;
}

