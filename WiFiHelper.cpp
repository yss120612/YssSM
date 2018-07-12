#include "WiFiHelper.h"
#include "Log.h"
#include "Config.h"

//#define _SERIAL

WiFiHelper::WiFiHelper()
{
	//conf = c;
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
		logg.logging("network " + WiFi.SSID(i) + " present");
		if (WiFi.SSID(i).equals(CONF.getWiFiN()))
		{
			modeWiFi = 1; // ���� ���� ������������
			break;
		}
		
	}

if (modeWiFi == 1) {
		// ������� ������������

		logg.logging("Connecting to "+ CONF.getWiFiN());

		WiFi.disconnect(true);
		WiFi.begin(CONF.getWiFiN().c_str(), CONF.getWiFiP().c_str());
		// ���� N ���-�� �������, ���� ���, �� AP Mode
		byte tmp_while = 0;
		while (WiFi.waitForConnectResult() != WL_CONNECTED) {
			delay(1000);

			logg.logging("Connecting to "+CONF.getWiFiN());

			if (tmp_while < 5) tmp_while++;
			else {
				modeWiFi = 0;
			logg.logging("Connection to "+ CONF.getWiFiN() +" failed!");

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
	logg.logging("Reconnect...");

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

