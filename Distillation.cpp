#include "Distillation.h"

Distillation::Distillation(Aggregates * a, Hardware *h) : Mode(a,h)
{
	MyName = "Distillation";
	makeMenu();
}

Distillation::~Distillation()
{
	delete mcmd;
}

void Distillation::showState()
{
	uint8_t x;
	uint8_t y;
	if (ss_active) {
		x = rand()%40;
		y = 0;
	}
	else {
		x = 0;
		y = 0;
	}
	hardware->getDisplay()->drawString(x, 0, "Dist");
	hardware->getDisplay()->drawString(x+40, 0, String(agg->getHeater()->getPower()));

	hardware->getDisplay()->drawString(x, y + 13, "TSA=" + String(hardware->getTTSA()->getTemp()));
	hardware->getDisplay()->drawString(x, y + 29, "KUB=" + String(hardware->getTKube()->getTemp()));
	switch (work_mode) {
	case PROC_OFF:
		hardware->getDisplay()->drawString(x, y + 45, "OFF");
		break;
	case PROC_FORSAJ:
		hardware->getDisplay()->drawString(x, y + 45, "FORSAJ");
		break;
	case PROC_WORK:
		hardware->getDisplay()->drawString(x, y + 45, "WORKING");
		break;
	}
}

String Distillation::getData(uint w)
{
	
	if (w > DS_DISTSTART && w < DS_DISTEND) {
		switch (w) {
		case DS_DISTSTATE:
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
		case DS_DISTSTOP:
			return String(CONF.getDistStopTemp(), 1);
			break;
		default:
			return "";
		break;
		}
		
	}
	else
	return Mode::getData(w);
}

void Distillation::makeMenu()
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
	MenuIParameter * tFor = new MenuIParameter("T Forsaj", setup, 12);
	MenuFParameter * tEnd = new MenuFParameter("T End", setup, 13);
	MenuIParameter * pwWork = new MenuIParameter("WorkPower", setup, 14);
	MenuFParameter * pwKran = new MenuFParameter("OpenKran", setup, 15);
	setup->add(tFor);
	setup->add(tEnd);
	setup->add(pwWork);
	setup->add(pwKran);
	menu->add(new MenuSubmenu("Setup", setup));
}

void Distillation::command(MenuCommand * id)
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
		//if (work_mode == PROC_OFF) return;
		//stop(PROCEND_MANUAL);
		break;
	case 3:
		if (work_mode != PROC_OFF)
		{
			stop(PROCEND_MANUAL);
		}
		workMode.setCurrent(MODE_MAIN);
		break;
	}
}

void Distillation::stop(uint8_t reason) {
	work_mode = PROC_OFF;
	end_reason = reason;
	switch (end_reason)
	{
	case PROCEND_FAULT:
		logg.logging("Distill fault and finished at " + getTimeStr());
		break;
	case PROCEND_MANUAL:
		logg.logging("Distill manually stopped at " + getTimeStr());
		break;
	case PROCEND_TEMPERATURE:
		logg.logging("Distill normal finished at " + getTimeStr() + " by kube temperature");
		break;
	case PROCEND_UROVEN:
		logg.logging("Distill normal finished at " + getTimeStr() + " by uroven sensor");
		break;
	case PROCEND_FLOOD:
		logg.logging("Distill  finished at " + getTimeStr() + " by flood sensor");
		break;
	default:
		break;
	}
	agg->getHeater()->setPower(0);
	agg->getHeater()->stop();
	agg->getKran()->forceClose();
	hardware->getFloodWS()->disarm();
	hardware->getUrovenWS()->disarm();
	mcmd->setName("Start");
}

void Distillation::start() {
	work_mode = PROC_FORSAJ;
	err = PROCERR_OK;
	end_reason = PROCEND_NO;
	agg->getHeater()->setPower(98);
	agg->getHeater()->start();
	mcmd->setName("Stop");
	coldBeginCheck = 0;
	tsa_alarms = 0;
	hardware->getUrovenWS()->disarm();
	hardware->getFloodWS()->arm(50);
	logg.logging("Distill process started at " + getTimeStr());
}

