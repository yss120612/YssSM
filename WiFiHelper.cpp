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
	int n_network = WiFi.scanNetworks(); // ������ ���������� ��������� �����
	for (int i = 0; i < n_network; ++i) {
		if (WiFi.SSID(i) == conf->getWiFiN().c_str()) modeWiFi = 1; // ���� ���� ������������
	}

if (modeWiFi == 1) {
		// ������� ������������
#ifdef _SERIAL
		Serial.printf("Connecting to %s\n", conf->getWiFiN().c_str());
#endif
		WiFi.disconnect(true);
		WiFi.begin(conf->getWiFiN().c_str(), conf->getWiFiP().c_str());
		// ���� N ���-�� �������, ���� ���, �� AP Mode
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
	// ��� ������ ����� � ������� �������� ��������� � ����� ����� ������� � ������� ����������������
	/*if (conf->getWiFiN().length() && tCnt >= setRestartWiFi && !WiFi.softAPgetStationNum()) {
		WiFi.reconnect();
		Serial.println("reconnect");
	}*/
}

boolean WiFiHelper::isConnected()
{
	return WiFi.status() == WL_CONNECTED;
}

