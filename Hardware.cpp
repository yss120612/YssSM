// 
// 
// 

#include "Hardware.h"


Hardware::Hardware()
	:ow(TEMPERATURE_PIN),
	t_kube(tkube, &ow, 2.5),
	t_triak(tkube, &ow, 2.5),
	display(0x3C, SDA, SCL)
	
{
}

Hardware::~Hardware()
{
}

void Hardware::init()
{
	pinExtender.setup(EXT_LOCK, EXT_CLC, EXT_DATA);
	encoder.setup(ENC_A_PIN, ENC_B_PIN, ENC_BTN_PIN);
}

void Hardware::timed_process(long ms)
{
	t_kube.process(ms);
}

void Hardware::process(long ms)
{
	encoder.process(ms);
}


DallasTerm * Hardware::getTKube() { return &t_kube; }
DallasTerm * Hardware::getTTsarga() { return NULL; }
DallasTerm * Hardware::getTWater() { return NULL; }
DallasTerm * Hardware::getTTriak() { return &t_triak; }
//HttpHelper * Hardware::getHttpHelper() { return &httpHelper; }
Config * Hardware::getConfig() { return &config; }
Beeper * Hardware::getBeeper() { return &beeper; }
PinExtender * Hardware::getExtender() { return &pinExtender; }
MD_DS3231 * Hardware::getClock() { return &RTC; }
Encoder * Hardware::getEncoder(){ return &encoder;}
SSD1306Wire * Hardware::getDisplay() { return &display; }

/*void Hardware::setDisplay(SSD1306Wire * d) { display = d; }
void Hardware::setTKube(DallasTerm * k) { t_kube = k; }
void Hardware::setTTsarga(DallasTerm * t) { t_tsarga = t; }
void Hardware::setTTriak(DallasTerm * r) { t_triak = r; }
void Hardware::setTWater(DallasTerm * w) { t_water = w; }
void Hardware::setHttpHelper(HttpHelper * h) { httpHelper = h; }
void Hardware::setConfig(Config * c) { config = c; }
void Hardware::setBeeper(Beeper * b) { beeper = b; }
void Hardware::setExtender(PinExtender * p) { pinExtender = p; }
void Hardware::setClock(MD_DS3231 * cl){clock = cl;}*/

