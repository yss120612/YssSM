// 
// 
// 
#include "Brewing.h"

Brewing::Brewing(Aggregates * a, Hardware *h) : Mode(a, h) {
	makeMenu();
	MyName = "Brewing";
	have_chiller = true;
	pump_cycled = true;
	end_reason = PROCEND_NO;
}

void Brewing::initDraw() {
	Mode::initDraw();
}

void Brewing::showState() {
	uint8_t X;
	uint8_t Y;
	if (ss_active) {
		X = rand() % 25;
		//Y = 13 + rand() % (hardware->getDisplay()->height() - 44);
		Y = 15;
		hardware->getDisplay()->drawString(rand() % (80), 0, "Brewing...");
	}
	else {
		hardware->getDisplay()->drawString(0, 0, "Brewing");
		X = 0;
		Y = 15;
	}

	uint8_t t = String(hardware->getTKube()->getTemp() > 0 && hardware->getTKube()->getTemp() < 110) ? hardware->getTKube()->getTemp() : 0;
	//readTime();
	switch (work_mode)
	{
	case PROC_OFF:
		switch (end_reason) {
		case PROCEND_NO: //работаем
			hardware->getDisplay()->drawString(X, Y, "Ready 2 start");
			break;
		case PROCEND_TIME: //закончили по времени
			hardware->getDisplay()->drawString(X, Y, "End by time");
			break;
		case PROCEND_ERROR: //закончили с ошибкой
			hardware->getDisplay()->drawString(X, Y, "End by error");
			break;
		case PROCEND_FAULT: //закончили аварийно
			hardware->getDisplay()->drawString(X, Y, "End by fault");
			break;
		case PROCEND_TEMPERATURE: //закончили по температуре
			hardware->getDisplay()->drawString(X, Y, "End by temp");
			break;
		case PROCEND_MANUAL: //закон
			hardware->getDisplay()->drawString(X, Y, "End manual");
			break;
		}
		hardware->getDisplay()->drawString(X, Y + 16, "T=" + String(t));
		break;
	case PROC_FORSAJ:
		hardware->getDisplay()->drawString(X, Y, "Fsj(" + String(phase) + ") T:" + String(t));
		hardware->getDisplay()->drawString(X, Y + 16, " PWR:" + String(agg->getHeater()->getPower()));
		break;
	case PROC_FORSAJDOWN:
		hardware->getDisplay()->drawString(X, Y, "FsjDown(" + String(phase) + ") T:" + String(t));
		hardware->getDisplay()->drawString(X, Y + 16, " Kran:" + String(agg->getKran()->getState(),1));
		break;
	case PROC_WORK:
		hardware->timeLeft2(tleft);
		hardware->getDisplay()->drawString(X, Y, "Work("+String(phase)+") T:" + String(t));
		hardware->getDisplay()->drawString(X, Y + 16, " PWR:" + String(agg->getHeater()->getPower()));
		hardware->getDisplay()->drawString(X, Y + 32, " Left:" + String(tleft));
		break;
	case PROC_COOLING:
		hardware->getDisplay()->drawString(X, Y, "Cooling T:" + String(t));
		hardware->getDisplay()->drawString(X, Y + 16, " Kran:" + String(agg->getKran()->getState(), 1));
		break;
	default:
		break;
	}

}

String Brewing::getData(uint w)
{
	if (w > DS_BREWINGSTART && w < DS_BREWINGEND) {
		switch (w) {
		case DS_BREWINGSTATE:
			switch (work_mode) {
			case PROC_OFF:
				return "OFF";
				break;
			case PROC_FORSAJ:
				return "FORSAJ[preparing phase " + String(phase) + "]";
				break;
			case PROC_FORSAJDOWN:
				return "FORSAJDOWN[preparing phase " + String(phase) + "]";
				break;
			case PROC_WORK:
				return "WORKING[phase " + String(phase) + "]";
				break;
			case PROC_COOLING:
				return "COOLING";
				break;
			}
			break;
		case DS_BREWINGTIMELEFT:
			if (work_mode == PROC_WORK) {
				hardware->timeLeft2(tleft);
				return String(tleft);
			}
			else {
				return "-";
			}
			break;
		case DS_BREWINGTMP1:
			return String(CONF.getBrewingTemp1());
			break;
		case DS_BREWINGTIME1:
			return String(CONF.getBrewingMin1());
			break;
		case DS_BREWINGTMP2:
			return String(CONF.getBrewingTemp2());
			break;
		case DS_BREWINGTIME2:
			return String(CONF.getBrewingMin2());
			break;
		case DS_BREWINGTMP3:
			return String(CONF.getBrewingTemp3());
			break;
		case DS_BREWINGTIME3:
			return String(CONF.getBrewingMin3());
			break;
		case DS_BREWINGTMP4:
			return String(CONF.getBrewingTemp4());
			break;
		case DS_BREWINGTIME4:
			return String(CONF.getBrewingMin4());
			break;
		case DS_BREWINGPHASE:
			return String(phase);
			break;
		case DS_BREWINGCHILLER:
			return have_chiller ? "1" : "0";
			break;
		case DS_BREWINGTARGET:
			return String(getTarget());
			break;
		
		default:
			return "";
			break;
		}

	}
	else {
		return Mode::getData(w);
	}
	return "";
}

