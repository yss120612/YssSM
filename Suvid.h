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
#include "Termopause.h"


#define SU_OFF  0 //������
#define SU_FORSAJ  1 //������ �� temp_start
#define SU_WORK 2

#define SUEND_NO 0 //��������
#define SUEND_TIME 1 //��������� �� �������
#define SUEND_ERROR 2 //��������� ��������

#define SUERR_OK 0 //��� ������
#define SUERR_NOTKUB 1 //��� ���������� � ����
#define SUERR_NOHEATER 2 //��� ����



const uint16_t test_time = 5000;//5 ������

class Suvid : public Mode {
public:
	Suvid(Aggregates * a, Hardware *h);
	void start();
	void stop();

	
	void process(long ms);
	//int getHeaterPower() { return hardware->getHeater()->getPower(); };
protected:
	void armAlarm();
	TermoPause tpause;
	long last_time;
	int8_t work_mode;
	int8_t end_reason;
	int8_t err;
	//long time;
	void error(uint8_t);
	void draw(long m);
	void initDraw();
	void left();
	void right();
	void press();
	void long_press();
	void makeMenu();
	void command(uint8_t id);
	void initParams(MenuParameter * mp);
	void acceptParams(MenuParameter * mp);
};


#endif