void Distillation::initParams(MenuParameter * mp)
{
	if (mp == NULL) return;
	switch (mp->getId()) {
	case 12:
		((MenuIParameter *)mp)->setup(CONF.getDistForsajTemp(), 1, 20, 100);
		break;
	case 13:
		((MenuFParameter *)mp)->setup(CONF.getDistStopTemp(), 0.2, 50, 110);
		break;
	case 14:
		((MenuIParameter *)mp)->setup(CONF.getDistWorkPower(), 1, 10, 100);
		break;
	case 15:
		((MenuFParameter *)mp)->setup(CONF.getDistKranOpened(), 0.1, 10 , 85);
		break;
	}
}

void Distillation::acceptParams(MenuParameter * mp)
{
	if (mp == NULL) return;
	switch (mp->getId())
	{
	case 12:
		CONF.setDistForsajTemp(((MenuIParameter *)mp)->getCurrent());
		break;
	case 13:
		CONF.setDistStopTemp(((MenuFParameter *)mp)->getCurrent());
		break;
	case 14:
		CONF.setDistWorkPower(((MenuIParameter *)mp)->getCurrent());
		if (work_mode == PROC_WORK) {
			agg->getHeater()->setPower(CONF.getDistWorkPower());
		}
		break;
	case 15:
		CONF.setDistKranOpened(((MenuFParameter *)mp)->getCurrent());
		if (work_mode == PROC_WORK) {
			agg->getKran()->openQuantum(CONF.getDistKranOpened());
		}
		break;
	}
}

void Distillation::process(long ms) {
	if (work_mode == PROC_OFF) return;
	if (last_time + test_time - ms >0) return;
	last_time = ms;

	
	tcube = hardware->getTKube()->getTemp();
	ttsa = hardware->getTTSA()->getTemp();
	tdef= hardware->getTTsarga()->getTemp();
	switch (work_mode) {
	case PROC_FORSAJ:
		if (tdef > CONF.getDistForsajTemp()){//end of forsaj
			agg->getHeater()->setPower(CONF.getDistWorkPower());
			agg->getKran()->openQuantum(CONF.getDistKranOpened());
			hardware->getUrovenWS()->arm(50);
			logg.logging("Distill forsaj finished at "+ getTimeStr());
			hardware->getBeeper()->beep(2000, 2000);
			hardware->setAlarm1(3);
			hardware->setAlarm2(15);
			work_mode = PROC_WORK;
		}
		break;
	case PROC_WORK:
		if (tcube > CONF.getDistStopTemp()) {//end of collect product by T cube
			hardware->getBeeper()->beep(2000, 3000);
			stop(PROCEND_TEMPERATURE);
		}
		if (hardware->getUrovenWS()->isAlarmed()) {//end of collect product by level sensor
			hardware->getBeeper()->beep(2000, 3000);
			stop(PROCEND_UROVEN);
		}
				
		if (coldBeginCheck==0 && hardware->getClock()->checkAlarm2()) {
			coldBeginCheck = 2;
		}
		break;
	}

	boolean evnt = false;

	if (hardware->getClock()->checkAlarm1()) {
		if (ttsa < CONF.getTSAmin() && coldBeginCheck==2)
		{
			hardware->getBeeper()->beep(1000, 500);
			logg.logging("TSA cold (" + String(ttsa) + "C) at " + String(tim));
			agg->getHeater()->shiftPower(3);
			agg->getKran()->openQuantum(agg->getKran()->getState() - 0.2);
			evnt = true;
		}
		if (ttsa > CONF.getTSAmax()) {
			hardware->getBeeper()->beep(1000, 500);
			logg.logging("TSA alarm (" + String(ttsa) + "C) at " + getTimeStr());
			agg->getHeater()->shiftPower(-5);
			agg->getKran()->openQuantum(agg->getKran()->getState() + 0.5);
			tsa_alarms++;
			evnt = true;
			if (tsa_alarms >= 3) {
				hardware->getBeeper()->beep(1000, 5000);
				logg.logging("TSA max alarms (" + String(ttsa) + "C) at " + getTimeStr());
				stop(PROCEND_FAULT);
			}
		}	else {
			if (tsa_alarms > 0) {
				logg.logging("TSA alarm reset (" + String(ttsa) + "C) at " + getTimeStr());
				tsa_alarms = 0;
			}
		}
		hardware->setAlarm1(evnt?3:3);
	}

	//Аварийные остановки
	if (ttsa > CONF.getTSAcritical())
	{
		logg.logging("TSA critical T (" + String(ttsa) + "C) at " + getTimeStr());
		stop(PROCEND_FAULT);
	}

	if (hardware->getFloodWS()->isAlarmed()) {
		stop(PROCEND_FLOOD);
	}
}