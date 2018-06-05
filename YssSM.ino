#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
//#include <U8glib.h>
//#include <U8g2lib.h>
#include <OneWire.h>
#include <Wire.h>  
#include "SSD1306Wire.h"
#include "DallasTerm.h"
#include "images.h"

#define MODE_MAIN 0
#define MODE_SUVID 1
#define MODE_DISCIL 2
#define MODE_RECTIFY 3
#define MODE_SETUP 99

uint8_t mode;//Режим работы устройства в данный момент
long scrLoop = 0;

const char* ssid = "Yss_GIGA";
const char* password = "bqt3bqt3";

ESP8266WebServer server(80);

const char* www_username = "admin";
const char* www_password = "esp";

//const uint8_t COOLER_PIN = 3;
//const uint8_t LEFT_BTN_PIN = 4;
//const uint8_t WATER_OPEN_PIN = 5;
//const uint8_t WATER_CLOSE_PIN = 6;
//const uint8_t CENTER_BTN_PIN = 7;
//const uint8_t RIGHT_BTN_PIN = 8;
//const uint8_t RELAY_PIN = 9;
//const uint8_t HEATER_PIN = 9;
const uint8_t TEMPERATURE_PIN = D3;
//const uint8_t UROVEN_VCC_PIN = 11;
const uint8_t BEEPER_PIN = D4;

//const uint8_t CLOCK_RST_PIN = 3;
//const uint8_t CLOCK_DAT_PIN = 5;
//const uint8_t CLOCK_CLK_PIN = 6;

//const uint8_t TERMISTOR_PIN = A0;
//const uint8_t WATER_MEASURE_PIN = 11;
//const uint8_t UROVEN_PIN = D0;



OneWire ds(TEMPERATURE_PIN);
uint8_t  tkube[] = { 0x28,0xFF,0x73,0x37,0x67,0x14,0x02,0x11 };
DallasTerm kube_temp(tkube, &ds, 2.5);

SSD1306Wire display(0x3C, SDA, SCL);

//SSD1306Brzo display(ADDRESS, SDA, SDC);

//U82GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

//U8G2_SSD1306_128X64_ALT0_1_2ND_HW_I2C display(U8G2_R0);
//#define DEMO_DURATION 3000
//typedef void(*Demo)(void);





void setup() {
	Serial.begin(115200);
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	if (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("WiFi Connect Failed! Rebooting...");
		delay(1000);
		ESP.restart();
	}
	ArduinoOTA.begin();
	
	server.on("/", []() {
		if (!server.authenticate(www_username, www_password))
			return server.requestAuthentication();
		server.send(200, "text/plain", "Login OK");
	});

	server.on("/aaa", []() {
		if (!server.authenticate(www_username, www_password))
			return server.requestAuthentication();
		server.send(200, "text/plain", "Login OK on AAA");
		tone(BEEPER_PIN, 1000);
		//digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
										  // but actually the LED is on; this is because 
										  // it is active low on the ESP-01)
		delay(1000);                      // Wait for a second
		//digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
		noTone(BEEPER_PIN);
	});

	server.begin();

	pinMode(BEEPER_PIN, OUTPUT);

	display.init();
	display.flipScreenVertically();
	display.setFont(ArialMT_Plain_10);
	display.flipScreenVertically();

	mode = MODE_MAIN;
	pinMode(FUNC_GPIO10,OUTPUT);

	Serial.print("Open http://");
	Serial.print(WiFi.localIP());
	Serial.println("/ in your browser to see it working");
}

long mls;
void loop() {
	ArduinoOTA.handle();
	server.handleClient();
	mls = millis();
	if (scrLoop + 1000 - mls < 0) {
		kube_temp.process(mls);

		display.clear();
		// draw the current demo method
		//demos[demoMode]();

		display.setTextAlignment(TEXT_ALIGN_LEFT);
		display.drawString(10, 22, String(millis()));
		display.display();
		scrLoop = mls;
		draw();
		//digitalWrite(FUNC_GPIO10, !digitalRead(FUNC_GPIO10));
	//	draw();
	}
	/*display.firstPage();
	do {
		draw();
	} while (display.nextPage());
*/
}
void draw(void) {
	switch (mode)
	{
	case MODE_MAIN:
		break;
	default:
		break;
	}


	
	display.clear();
	display.drawString(0, 0,String(kube_temp.getTemp()));
	display.display();
	
	
	
}


void drawFontFaceDemo() {
	// Font Demo1
	// create more fonts at http://oleddisplay.squix.ch/
	display.setTextAlignment(TEXT_ALIGN_LEFT);
	display.setFont(ArialMT_Plain_10);
	display.drawString(0, 0, "Hello world");
	display.setFont(ArialMT_Plain_16);
	display.drawString(0, 10, "Hello world");
	display.setFont(ArialMT_Plain_24);
	display.drawString(0, 26, "Hello world");
}

void drawTextFlowDemo() {
	display.setFont(ArialMT_Plain_10);
	display.setTextAlignment(TEXT_ALIGN_LEFT);
	display.drawStringMaxWidth(0, 0, 128,
		"Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore.");
}

void drawTextAlignmentDemo() {
	// Text alignment demo
	display.setFont(ArialMT_Plain_10);

	// The coordinates define the left starting point of the text
	display.setTextAlignment(TEXT_ALIGN_LEFT);
	display.drawString(0, 10, "Left aligned (0,10)");

	// The coordinates define the center of the text
	display.setTextAlignment(TEXT_ALIGN_CENTER);
	display.drawString(64, 22, "Center aligned (64,22)");

	// The coordinates define the right end of the text
	display.setTextAlignment(TEXT_ALIGN_RIGHT);
	display.drawString(128, 33, "Right aligned (128,33)");
}

void drawRectDemo() {
	// Draw a pixel at given position
	for (int i = 0; i < 10; i++) {
		display.setPixel(i, i);
		display.setPixel(10 - i, i);
	}
	display.drawRect(12, 12, 20, 20);

	// Fill the rectangle
	display.fillRect(14, 14, 17, 17);

	// Draw a line horizontally
	display.drawHorizontalLine(0, 40, 20);

	// Draw a line horizontally
	display.drawVerticalLine(40, 0, 20);
}

void drawCircleDemo() {
	for (int i = 1; i < 8; i++) {
		display.setColor(WHITE);
		display.drawCircle(32, 32, i * 3);
		if (i % 2 == 0) {
			display.setColor(BLACK);
		}
		display.fillCircle(96, 32, 32 - i * 3);
	}
}

void drawProgressBarDemo() {
	int progress = (10 / 5) % 100;
	// draw the progress bar
	display.drawProgressBar(0, 32, 120, 10, progress);

	// draw the percentage as String
	display.setTextAlignment(TEXT_ALIGN_CENTER);
	display.drawString(64, 15, String(progress) + "%");
}

void drawImageDemo() {
	// see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
	// on how to create xbm files
	display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
}


