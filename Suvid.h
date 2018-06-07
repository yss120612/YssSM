// Suvid.h

#ifndef _SUVID_h
#define _SUVID_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "Heater.h"
#include "DallasTerm.h"
#include "Beeper.h"
#include "Display.h"
#include "Mode.h"

#define SU_OFF  0 //начало
#define SU_FORSAJ  1 //разгон до temp_start
#define SU_WORK 2

#define SUEND_NO 0 //работаем
#define SUEND_TIME 1 //закончили по времени
#define SUEND_ERROR 2 //закончили аварийно

#define SUERR_OK 0 //нет ошибок
#define SUERR_NOTKUB 1 //нет градусника в кубе
#define SUERR_NOHEATER 2 //нет тена


const uint16_t test_time = 1000;

class Suvid : public Mode {
private:
	Heater * heater;
	DallasTerm * term;
	Beeper * beeper;
	int8_t targetT;
	long last_time;
	int8_t work_mode;
	int8_t end_reason;
	int8_t err;
	long time;
	void error(uint8_t);
	void draw();
public:
	Suvid(Display *d, Heater * he, DallasTerm * tr, Beeper * bee);
	void start(int8_t tm, uint16_t min);
	void stop();

	
	void process_suvid(long);
	int getHeaterPower() { return heater->getPower(); };
};


#endif

