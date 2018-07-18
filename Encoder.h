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
	const long timeButtonPressed = 1500; // ������ ��������� ������ ����� 1,5 ������ volatile 
	int8_t state = 0; // ���������� �������� ������ �������� 
				   // ���������� �������� ��������� �������� �� ��� ���������� 
	volatile bool flagCW = false; // ���� �� �������� �� ������� ������� 
	volatile bool flagCCW = false; // ���� �� �������� ������ ������� ������� 
	volatile bool flagButton = false; // ���� �� ������� ������ 
	volatile bool flagButtonLong = false; // ���� �� ������ ��������� ������ 
	volatile long timeButtonDown = 0; // ���������� �������� ����� ������� ������ 
	volatile bool isButtonDown = false; // ���������� �������� ����� ������� ������ 
	volatile bool longPressReleased = false; // ���������� ��� �������� ������������ ������� ������� 

};




#endif

