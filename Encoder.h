// Encoder.h

#ifndef _ENCODER_h
#define _ENCODER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//#include "Mode.h"

class ModeBase
{
public:
	virtual void left() {  }
	virtual void right() {  }
	virtual void press() {  }
	virtual void long_press() { }
protected:
	long last_action;
	boolean ss_active;
};

class Encoder
{
public:
	Encoder();
	void setup(uint8_t a, uint8_t b, uint8_t btn);
	void process(long mls);
	void A();
	void Button();
	void setHandler(ModeBase * m);
private:
	
	uint8_t pin_a;
	uint8_t pin_b;
	uint8_t pin_btn;
	ModeBase * mode;
	const long timeButtonPressed = 1500; // Долгое удержание кнопки после 1,5 секунд volatile 
	int8_t state = 0; // Переменная хранящая статус вращения 
				   // Переменные хранящие состояние действия до его выполнения 
	volatile bool flagCW = false; // Было ли вращение по часовой стрелке 
	volatile bool flagCCW = false; // Было ли вращение против часовой стрелки 
	volatile bool flagButton = false; // Было ли нажатие кнопки 
	volatile bool flagButtonLong = false; // Было ли долгое удержание кнопки 
	volatile long timeButtonDown = 0; // Переменная хранящая время нажатия кнопки 
	volatile bool isButtonDown = false; // Переменная хранящая время нажатия кнопки 
	volatile bool longPressReleased = false; // Переменная для фиксации срабатывания долгого нажатия 

};




#endif