void Brewing::setData(uint w, String ds) {
	if (w > SET_BREWINGSTART && w < SET_BREWINGEND) {
		switch (w) {

		case SET_BREWINGTMP1:
			CONF.setBrewingTemp1((uint8_t)ds.toInt());
			break;
		case SET_BREWINGTIME1:
			CONF.setBrewingMin1(ds.toInt());
			break;
		case SET_BREWINGTMP2:
			CONF.setBrewingTemp2((uint8_t)ds.toInt());
			break;
		case SET_BREWINGTIME2:
			CONF.setBrewingMin2(ds.toInt());
			break;
		case SET_BREWINGTMP3:
			CONF.setBrewingTemp3((uint8_t)ds.toInt());
			break;
		case SET_BREWINGTIME3:
			CONF.setBrewingMin3(ds.toInt());
			break;
		case SET_BREWINGTMP4:
			CONF.setBrewingTemp4((uint8_t)ds.toInt());
			break;
		case SET_BREWINGTIME4:
			CONF.setBrewingMin4(ds.toInt());
			break;
		case SET_BREWINGCHILLER:
			have_chiller = (ds.toInt() != 0);
			break;
			
		}
	}
	else {
		Mode::setData(w,ds);
	}
}

void Brewing::makeMenu(){
	menu = new Menu();
	menu->setActive(true);
	mcmd = new MenuCommand("Start", 1);
	menu->add(mcmd);
	menu->add(new MenuCommand("Hide menu", 2));
	menu->add(new MenuCommand("Return", 3));
	Menu * setup = new Menu();
	setup->setParent(menu);
	setup->setActive(true);
	MenuIParameter * iHo1 = new MenuIParameter("Duration1;Hours", setup, 10);
	MenuIParameter * iMi1 = new MenuIParameter("Minutes", setup, 11);
	iHo1->setNext(iMi1);
	setup->add(iHo1);
	MenuIParameter * iTm1 = new MenuIParameter("Temp-ra1;Temp-ra", setup, 12);
	setup->add(iTm1);

	MenuIParameter * iHo2 = new MenuIParameter("Duration2;Hours", setup, 13);
	MenuIParameter * iMi2 = new MenuIParameter("Minutes", setup, 14);
	iHo2->setNext(iMi2);
	setup->add(iHo2);
	MenuIParameter * iTm2 = new MenuIParameter("Temp-ra2;Temp-ra", setup, 15);
	setup->add(iTm2);

	MenuIParameter * iHo3 = new MenuIParameter("Duration3;Hours", setup, 16);
	MenuIParameter * iMi3 = new MenuIParameter("Minutes", setup, 17);
	iHo3->setNext(iMi3);
	setup->add(iHo3);
	MenuIParameter * iTm3 = new MenuIParameter("Temp-ra3;Temp-ra", setup, 18);
	setup->add(iTm3);

	MenuIParameter * iHo4 = new MenuIParameter("Duration4;Hours", setup, 19);
	MenuIParameter * iMi4 = new MenuIParameter("Minutes", setup, 20);
	iHo4->setNext(iMi4);
	setup->add(iHo4);
	MenuIParameter * iTm4 = new MenuIParameter("Temp-ra4;Temp-ra", setup, 21);
	setup->add(iTm4);
	MenuFParameter * krncool = new MenuFParameter("CoolKran", setup, 22);
	setup->add(krncool);
	MenuIParameter *  tcool = new MenuIParameter("Cool T", setup, 23);
	setup->add(tcool);
	MenuBParameter * hColl = new MenuBParameter("Chiller", setup, 24);
	setup->add(hColl);

	MenuBParameter * hPump = new MenuBParameter("Pump cycl", setup, 25);
	setup->add(hPump);

	menu->add(new MenuSubmenu("Setup", setup));
}

