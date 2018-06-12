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

#define SU_OFF  0 //������
#define SU_FORSAJ  1 //������ �� temp_start
#define SU_WORK 2

#define SUEND_NO 0 //��������
#define SUEND_TIME 1 //��������� �� �������
#define SUEND_ERROR 2 //��������� ��������

#define SUERR_OK 0 //��� ������
#define SUERR_NOTKUB 1 //��� ���������� � ����
#define SUERR_NOHEATER 2 //��� ����


const uint16_t test_time = 1000;

class Suvid : public Mode {
private:
	int8_t targetT;
	long last_time;
	int8_t work_mode;
	int8_t end_reason;
	int8_t err;
	long time;
	void error(uint8_t);
	void draw();
	void left();
	void right();
	void press();
	void long_press();
public:
	Suvid(Hardware *h);
	void start(int8_t tm, uint16_t min);
	void stop();

	
	void process_suvid(long);
	int getHeaterPower() { return hardware->getHeater()->getPower(); };
};


#endif

