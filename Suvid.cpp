#include "Suvid.h"

Suvid::Suvid(Aggregates * a, Hardware *h) : Mode(a,h) {
	
	makeMenu();
}

void Suvid::initDraw() {
	tpause.setup(CONF.getSuvidMin(), CONF.getSuvidTemp());
	last_action = millis();
	ss_active = false;
}

void Suvid::draw(long m) {
	hardware->getDisplay()->clear();
	hardware->getDisplay()->setTextAlignment(TEXT_ALIGN_LEFT);
	if (ss_active || m - last_action > CONF.getScrSavMin() * 60000) {
		ss_active = true;
		showState();
	}
	else {
				
		if (menu != NULL && menu->isActive()) {
			hardware->getDisplay()->drawString(0, 0, "Suvid");
			if (menu->isEditMode()) {
				hardware->getDisplay()->drawString(0, hardware->getDisplay()->getHeight() / 2, menu->getEditParams()->getMyName() + " : " + menu->getEditParams()->getStCurr());
			}
			else {
				menu->display(hardware->getDisplay());
			}
		}
		else
		{
		showState();
		}
	}
	hardware->getDisplay()->display();
}

void Suvid::showState() {
	uint8_t X;
	uint8_t Y;
	if (ss_active) {
		X = rand() % 25;
		Y = 13 + rand() % (hardware->getDisplay()->height() - 44);
		hardware->getDisplay()->drawString(rand() % (80), 0, "Suvid...");
	}
	else {
		hardware->getDisplay()->drawString(0, 0, "Suvid");
		X = 0;
		Y = 15;
	}
	
	//X = 25;
	//Y = 13 + (hardware->getDisplay()->height() - 44);

	uint8_t t = String(hardware->getTKube()->getTemp() > 0 && hardware->getTKube()->getTemp() < 110) ? hardware->getTKube()->getTemp() : 0;

	switch (work_mode)
	{
	case PROC_OFF:
		switch (end_reason) {
		case PROCEND_NO: //работаем
		hardware->getDisplay()->drawString(X, Y, "Ready 2 start");
		break;
		case	PROCEND_TIME: //закончили по времени
		hardware->getDisplay()->drawString(X, Y, "End by time");
		break;
		case	PROCEND_ERROR: //закончили с ошибкой
		hardware->getDisplay()->drawString(X, Y, "End by error");
		break;
		case  PROCEND_FAULT: //закончили аварийно
		hardware->getDisplay()->drawString(X, Y, "End by fault");
		break;
		case PROCEND_TEMPERATURE: //закончили по температуре
		hardware->getDisplay()->drawString(X, Y, "End by temp");
		break;
		case  PROCEND_MANUAL: //закон
		hardware->getDisplay()->drawString(X, Y, "End manual");
		break;
		}
		//hardware->getDisplay()->drawString(X, Y, "Ready");
		hardware->getDisplay()->drawString(X, Y+16, "T="+String(t));
		break;
	case PROC_FORSAJ:
		hardware->getDisplay()->drawString(X, Y, "Forsaj T:" + String(t));
		//hardware->getDisplay()->drawString(X, Y + 12, "T=" + String(t));
		hardware->getDisplay()->drawString(X, Y + 16," NOW:" + String(tim));
		break;
	case PROC_WORK:
		
		timeLeft();
		hardware->getDisplay()->drawString(X, Y, "Working T:" + String(t));
		hardware->getDisplay()->drawString(X, Y + 16, " Left:"+ String(tleft));
		break;
	default:
		break;
	}

}

void Suvid::left() {
	Mode::left();
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
#ifdef ENCODER_LOG
	logg.logging("suvid left");
#endif
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
#ifdef ENCODER_LOG
	logg.logging("suvid right");
#endif

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
#ifdef ENCODER_LOG
	logg.logging("suvid press");
#endif
	
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
#ifdef ENCODER_LOG
	logg.logging("suvid long_press");
#endif
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
	MenuIParameter * iTm = new MenuIParameter("Temp-ra;Temp-ra", setup, 12);
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
	if (mp == NULL) return;
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
	if (mp == NULL) return;
	switch (mp->getId()) {
	case 10:
		break;
	case 11:
		logg.logging("Hours="+String(((MenuIParameter *)mp->getPrev())->getCurrent()));
		logg.logging("Minutes=" + String(((MenuIParameter *)mp)->getCurrent()));
		tpause.setTime(((MenuIParameter *)mp->getPrev())->getCurrent()*60+((MenuIParameter *)mp)->getCurrent());
		break;
	case 12:
		logg.logging("Temp-ra=" + String(((MenuIParameter *)mp)->getCurrent()));
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
	hardware->getClock()->writeAlarm2(DS3231_ALM_DTHM);
	//hardware->getClock() ->
	
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
		armAlarm();//Завели будильник
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