void Brewing::command(MenuCommand * id){
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

void Brewing::initParams(MenuParameter * mp)
{
	if (mp == NULL) return;
	switch (mp->getId()) {
		//ot 0:0 do 23:50
	case 10:
		((MenuIParameter *)mp)->setup(CONF.getBrewingMin1() / 60, 1, 0, 23);
		break;
	case 11:
		((MenuIParameter *)mp)->setup(CONF.getBrewingMin1() % 60, 10, 0, 50);
		break;
	case 12:
		((MenuIParameter *)mp)->setup(CONF.getBrewingTemp1(), 1, 20, 100);
		break;
	case 13:
		((MenuIParameter *)mp)->setup(CONF.getBrewingMin2() / 60, 1, 0, 23);
		break;
	case 14:
		((MenuIParameter *)mp)->setup(CONF.getBrewingMin2() % 60, 10, 0, 50);
		break;
	case 15:
		((MenuIParameter *)mp)->setup(CONF.getBrewingTemp2(), 1, 20, 100);
		break;
	case 16:
		((MenuIParameter *)mp)->setup(CONF.getBrewingMin3() / 60, 1, 0, 23);
		break;
	case 17:
		((MenuIParameter *)mp)->setup(CONF.getBrewingMin3() % 60, 10, 0, 50);
		break;
	case 18:
		((MenuIParameter *)mp)->setup(CONF.getBrewingTemp3(), 1, 20, 100);
		break;
	case 19:
		((MenuIParameter *)mp)->setup(CONF.getBrewingMin4() / 60, 1, 0, 23);
		break;
	case 20:
		((MenuIParameter *)mp)->setup(CONF.getBrewingMin4() % 60, 10, 0, 50);
		break;
	case 21:
		((MenuIParameter *)mp)->setup(CONF.getBrewingTemp4(), 1, 20, 100);
		break;
	case 22:
		((MenuFParameter *)mp)->setup(CONF.getBrewingKran(), 0.2, 15, 80);
		break;
	case 23:
		((MenuIParameter *)mp)->setup(CONF.getBrewingCoolingTemp(), 1, 10, 90);
		break;
	case 24:
		((MenuBParameter *)mp)->setup(have_chiller);
		break;
	case 25:
		((MenuBParameter *)mp)->setup(pump_cycled);
		break;
	}
}

void Brewing::acceptParams(MenuParameter * mp)
{
	if (mp == NULL) return;
	switch (mp->getId()) {
	case 10:
		break;
	case 11:
		CONF.setBrewingMin1(((MenuIParameter *)mp->getPrev())->getCurrent() * 60 + ((MenuIParameter *)mp)->getCurrent());
		break;
	case 12:
		CONF.setBrewingTemp1(((MenuIParameter *)mp)->getCurrent());
		break;
	case 13:
		break;
	case 14:
		CONF.setBrewingMin2(((MenuIParameter *)mp->getPrev())->getCurrent() * 60 + ((MenuIParameter *)mp)->getCurrent());
		break;
	case 15:
		CONF.setBrewingTemp2(((MenuIParameter *)mp)->getCurrent());
		break;
	case 16:
		break;
	case 17:
		CONF.setBrewingMin3(((MenuIParameter *)mp->getPrev())->getCurrent() * 60 + ((MenuIParameter *)mp)->getCurrent());
		break;
	case 18:
		CONF.setBrewingTemp3(((MenuIParameter *)mp)->getCurrent());
		break;
	case 19:
		break;
	case 20:
		CONF.setBrewingMin4(((MenuIParameter *)mp->getPrev())->getCurrent() * 60 + ((MenuIParameter *)mp)->getCurrent());
		break;
	case 21:
		CONF.setBrewingTemp4(((MenuIParameter *)mp)->getCurrent());
		break;
	case 22:
		CONF.setBrewingKran(((MenuFParameter *)mp)->getCurrent());
		break;
	case 23:
		CONF.setBrewingCoolingTemp(((MenuIParameter *)mp)->getCurrent());
		break;
	case 24:
		have_chiller=((MenuBParameter *)mp)->getCurrent();
		break;
	case 25:
		pump_cycled = ((MenuBParameter *)mp)->getCurrent();
		if (work_mode != PROC_OFF) {
			hardware->reSetAlarm1();
			hardware->getPump()->start();
			if (pump_cycled) {
				hardware->setAlarm1(2);
			}
		}
		break;
	}
}

uint8_t  Brewing::getTarget() {
	switch (phase) {
	case 1: return CONF.getBrewingTemp1();
	case 2: return CONF.getBrewingTemp2();
	case 3: return CONF.getBrewingTemp3();
	case 4: return CONF.getBrewingTemp4();
	default: return 0;
	}
}

int Brewing::getTimeTarget()
{
	switch (phase) {
	case 1: return CONF.getBrewingMin1();
	case 2: return CONF.getBrewingMin2();
	case 3: return CONF.getBrewingMin3();
	case 4: return CONF.getBrewingMin4();
	default: return 0;
	}
}

void Brewing::prepareWork() {
	if (have_chiller && hardware->getTKube()->getTemp() > getTarget()) {
		work_mode = PROC_FORSAJDOWN;
		agg->getKran()->openQuantum(CONF.getBrewingKran());
		agg->getHeater()->setPower(0);
	}
	else {
		work_mode = PROC_FORSAJ;
	}
	logg.logging("Prepare to phase " + String(phase) + " started at " + getTimeStr());
}

void Brewing::start() {
	work_mode = PROC_OFF;
	end_reason = PROCEND_NO;
	
	if (agg->getHeater() == NULL) {
		stop(PROCEND_ERROR, "Heater not found!");
		return;
	}

	if (hardware->getTKube() == NULL || hardware->getTKube()->getTemp() <= 0 || hardware->getTKube()->getTemp() > 120) {
		stop(PROCEND_ERROR, "Cube termometr not found!");
		return;
	}
	
	phase = 1;
	hardware->reSetAlarm2();
	hardware->reSetAlarm1();
	if (pump_cycled) {
		hardware->setAlarm1(2);
	}
	agg->getHeater()->start();
	prepareWork();
	hardware->getPump()->start();
	hardware->getFloodWS()->arm(25);
	logg.logging("Brewing process started at " + getTimeStr());
	mcmd->setName("Stop");
}

void Brewing::stop(uint8_t reason,String text) {
	agg->getHeater()->setPower(0);
	agg->getHeater()->stop();
	agg->getKran()->forceClose();
	hardware->getPump()->stop();
	hardware->getFloodWS()->disarm();
	work_mode = PROC_OFF;
	end_reason = reason;
	hardware->reSetAlarm2();
	hardware->reSetAlarm1();
	String st = "Brewing finished at " + getTimeStr() + " by reason ";
	phase = 0;
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
		st += "error detected:" + text;
		break;
	case PROCEND_FAULT:
		st += "fault";
		break;
	case PROCEND_FLOOD:
		st += "flood sensor alarmed";
		break;
	}
	logg.logging(st);
	mcmd->setName("Start");
}

