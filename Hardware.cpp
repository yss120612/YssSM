// 
// 
// 

#include "Hardware.h"


Hardware::Hardware()
{
}

Hardware::~Hardware()
{
}


Heater * Hardware::getHeater() { return heater; }
Display * Hardware::getDisplay() { return display; }
DallasTerm * Hardware::getTKube() { return t_kube; }
DallasTerm * Hardware::getTTsarga() { return t_tsarga; }
DallasTerm * Hardware::getTWater() { return t_water; }
DallasTerm * Hardware::getTTriak() { return t_triak; }
HttpHelper * Hardware::getHttpHelper() { return httpHelper; }
Config * Hardware::getConfig() { return config; }
Beeper * Hardware::getBeeper() { return beeper; }
PinExtender * Hardware::getExtender() { return pinExtender; }

MD_DS3231 * Hardware::getClock()
{
	return clock;
}

void Hardware::setHeater(Heater * h) { heater = h; }
void Hardware::setDisplay(Display * d) { display = d; }
void Hardware::setTKube(DallasTerm * k) { t_kube = k; }
void Hardware::setTTsarga(DallasTerm * t) { t_tsarga = t; }
void Hardware::setTTriak(DallasTerm * r) { t_triak = r; }
void Hardware::setTWater(DallasTerm * w) { t_water = w; }
void Hardware::setHttpHelper(HttpHelper * h) { httpHelper = h; }
void Hardware::setConfig(Config * c) { config = c; }
void Hardware::setBeeper(Beeper * b) { beeper = b; }
void Hardware::setExtender(PinExtender * p) { pinExtender = p; }

void Hardware::setClock(MD_DS3231 * cl)
{
	clock = cl;
}
