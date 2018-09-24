#include "Suvid.h"

Suvid::Suvid(Aggregates * a, Hardware *h) : Mode(a,h) {
	
	makeMenu();
	MyName = "SuVid";
	
}

void Suvid::initDraw() {
	Mode::initDraw();
	tpause.setup(CONF.getSuvidMin(), CONF.getSuvidTemp());
}

void Suvid::showState() {
	uint8_t X;
	uint8_t Y;
	if (ss_active) {
		X = rand() % 25;
		//Y = 13 + rand() % (hardware->getDisplay()->height() - 44);
		Y = 15;
		hardware->getDisplay()->drawString(rand() % (80), 0, "Suvid...");
	}
	else {
		hardware->getDisplay()->drawString(0, 0, "Suvid");
		X = 0;
		Y = 15;
	}
	
	uint8_t t = String(hardware->getTKube()->getTemp() > 0 && hardware->getTKube()->getTemp() < 110) ? hardware->getTKube()->getTemp() : 0;
	readTime();
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
		hardware->getDisplay()->drawString(X, Y+16, "T="+String(t));
		break;
	case PROC_FORSAJ:
		hardware->getDisplay()->drawString(X, Y, "Forsaj T:" + String(t));
		hardware->getDisplay()->drawString(X, Y + 16," PWR:" + String(agg->getHeater()->getPower()));
		break;
	case PROC_WORK:
		hardware->timeLeft2(tleft);
		hardware->getDisplay()->drawString(X, Y, "Working T:" + String(t));
		hardware->getDisplay()->drawString(X, Y + 16, " PWR:" + String(agg->getHeater()->getPower()));
		hardware->getDisplay()->drawString(X, Y + 32, " Left:"+ String(tleft));
		break;
	default:
		break;
	}

}

String Suvid::getData(uint w)
{
	if (w > DS_SUVIDSTART && w < DS_SUVIDEND) {
		switch (w) {
		case DS_SUVIDSTATE:
			switch (work_mode) {
			case PROC_OFF:
				return "OFF";
				break;
			case PROC_FORSAJ:
				return "FORSAJ";
				break;
			case PROC_WORK:
				return "WORKING";
				break;
			}
			break;
		case DS_SUVIDTIMELEFT:
			if (work_mode == PROC_WORK) {
				hardware->timeLeft2(tleft);
				return String(tleft);
			}
			else {
				return "-";
			}
			break;
		case DS_SUVIDTARGET:
			return String(tpause.getTemp());
		break;
		default:
			return "";
			break;
		}

	}
	else
		return Mode::getData(w);
}

void Suvid::makeMenu()
{
	menu = new Menu();
	menu->setActive(true);
	mcmd = new MenuCommand("Start", 1);
	menu->add(mcmd);
	menu->add(new MenuCommand("Hide menu", 2));
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

void Suvid::command(MenuCommand * id)
{
	switch (id->getId()) {
	case 1:
		if (work_mode == PROC_OFF) {
			menu->setActive(false);
			start();

		}
		else {
			stop(PROCEND_MANUAL);
		}
		break;
	case 2:
		menu->setActive(false);
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
		//ot 0:0 do 23:50
	case 10:
		((MenuIParameter *)mp)->setup(tpause.getTime()/60, 1, 0, 23);
		break;
	case 11:
		((MenuIParameter *)mp)->setup(tpause.getTime() % 60, 10, 0, 50);
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
		//logg.logging("Hours="+String(((MenuIParameter *)mp->getPrev())->getCurrent()));
		//logg.logging("Minutes=" + String(((MenuIParameter *)mp)->getCurrent()));
		CONF.setSuvidMin(((MenuIParameter *)mp->getPrev())->getCurrent() * 60 + ((MenuIParameter *)mp)->getCurrent());
		tpause.setTime(CONF.getSuvidMin());
		//CONF.read();
		break;
	case 12:
		//logg.logging("Temp-ra=" + String(((MenuIParameter *)mp)->getCurrent()));
		CONF.setSuvidTemp(((MenuIParameter *)mp)->getCurrent());
		tpause.setTemp(CONF.getSuvidTemp());
		break;
	}
}

void Suvid::process(long ms) {
	if (work_mode == PROC_OFF) return;
	if (last_time + test_time - ms >0) return;
	last_time = ms;
	float tmp = hardware->getTKube()->getTemp();
	switch (work_mode) {
	
	case PROC_FORSAJ:
		
		if (tmp >= tpause.getTemp()) {
			work_mode = PROC_WORK;
			logg.logging("SuVid WORK started at " + getTimeStr());
			hardware->setAlarm2(tpause.getTime());//Завели будильник

		}
		break;
	case PROC_WORK:
		if (hardware->getClock()->checkAlarm2()) {
			stop(PROCEND_TIME);//будильник сработал
		}
		break;
	}

	agg->getHeater()->setPID(tmp, tpause.getTemp());
}

void Suvid::error(uint8_t er) {
	err = er;
	end_reason = PROCEND_ERROR;

}

void Suvid::start() {
	work_mode = PROC_OFF;
	err = PROCERR_OK;
	end_reason = PROCEND_NO;
	//hardware->getUrovenWS()->arm();
	//hardware->getFloodWS()->arm();
	//hardware->getUrovenWS()->setLimit(0);
	if (agg->getHeater() == NULL) {
		error(PROCERR_NOHEATER);
		return;
	}

	if (hardware->getTKube() == NULL) {
		error(PROCERR_NOTKUB);
		return;
	}
	work_mode = PROC_FORSAJ;
	agg->getHeater()->start();
	agg->getHeater()->setPower(50);
	hardware->getPump()->start();
	logg.logging("SuVid started at "+ getTimeStr());
	mcmd->setName("Stop");
}

void Suvid::stop(uint8_t reason) {
	agg->getHeater()->setPower(0);
	agg->getHeater()->stop();
	hardware->getPump()->stop();
	work_mode = PROC_OFF;
	end_reason = reason;
	String st = "SuVid finished started at " + getTimeStr() + " by reason ";
	hardware->getBeeper()->beep(2000, 3000);
	switch (reason)
	{
	case PROCEND_TIME:
		st += "time end";
		break;
	case PROCEND_TEMPERATURE:
		st += "temperature limit";
		break;
	case PROCEND_MANUAL:
		st += "manual";
		break;
	case PROCEND_ERROR:
		st += "error detected";
		break;
	case PROCEND_FAULT:
		st += "fault";
		break;
	}
	logg.logging(st);
	mcmd->setName("Start");
}

