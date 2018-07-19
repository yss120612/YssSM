#include "Suvid.h"

Suvid::Suvid(Aggregates * a, Hardware *h) : Mode(a,h) {
	tpause.setup(CONF.getSuvidMin(),CONF.getSuvidTemp());
	makeMenu();
}

void Suvid::initDraw() {
}

void Suvid::draw(long m) {
	hardware->getDisplay()->clear();
	if (ss_active || m - last_action > CONF.getScrSavMin() * 60000) {
		ss_active = true;
	}
	else {
		if (menu != NULL && menu->isActive()) {
			if (menu->isEditMode()) {
				hardware->getDisplay()->drawString(0, hardware->getDisplay()->getHeight() / 2, menu->getEditParams()->getMyName() + " : " + menu->getEditParams()->getStCurr());
			}
			else {
				menu->display(hardware->getDisplay());
			}
		}
		else
		{
			
		}
	}
	hardware->getDisplay()->display();
}

void Suvid::left() {
	Mode::left();
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
	logg.logging("suvid left");
	if (menu->isActive())
	{
		processMenuChange(false);
	}
	else {//MENU IS NOT ACTIVE

		  //hardware->getHeater()->setPower(hardware->getHeater()->getPower() + 1);
	}
	drawImmed = true;
}

void Suvid::right() {
	Mode::right();
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
	logg.logging("suvid right");

	if (menu->isActive())
	{
		processMenuChange(true);
	}
	else {//MENU IS NOT ACTIVE

		  //hardware->getHeater()->setPower(hardware->getHeater()->getPower() + 1);
	}
	drawImmed = true;

}

void Suvid::press() {
	Mode::press();
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
	logg.logging("suvid press");
	
	if (menu->isActive())
	{
		processMenuPress();
	}
	else {//MENU IS NOT ACTIVE

		
	}
	drawImmed = true;
}

void Suvid::long_press() {
	Mode::long_press();
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}

	logg.logging("long_press");
	if (menu->isActive()) {
		processMenuLong();
	}
	else {
		menu->setActive(true);
	}
}

void Suvid::makeMenu()
{
	menu = new Menu();
	menu->setActive(true);
	menu->add(new MenuCommand("Start", 1));
	menu->add(new MenuCommand("Stop", 2));
	menu->add(new MenuCommand("Return", 3));
	Menu * setup = new Menu();
	setup->setParent(menu);
	setup->setActive(true);
	MenuIParameter * iHo = new MenuIParameter("Duration;Hours", setup, 10);
	MenuIParameter * iMi = new MenuIParameter("Minutes", setup, 11);
	iHo->setNext(iMi);
	setup->add(iHo);
	MenuIParameter * iTm = new MenuIParameter("Temp-ra;Temperature", setup, 12);
	setup->add(iTm);
	menu->add(new MenuSubmenu("Setup", setup));
}

void Suvid::command(uint8_t id)
{
	switch (id) {
	case 1:
		if (work_mode != PROC_OFF) return;
		menu->setActive(false);
		start();
		break;
	case 2:
		if (work_mode == PROC_OFF) return;
		stop(PROCEND_MANUAL);
		break;
	case 3:
		stop(PROCEND_MANUAL);
		workMode.setCurrent(MODE_MAIN);
		break;
	}
}

void Suvid::initParams(MenuParameter * mp)
{
	switch (mp->getId()) {
	case 10:
		((MenuIParameter *)mp)->setup(tpause.getTime()/60, 1, 0, 11);
		break;
	case 11:
		((MenuIParameter *)mp)->setup(tpause.getTime() % 60, 1, 0, 59);
		break;
	case 12:
		((MenuIParameter *)mp)->setup(tpause.getTemp(), 1, 20, 100);
		break;
	}
}

void Suvid::acceptParams(MenuParameter * mp)
{
	switch (mp->getId()) {
	case 10:
		break;
	case 11:
		tpause.setTime(((MenuIParameter *)mp->getPrev())->getCurrent()*60+((MenuIParameter *)mp)->getCurrent());
		break;
	case 12:
		tpause.setTemp(((MenuIParameter *)mp)->getCurrent());
		break;
	}
}

