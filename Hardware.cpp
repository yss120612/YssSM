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
	at24mem.begin();
	pinExtender.setup();
	mult.setup(A0, MP_PIN0, MP_PIN1, MP_PIN2, MP_PIN3, &pinExtender);
	encoder.setup(ENC_A_PIN, ENC_B_PIN, ENC_BTN_PIN);
	uroven.setup(WS1_PIN, WS1_PWR_PIN, &mult, &pinExtender);
	flood.setup(WS2_PIN, WS2_PWR_PIN, &mult, &pinExtender);
	t_kube.set12bit();
	t_tsarga.set12bit();
	t_tsa.set12bit();
	t_triak.set12bit();
	beeper.setup(BEEPER_PIN);
	pump.setup(PUMP_PIN, &pinExtender);
	//flood.setLimit(25);
	//flood.arm();
	
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
Pump * Hardware::getPump(){	return &pump;}

void Hardware::setAlarm(int minutes)
{
		RTC.now();
		uint minutes = minutes % 60;
		uint hours = minutes / 60;
		RTC.m += minutes;
		if (RTC.m >= 60) {
			RTC.m -= 60;
			hours += 1;
		}
		RTC.h += hours;
		if (RTC.h >= 24)
		{
			RTC.h -= 24;
			RTC.dd += 1;
		}

		switch (RTC.mm) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
			if (RTC.dd > 31)
			{
				RTC.dd = 1;
				RTC.mm += 1;
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if (RTC.dd > 30) RTC.dd = 1;
			break;
		case 2:
			if (RTC.yyyy % 4 == 0) {
				if (RTC.dd > 29)
				{
					RTC.dd = 1;
					RTC.mm += 1;
				}
			}
			else {
				if (RTC.dd > 28)
				{
					RTC.dd = 1;
					RTC.mm += 1;
				}
			}
			break;
		case 12:
			if (RTC.dd > 31)
			{
				RTC.dd = 1;
				RTC.mm = 1;
				RTC.yyyy += 1;
			}
			break;



		}
		RTC.writeAlarm2(DS3231_ALM_DTHM);

	
}

void Hardware::timeLeft(char * buff) {
	RTC.readAlarm2();
	int8_t dd = RTC.dd;
	int8_t h = RTC.h;
	int8_t m = RTC.m;
	int8_t s = 0;
	RTC.now();
	s -= RTC.s;
	if (s < 0)
	{
		m -= 1;
		s += 60;
	}

	m -= RTC.m;
	if (m < 0)
	{
		h -= 1;
		m += 60;
	}
	h -= RTC.h;
	if (h < 0) h += 24;
	sprintf(buff, "%02d:%02d:%02d", h, m, s);
}


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

