// 
// 
// 

#include "Suvid.h"

Suvid::Suvid(Aggregates * a, Hardware *h) : Mode(a,h) {
	targetT = 0;
	last_time = 0;
	makeMenu();
}

void Suvid::initDraw() {
}

void Suvid::draw() {

}



void Suvid::left() {

logg.logging("suvid left");

}
void Suvid::right() {

	logg.logging("suvid right");


}
void Suvid::press() {

	logg.logging("suvid press");

}
void Suvid::long_press() {
	logg.logging("long_press");
}

void Suvid::makeMenu()
{
	menu = new Menu();
	menu->setActive(true);
	menu->add(new MenuCommand("Start", 1));
	menu->add(new MenuCommand("Return", 2));
	Menu * setup = new Menu();
	setup->setParent(menu);
	setup->setActive(true);

	MenuIParameter * iHo = new MenuIParameter("Duration;Hours", setup, 10);
	MenuIParameter * iMi = new MenuIParameter("Minutes", setup, 11);
	
	iHo->setNext(iMi);
	setup->add(iHo);
	
	menu->add(new MenuSubmenu("Setup", setup));
}

void Suvid::command(uint8_t id)
{
}

void Suvid::initParams(MenuParameter * mp)
{
}

void Suvid::acceptParams(MenuParameter * mp)
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
		//Serial.print("Curr=");
		//Serial.print(ms);
		//Serial.print("Time=");
		//Serial.println(time);
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