void Suvid::armAlarm()
{
	hardware->getClock()->now();
	uint minutes = tpause.getTime() % 60;
	uint hours = tpause.getTime() / 60;
	hardware->getClock()->m += minutes;
	if (hardware->getClock()->m >= 60) {
		hardware->getClock()->m -= 60;
		hours += 1;
	}
	hardware->getClock()->h += hours;
	if (hardware->getClock()->h >= 24)
	{
		hardware->getClock()->h -= 24;
		hardware->getClock()->dd += 1;
	}

	switch (hardware->getClock()->mm) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
		if (hardware->getClock()->dd > 31)
		{
			hardware->getClock()->dd = 1;
			hardware->getClock()->mm += 1;
		}
		break;
	case 12:
		if (hardware->getClock()->dd > 31) hardware->getClock()->dd = 1;
		{
			hardware->getClock()->mm = 1;
			hardware->getClock()->yyyy += 1;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (hardware->getClock()->dd > 30) hardware->getClock()->dd = 1;
		break;
	case 2:
		if (hardware->getClock()->yyyy % 4 == 0) {
			if (hardware->getClock()->dd > 29)
			{
				hardware->getClock()->dd = 1;
				hardware->getClock()->mm += 1;
			}
		}
		else {
			if (hardware->getClock()->dd > 28)
			{
				hardware->getClock()->dd = 1;
				hardware->getClock()->mm += 1;
			}
		}
		break;
	
	}
	hardware->getClock()->writeAlarm2(DS3231_ALM_DDHM);
}

void Suvid::timeLeft() {
	hardware->getClock()->readAlarm2();
	int8_t dd = hardware->getClock()->dd;
	int8_t h = hardware->getClock()->h;
	int8_t m = hardware->getClock()->m;
	int8_t s = 0;
	hardware->getClock()->now();
	s -= hardware->getClock()->s;
	if (s < 0)
	{
		m -= 1;
		s += 60;
	}

	m -= hardware->getClock()->m;
	if (m < 0)
	{
		h -= 1;
		m += 60;
	}
	h -= hardware->getClock()->h;
	if (h < 0) h += 24;
	sprintf(tleft, "%02d:%02d:%02d", h, m, s);
}

void Suvid::process(long ms) {
	if (work_mode == PROC_OFF) return;
	if (last_time + test_time - ms >0) return;
	last_time = ms;

	if (work_mode == PROC_WORK && hardware->getClock()->checkAlarm2()) {
		stop(PROCEND_TIME);
		hardware->getBeeper()->beep(1000, 5000);
		return;
	}


	float tmp = hardware->getTKube()->getTemp();

	if (tmp >= tpause.getTemp() && work_mode == PROC_FORSAJ) {//вышли на рабочий режим
		work_mode = PROC_WORK;
		hardware->getBeeper()->beep(1000, 500);
		armAlarm();//«авели будильник
	}

	uint8_t need_pw = 100;

	if (tpause.getTemp() <= tmp) {
		need_pw = 0;
	}

	else if (tpause.getTemp() - tmp < 10)
	{
		need_pw = (tpause.getTemp() - tmp) * 10 + 5;
	}
	agg->getHeater()->setPower(need_pw);
}

void Suvid::error(uint8_t er) {
	err = er;
	end_reason = PROCEND_ERROR;

}

void Suvid::start() {
	work_mode = PROC_OFF;
	err = PROCERR_OK;
	end_reason = PROCEND_NO;

	if (agg->getHeater() == NULL) {
		error(PROCERR_NOHEATER);
		return;
	}

	if (hardware->getTKube() == NULL) {
		error(PROCERR_NOTKUB);
		return;
	}
	work_mode = PROC_FORSAJ;
}

void Suvid::stop(uint8_t reason) {
	agg->getHeater()->setPower(0);
	agg->getHeater()->stop();
	work_mode = PROC_OFF;
	end_reason = reason;
}

