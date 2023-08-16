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

	pinMode(pin_a, INPUT); // Пины в режим приема INPUT 
	pinMode(pin_b, INPUT); // Пины в режим приема INPUT 
	pinMode(pin_btn, INPUT); // Пины в режим приема INPUT 
}

void Encoder::A() {
	int pinAValue = digitalRead(pin_a); // Получаем состояние пинов A и B 
	int pinBValue = digitalRead(pin_b);
	cli(); // Запрещаем обработку прерываний, чтобы не отвлекаться 
	if (pinAValue == LOW) {
		if (pinBValue == HIGH) state = 1; // Если при спаде линии А на линии B лог. единица, то вращение в одну сторону 
		else state = -1; // Если при спаде линии А на линии B лог. ноль, то вращение в другую сторону 
	}

	if (pinAValue == HIGH && state != 0)
	{
		if (state == 1 && pinBValue == LOW || state == -1 && pinBValue == HIGH)
		{ // Если на линии А снова единица, фиксируем шаг 
			if (state == 1) flagCW = true; // Флаг вращения по часовой стрелке 
			if (state == -1) flagCCW = true; // Флаг вращения против часовой стрелки 
			state = 0;
		}
	}
	sei(); // Разрешаем обработку прерываний 
}


void Encoder::Button() {
	//if (millis() - timeButtonDown < 50) return; 
	int pinButValue = digitalRead(pin_btn); // Получаем состояние пина кнопки 

	cli(); // Запрещаем обработку прерываний, чтобы не отвлекаться 
	timeButtonDown = millis(); // Запоминаем время нажатия/отжатия 
	if (pinButValue==LOW) { // При нажатии подается инвертированный сигнал 
		isButtonDown = true; // Устанавливаем флаг нажатия кнопки 
	}
	else if (isButtonDown) { // Если кнопка отжата, смотрим не было ли выполнено действие 
		if (!longPressReleased) { // Если долгое нажатие не было ни разу отработано, то... 
			flagButton = true; // Если не было удержания, ставим флаг события обычного нажатия 
		} 
		isButtonDown = false; // Сбрасываем флаг нажатия 
		longPressReleased = false; // Сбрасываем флаг длительного удержания 
	}
	sei(); // Разрешаем обработку прерываний 
}

void Encoder::process(long mls) {
	if (mls - timeButtonDown > timeButtonPressed && isButtonDown) { // Время длительного удержания наступило 
		flagButtonLong = true;
	}
	if (flagCW) { // Шаг вращения по часовой стрелке // ... 
		if (mode != NULL) mode->right();
		flagCW = false; // Действие обработано - сбрасываем флаг 
	}
	if (flagCCW) { // Шаг вращения против часовой стрелки // ...
		if (mode != NULL) mode->left();
		flagCCW = false; // Действие обработано - сбрасываем флаг 
	}
	if (flagButton) { // Кнопка нажата // ... 
		if (mode != NULL) mode->press();
		flagButton = false; // Действие обработано - сбрасываем флаг 
	}
	if (flagButtonLong && isButtonDown) { // Кнопка удерживается 
		if (!digitalRead(pin_btn) && mls - timeButtonDown > timeButtonPressed) { // Защита от ложного срабатывания // ... 
			if (mode != NULL) mode->long_press();
			
		}
		//=========================================== Настраиваем реакцию на долгое удержание кнопки ===============================================
		// Чтобы событие long_press во время удержания срботало только один раз, необходимо раскомментировать блок и закомментировать следующий
		isButtonDown = false;                   // Программно "отжимаем" кнопку
		// Эти две строки отвечают за то, чтобы при долгом удержании кнопки, событие long_press повторялось каждые 1,5 секунды
		// Для того, чтобы изменить это поведение нужно закомментировать две эти строки и раскомментировать строку из предыдущего блока
		//timeButtonDown = millis();            // Сбрасываем таймер
		//longPressReleased = true;             // Флаг срабатывания долгого удержания, чтобы отсечь генерацию обычного нажатия при отпускании кнопки
		//==========================================================================================================================================
		flagButtonLong = false; // Действие обработано - сбрасываем флаг 
	}
}


void Encoder::setHandler(ModeBase *m) {
	mode = m;
}