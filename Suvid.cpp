// 
// 
// 

#include "Suvid.h"

Suvid::Suvid(Hardware *h) : Mode(h) {
	targetT = 0;
	last_time = 0;
}

void Suvid::draw() {

}
void Suvid::left() {
#ifdef _SERIAL
	Serial.println("left");
#endif // _SERIAL
}
void Suvid::right() {
#ifdef _SERIAL
	Serial.println("right");
#endif // _SERIAL

}
void Suvid::press() {
#ifdef _SERIAL
	Serial.println("press");
#endif // _SERIAL
}
void Suvid::long_press() {
#ifdef _SERIAL
	Serial.println("long_press");
#endif // _SERIAL
}

void Suvid::makeMenu()
{
}


void Suvid::process_suvid(long ms) {
	if (work_mode == SU_OFF) return;
	if (last_time + test_time - ms >0) return;
	last_time = ms;



	if (work_mode == SU_WORK && time - ms < 0) {
		end_reason = SUEND_TIME;
		stop();
		hardware->getBeeper()->beep(1000, 5000);
		return;
	}


	float tmp = hardware->getTKube()->getTemp();

	if (tmp >= targetT && work_mode == SU_FORSAJ) {//вышли на рабочий режим
		work_mode = SU_WORK;
		hardware->getBeeper()->beep(1000, 500);
		time = ms + time * 60000L;
	}

	if (work_mode)
	{
		Serial.print("Curr=");
		Serial.print(ms);
		Serial.print("Time=");
		Serial.println(time);
	}

	uint8_t need_pw = 100;

	if (targetT <= tmp) {
		need_pw = 0;
	}

	else if (targetT - tmp < 10)
	{
		need_pw = (targetT - tmp) * 10 + 5;
	}

	//hardware->getHeater()->setPower(need_pw);

}

void Suvid::error(uint8_t er) {
	err = er;
	end_reason = SUEND_ERROR;

}

void Suvid::start(int8_t tm, uint16_t  min) {
	work_mode = SU_OFF;
	err = SUERR_OK;
	end_reason = SUEND_NO;

	//if (hardware->getHeater() == NULL) {
	//	error(SUERR_NOHEATER);
	//	return;
	//}

	if (hardware->getTKube() == NULL) {
		error(SUERR_NOTKUB);
		return;
	}

	time = min;
	targetT = tm;
	work_mode = SU_FORSAJ;
//	hardware->getHeater()->start();
}

void Suvid::stop() {
	//hardware->getHeater()->setPower(0);
	//hardware->getHeater()->stop();
	work_mode = SU_OFF;
	targetT = 0;
}