void Brewing::process(long ms) {
	if (work_mode == PROC_OFF) return;
	if (last_time + test_time - ms > 0) return;
	last_time = ms;
	float tmp = hardware->getTKube()->getTemp();
	switch (work_mode) {

	case PROC_FORSAJ:
		if (tmp >= getTarget()) {
			work_mode = PROC_WORK;
			logg.logging("Brewing WORK phase №" + String(phase) + " started at " + getTimeStr());
			hardware->setAlarm2(getTimeTarget());//Завели будильник
			hardware->getBeeper()->beep(2000, 1000);
		}
		break;
	case PROC_FORSAJDOWN:
		if (tmp <= getTarget()) {
			work_mode = PROC_WORK;
			agg->getKran()->close();
			logg.logging("Brewing WORK phase №" + String(phase) + " started at " + getTimeStr());
			hardware->setAlarm2(getTimeTarget());//Завели будильник
			hardware->getBeeper()->beep(2000, 1000);
		}
		break;
	case PROC_WORK:
		if (hardware->getClock()->checkAlarm2()) {//будильник сработал
			logg.logging("Brewing WORK phase №" + String(phase) + " finished at " + getTimeStr());
			phase++;
			if (getTimeTarget() == 0 || getTarget() == 0) {
				if (have_chiller) {
					phase = 5;
					agg->getHeater()->setPower(0);
					agg->getHeater()->stop();
					agg->getKran()->openQuantum(CONF.getBrewingKran());
					work_mode = PROC_COOLING;
					hardware->getBeeper()->beep(2000, 1000);
					logg.logging("Brewing cooling started at " + getTimeStr());
				}
				else {
					stop(PROCEND_TIME);
					return;
				}
			}
			else {
				prepareWork();
			}
		}
		break;
	case PROC_COOLING:
		if (tmp <= CONF.getBrewingCoolingTemp()) {
			stop(PROCEND_TIME);
		}
		break;
	}

	if (work_mode == PROC_FORSAJ || work_mode == PROC_WORK) {
		agg->getHeater()->setPID(tmp, getTarget());
	}

	if (hardware->getClock()->checkAlarm1()) {
		if (hardware->getPump()->isWorking()) {
			hardware->getPump()->stop();
			hardware->setAlarm1(1);
		}
		else {
			hardware->getPump()->start();
			if (pump_cycled) hardware->setAlarm1(2);
		}
	}

	if (hardware->getFloodWS()->isAlarmed()) {
		stop(PROCEND_FLOOD);
	}
}

