// 
// 
// 

#include "Encoder.h"



Encoder::Encoder()
{
}


void Encoder::setup(uint8_t a, uint8_t b, uint8_t btn) {
	pin_a=a;
	pin_b = b;
	pin_btn = btn;

	pinMode(pin_a, INPUT); // ���� � ����� ������ INPUT 
	pinMode(pin_b, INPUT); // ���� � ����� ������ INPUT 
	pinMode(pin_btn, INPUT); // ���� � ����� ������ INPUT 
}

void Encoder::A() {
	int pinAValue = digitalRead(pin_a); // �������� ��������� ����� A � B 
	int pinBValue = digitalRead(pin_b);
	cli(); // ��������� ��������� ����������, ����� �� ����������� 
	if (pinAValue == LOW) {
		if (pinBValue == HIGH) state = 1; // ���� ��� ����� ����� � �� ����� B ���. �������, �� �������� � ���� ������� 
		else state = -1; // ���� ��� ����� ����� � �� ����� B ���. ����, �� �������� � ������ ������� 
	}

	if (pinAValue == HIGH && state != 0)
	{
		if (state == 1 && pinBValue == LOW || state == -1 && pinBValue == HIGH)
		{ // ���� �� ����� � ����� �������, ��������� ��� 
			if (state == 1) flagCW = true; // ���� �������� �� ������� ������� 
			if (state == -1) flagCCW = true; // ���� �������� ������ ������� ������� 
			state = 0;
		}
	}
	sei(); // ��������� ��������� ���������� 
}


void Encoder::Button() {
	//if (millis() - timeButtonDown < 50) return; 
	int pinButValue = digitalRead(pin_btn); // �������� ��������� ���� ������ 

	cli(); // ��������� ��������� ����������, ����� �� ����������� 
	timeButtonDown = millis(); // ���������� ����� �������/������� 
	if (pinButValue==LOW) { // ��� ������� �������� ��������������� ������ 
		isButtonDown = true; // ������������� ���� ������� ������ 
	}
	else if (isButtonDown) { // ���� ������ ������, ������� �� ���� �� ��������� �������� 
		if (!longPressReleased) { // ���� ������ ������� �� ���� �� ���� ����������, ��... 
			flagButton = true; // ���� �� ���� ���������, ������ ���� ������� �������� ������� 
		} 
		isButtonDown = false; // ���������� ���� ������� 
		longPressReleased = false; // ���������� ���� ����������� ��������� 
	}
	sei(); // ��������� ��������� ���������� 
}

void Encoder::process(long mls) {
	if (mls - timeButtonDown > timeButtonPressed && isButtonDown) { // ����� ����������� ��������� ��������� 
		flagButtonLong = true;
	}
	if (flagCW) { // ��� �������� �� ������� ������� // ... 
		if (mode != NULL) mode->right();
		flagCW = false; // �������� ���������� - ���������� ���� 
	}
	if (flagCCW) { // ��� �������� ������ ������� ������� // ...
		if (mode != NULL) mode->left();
		flagCCW = false; // �������� ���������� - ���������� ���� 
	}
	if (flagButton) { // ������ ������ // ... 
		if (mode != NULL) mode->press();
		flagButton = false; // �������� ���������� - ���������� ���� 
	}
	if (flagButtonLong && isButtonDown) { // ������ ������������ 
		if (!digitalRead(pin_btn) && mls - timeButtonDown > timeButtonPressed) { // ������ �� ������� ������������ // ... 
			if (mode != NULL) mode->long_press();
			
		}
		//=========================================== ����������� ������� �� ������ ��������� ������ ===============================================
		// ����� ������� long_press �� ����� ��������� �������� ������ ���� ���, ���������� ����������������� ���� � ���������������� ���������
		isButtonDown = false;                   // ���������� "��������" ������
		// ��� ��� ������ �������� �� ��, ����� ��� ������ ��������� ������, ������� long_press ����������� ������ 1,5 �������
		// ��� ����, ����� �������� ��� ��������� ����� ���������������� ��� ��� ������ � ����������������� ������ �� ����������� �����
		//timeButtonDown = millis();            // ���������� ������
		//longPressReleased = true;             // ���� ������������ ������� ���������, ����� ������ ��������� �������� ������� ��� ���������� ������
		//==========================================================================================================================================
		flagButtonLong = false; // �������� ���������� - ���������� ���� 
	}
}


void Encoder::setHandler(ModeBase *m) {
	mode = m;
}