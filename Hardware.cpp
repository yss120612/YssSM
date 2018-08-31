// 
// 
// 

#include "Hardware.h"


Hardware::Hardware()
	:ow(TEMPERATURE_PIN),
	t_kube(term_addr[T_KUBE], &ow, 1.94),
	t_triak(term_addr[T_TRIAK], &ow, 2.5),
	t_tsarga(term_addr[T_TSARGA], &ow, 1.29),
	t_tsa(term_addr[T_TSA], &ow, 1.53),
	display(0x3C, SDA, SCL)
	
{
}

Hardware::~Hardware()
{
}

void Hardware::init()
{
	pinExtender.setup(EXT_LOCK, EXT_CLC, EXT_DATA);
	mult.setup(A0, EX_PIN0, EX_PIN1, EX_PIN2, EX_PIN3, &pinExtender);
	encoder.setup(ENC_A_PIN, ENC_B_PIN, ENC_BTN_PIN);
	uroven.setup(WS1_PIN, WS1_PWR_PIN, &mult, &pinExtender);
	flood.setup(WS2_PIN, WS2_PWR_PIN, &mult, &pinExtender);
	t_kube.set12bit();
	t_tsarga.set12bit();
	t_tsa.set12bit();
	t_triak.set12bit();
	at24mem.begin();
}

void Hardware::timed_process(long ms)
{
	t_kube.process(ms);
	t_tsarga.process(ms);
	t_tsa.process(ms);
	t_triak.process(ms);
	uroven.process(ms);
	flood.process(ms);
}

void Hardware::process(long ms)
{
	encoder.process(ms);
}


DallasTerm * Hardware::getTKube() { return &t_kube; }
DallasTerm * Hardware::getTTsarga() { return &t_tsarga; }
DallasTerm * Hardware::getTWater() { return NULL; }
DallasTerm * Hardware::getTTriak() { return &t_triak; }
DallasTerm * Hardware::getTTSA() { return &t_tsa; }
//HttpHelper * Hardware::getHttpHelper() { return &httpHelper; }
Config * Hardware::getConfig() { return &config; }
Beeper * Hardware::getBeeper() { return &beeper; }
PinExtender * Hardware::getExtender() { return &pinExtender; }
MD_DS3231 * Hardware::getClock() { return &RTC; }
Encoder * Hardware::getEncoder(){ return &encoder;}
SSD1306Wire * Hardware::getDisplay() { return &display; }
AT24C32 * Hardware::getAT24mem() { return &at24mem; }
RTCmemory * Hardware::getRTCmem() { return &RTCmem; }
Multiplexor * Hardware::getMultiplexor(){ return &mult;}
WaterSensor * Hardware::getUrovenWS(){	return &uroven;}
WaterSensor * Hardware::getFloodWS(){	return &flood;}

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

