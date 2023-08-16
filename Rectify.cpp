#include "Rectify.h"

Rectify::Rectify(Aggregates * a, Hardware *h) : Mode(a, h)
{
	MyName = "Rectify";
	makeMenu();
	checkLowTSA = false;
	getTail = false;

}

Rectify::~Rectify()
{
//	delete mcmd;
//	delete cont;
	delete menu;
}

String Rectify::getData(uint w)
{

	if (w > DS_RECTSTART && w < DS_RECTEND) {
		switch (w) {
		case DS_RECTSTATE:
			switch (work_mode) {
			case PROC_OFF:
				return "OFF";
				break;
			case PROC_FORSAJ:
				return "FORSAJ";
				break;
			case PROC_WORK:
				return "BODY COLLECTING";
				break;
			case PROC_GET_HEAD:
				return "HEAD COLLECTING";
				break;
			case PROC_SELF_WORK:
				return "SELF WORK";
				break;
			case PROC_GET_TAIL:
				return "TAILS COLLECTING";
				break;
			case PROC_WAIT_HEAD:
				return "READY TO COLLECT BODY";
				break;
			case PROC_WAIT_SELF:
				return "READY TO COLLECT HEAD";
				break;
			case PROC_WAIT_TAIL:
				return "READY TO COLLECT TAIL";
				break;
			}
			break;
		case DS_RECTSTOP:
			return String(CONF.getRectStopTemp(), 1);
			break;
		default:
			return "";
			break;
		}

	}
	else
	return Mode::getData(w);
	return "";
}

void Rectify::setData(uint w, String ds)
{
	if (w > SET_RECTSTART && w < SET_RECTEND) {
		switch (w) {
		case SET_RECTTSTOP:
			CONF.setRectStopTemp(ds.toFloat());
			break;
		}
	}
	else {
		Mode::setData(w, ds);
	}
}

void Rectify::initDraw()
{
	Mode::initDraw();
	head_collected = false;
	stop_defined = false;
}

void Rectify::showState()
{
	uint8_t x;
	uint8_t y;
	if (ss_active) {
		x = rand() % 40;
		y = 0;
	}
	else {
		x = 0;
		y = 0;
	}
	hardware->getDisplay()->drawString(x, 0, "Rect");
	hardware->getDisplay()->drawString(x + 50, 0, "PW="+String(agg->getHeater()->getPower()));
	hardware->getDisplay()->drawString(x, y + 13, "TSA=" + String(hardware->getTTSA()->getTemp()));
	hardware->getDisplay()->drawString(x, y + 29, "DEF=" + String(hardware->getTTsarga()->getTemp()));
	switch (work_mode) {
	case PROC_OFF:
		hardware->getDisplay()->drawString(x, y + 45, "OFF");
		break;
	case PROC_SELF_WORK:
		hardware->getDisplay()->drawString(x, y + 45, "SELF");
		break;
	case PROC_WAIT_SELF:
		hardware->getDisplay()->drawString(x, y + 45, "READY 2 HEAD!");
		break;
	case PROC_WAIT_HEAD:
		hardware->getDisplay()->drawString(x, y + 45, "READY 2 BODY!");
		break;
	case PROC_GET_HEAD:
		hardware->getDisplay()->drawString(x, y + 45, "GET HEAD");
		break;
	case PROC_FORSAJ:
		hardware->getDisplay()->drawString(x, y + 45, "FORSAJ");
		break;
	case PROC_WORK:
		hardware->getDisplay()->drawString(x, y + 45, "WORKING");
		break;
	}
}

void Rectify::makeMenu()
{
	menu = new Menu();
	menu->setActive(true);
	mcmd = new MenuCommand("Start", 1);
	menu->add(mcmd);
	cont = new MenuCommand("Continue", 4);
	cont->setVisible(false);
	menu->add(cont);
	menu->add(new MenuCommand("Hide menu", 2));
	menu->add(new MenuCommand("Return", 3));

	Menu * setup = new Menu();
	setup->setParent(menu);
	setup->setActive(true);
		
	MenuIParameter * pwHWork = new MenuIParameter("Head Power", setup, 10);
	MenuFParameter * pwHKran = new MenuFParameter("Head Kran", setup, 11);
	MenuIParameter * pwWork = new MenuIParameter("Power", setup, 12);
	MenuFParameter * pwKran = new MenuFParameter("Kran", setup, 13);
	MenuIParameter * tFor = new MenuIParameter("T Forsaj", setup, 14);
	MenuFParameter * tEnd = new MenuFParameter("T End", setup, 15);
	MenuIParameter * wSelf = new MenuIParameter("Work Self", setup, 16);
	MenuBParameter * hColl = new MenuBParameter("No Head", setup, 17);//to continue (head already collected)
	MenuBParameter * mTail = new MenuBParameter("Get Tail", setup, 18);//Get tail or stop after body

	setup->add(wSelf);
	setup->add(pwHWork);
	setup->add(pwHKran);
	setup->add(pwWork);
	setup->add(pwKran);
	setup->add(tFor);
	setup->add(tEnd);
	setup->add(hColl);
	setup->add(mTail);

	menu->add(new MenuSubmenu("Setup", setup));
}

void Rectify::command(MenuCommand * id)
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
		if (work_mode != PROC_OFF)
		{
			stop(PROCEND_MANUAL);
		}
		workMode.setCurrent(MODE_MAIN);
		break;
	case 4:
		menu->setActive(true);
		next();
		break;
	}
}

void Rectify::initParams(MenuParameter * mp)
{
	if (mp == NULL) return;
	switch (mp->getId()) {
	case 10:
		((MenuIParameter *)mp)->setup(CONF.getRectHeadPower(), 1, 20, 100);
		break;
	case 11:
		((MenuFParameter *)mp)->setup(CONF.getRectHeadKranOpened(), 0.2, 15, 80);
		break;
	case 12:
		((MenuIParameter *)mp)->setup(CONF.getRectWorkPower(), 1, 10, 100);
		break;
	case 13:
		((MenuFParameter *)mp)->setup(CONF.getRectKranOpened(), 0.2, 15, 80);
		break;
	case 14:
		((MenuIParameter *)mp)->setup(CONF.getRectForsajTemp(), 1, 10, 100);
		break;
	case 15:
		((MenuFParameter *)mp)->setup(CONF.getRectStopTemp(), 0.1, 50, 85);
		break;
	case 16:
		((MenuIParameter *)mp)->setup(CONF.getRectWorkSelf(), 5, 5, 100);
		break;
	case 17:
		((MenuBParameter *)mp)->setup(head_collected);
		break;
	case 18:
		((MenuBParameter *)mp)->setup(getTail);
		break;
	}
}

void Rectify::acceptParams(MenuParameter * mp)
{
	if (mp == NULL) return;
	switch (mp->getId())
	{
	case 10:
		CONF.setRectHeadPower(((MenuIParameter *)mp)->getCurrent());
		if (work_mode == PROC_GET_HEAD || work_mode == PROC_SELF_WORK) {
			agg->getHeater()->setPower(CONF.getRectHeadPower());
		}
		break;
	case 11:
		CONF.setRectHeadKranOpened(((MenuFParameter *)mp)->getCurrent());
		if (work_mode == PROC_GET_HEAD || work_mode == PROC_SELF_WORK) {
			agg->getKran()->openQuantum(CONF.getRectHeadKranOpened());
		}
		break;
	case 12:
		CONF.setRectWorkPower(((MenuIParameter *)mp)->getCurrent());
		if (work_mode == PROC_WORK) {
			agg->getHeater()->setPower(CONF.getRectWorkPower());
		}
		break;
	case 13:
		CONF.setRectKranOpened(((MenuFParameter *)mp)->getCurrent());
		if (work_mode == PROC_WORK) {
			agg->getKran()->openQuantum(CONF.getRectKranOpened());
		}
		break;
	case 14:
		CONF.setRectForsajTemp(((MenuIParameter *)mp)->getCurrent());
		break;
	case 15:
		CONF.setRectStopTemp(((MenuFParameter *)mp)->getCurrent());
		break;
	case 16:
		CONF.setRectWorkSelf(((MenuIParameter *)mp)->getCurrent());
		break;
	case 17:
		head_collected = ((MenuBParameter *)mp)->getCurrent();
		break;
	case 18:
		getTail = ((MenuBParameter *)mp)->getCurrent();
		break;

	}
}

void Rectify::start()
{
	work_mode = PROC_FORSAJ;
	//err = PROCERR_OK;
	end_reason = PROCEND_NO;
	agg->getHeater()->setPower(98);
	agg->getHeater()->start();
	//hardware->getUrovenWS()->arm(25);
	hardware->getFloodWS()->arm(25);
	hardware->reSetAlarm1();
	hardware->reSetAlarm2();
	mcmd->setName("Stop");
	//TSAchecked = 0;
	//TSAcheckedCold = 0;

	coldBeginCheck = 0;
	tsa_alarms = 0;
	stop_defined = false;
	readTime();
	logg.logging("Rectify process started at " + String(tim));
}

void Rectify::stop(uint8_t reason)
{
	work_mode = PROC_OFF;
	end_reason = reason;
	readTime();
	switch (end_reason)
	{
	case PROCEND_FAULT:
		logg.logging("Rectify fault and finished at " + String(tim));
		break;
	case PROCEND_MANUAL:
		logg.logging("Rectify manually stopped at " + String(tim));
		break;
	case PROCEND_TEMPERATURE:
		logg.logging("Rectify normal finished at " + String(tim));
		break;
	case PROCEND_UROVEN:
		logg.logging("Rectify finished at " + String(tim)+" by uroven sensor");
		break;
	case PROCEND_FLOOD:
		logg.logging("Rectify finished at " + String(tim) + " by flood sensor");
		break;
	case PROCEND_NO_ATT_HEAD:
		logg.logging("Rectify finished at " + String(tim) + " by no attention after head");
		break;
	case PROCEND_NO_ATT_SELF:
		logg.logging("Rectify finished at " + String(tim) + " by no attention after self work");
		break;
	default:
		break;
	}
	agg->getHeater()->setPower(0);
	agg->getHeater()->stop();
	agg->getKran()->forceClose();
	hardware->getFloodWS()->disarm();
	hardware->getUrovenWS()->disarm();
	hardware->reSetAlarm1();
	hardware->reSetAlarm2();
	mcmd->setName("Start");
}

void Rectify::next() {
	hardware->reSetAlarm2();
	switch (work_mode) {
	case PROC_WAIT_SELF:
		hardware->getUrovenWS()->arm(25);
		cont->setVisible(false);
		menu->setActive(false);
		logg.logging("Rectify Collech HEAD started at " + getTimeStr());
		work_mode = PROC_GET_HEAD;
		break;
	case PROC_WAIT_HEAD:
		coldBeginCheck = 0;
		agg->getHeater()->setPower(CONF.getRectWorkPower());
		agg->getKran()->openQuantum(CONF.getRectKranOpened());
		hardware->getUrovenWS()->disarm();
		CONF.setRectStopTemp(hardware->getTTsarga()->getTemp() + 1.5f);//пока так а
		hardware->reSetAlarm2();
		hardware->setAlarm2(40);//через N минут определим температуру окончани¤
		cont->setVisible(false);
		menu->setActive(false);
		logg.logging("Rectify Collech BODY started at " + getTimeStr());
		work_mode = PROC_WORK;
		break;
	case PROC_WAIT_TAIL:
		cont->setVisible(false);
		menu->setActive(false);
		logg.logging("Rectify Collech TAIL started at " + getTimeStr());
		work_mode = PROC_GET_TAIL;
		break;
}
}

void Rectify::process(long ms)
{
	if (work_mode == PROC_OFF) return;
	if (last_time + test_time - ms > 0) return;
	last_time = ms;
	
	volatile float tcube = hardware->getTKube()->getTemp();
	volatile float ttsa = hardware->getTTSA()->getTemp();
	volatile float tdef = hardware->getTTsarga()->getTemp();

	switch (work_mode) {
	case PROC_FORSAJ:
		if (tdef > CONF.getRectForsajTemp()) {//end of forsaj
			agg->getHeater()->setPower(CONF.getRectHeadPower());
			agg->getKran()->openQuantum(CONF.getRectHeadKranOpened());
			logg.logging("Rectify forsaj finished at " + getTimeStr());
			hardware->getBeeper()->beep(2000, 1000);
			work_mode = PROC_SELF_WORK;
			hardware->reSetAlarm2();
			hardware->reSetAlarm1();
			hardware->setAlarm2((int)CONF.getRectWorkSelf());//через CONF.getRectWorkSelf() мин заканчиваем работать на себ¤
			hardware->setAlarm1(3);//начинаем провер¤ть “—ј
		}
		break;
	case PROC_SELF_WORK:
		if (hardware->getClock()->checkAlarm2()){
			logg.logging("Rectify Work Self finished at " + getTimeStr());
			work_mode = head_collected? PROC_WAIT_HEAD:PROC_WAIT_SELF;
			hardware->reSetAlarm2();
			hardware->setAlarm2(10);
			hardware->getBeeper()->beep(1000, 5000);
			cont->setVisible(true);
			menu->setActive(true);
			ss_active = false;
			last_action = ms;
		}
		break;
	case PROC_WAIT_SELF:
		if (hardware->getClock()->checkAlarm2()) {//если за 10 минут никто не подошел
		stop(PROCEND_NO_ATT_SELF);
		}
		break;
	case PROC_GET_HEAD: 
		if (hardware->getUrovenWS()->isAlarmed()) {
			logg.logging("Rectify collect head finished at " + getTimeStr());
			work_mode = PROC_WAIT_HEAD;
			hardware->reSetAlarm2();
			hardware->setAlarm2(10);
			hardware->getBeeper()->beep(2000, 5000);
			cont->setVisible(true);
			menu->setActive(true);
			ss_active = false;
			last_action = ms;
		}
		break;
	case PROC_WAIT_HEAD: 
		if (hardware->getClock()->checkAlarm2()) {//если за 10 минут никто не подошел
			stop(PROCEND_NO_ATT_HEAD);
		}
		break;
	case PROC_WORK:
		if (!stop_defined && hardware->getClock()->checkAlarm2()) {
			CONF.setRectStopTemp(tdef + 0.2f);
			stop_defined = true;
			logg.logging("Rectify stop temperature (tdefA=" + String(hardware->getTTsarga()->getTemp(), 2) + ")(tdefB=" + String(tdef, 2) + ") defined (" + String(CONF.getRectStopTemp(), 2) + "C) at " + getTimeStr());
			hardware->getBeeper()->beep(1000, 1000);
		}
		if (tdef > CONF.getRectStopTemp()) {//end of collect body
			if (getTail) {
				logg.logging("Rectify collect body finished at " + getTimeStr());
				work_mode = PROC_WAIT_TAIL;
				hardware->reSetAlarm2();
				hardware->setAlarm2(10);
				cont->setVisible(true);
				menu->setActive(true);
				ss_active = false;
				last_action = ms;
			}
			else {
				stop(PROCEND_TEMPERATURE);
			}
			hardware->getBeeper()->beep(1000, 5000);
		}
		break;
	case PROC_WAIT_TAIL:
		if (hardware->getClock()->checkAlarm2()) {//если за 10 минут никто не подошел
			stop(PROCEND_NO_ATT_TAIL);
		}
		break;
	case PROC_GET_TAIL:
		if (tdef > (CONF.getRectStopTemp()+1.1f)) {//end of collect tail
			stop(PROCEND_TEMPERATURE);
			hardware->getBeeper()->beep(1000, 5000);
		}
		break;
	}
	   
	boolean evnt = false;
	if (hardware->getClock()->checkAlarm1()) {
		if (work_mode == PROC_WORK && coldBeginCheck < 10) coldBeginCheck++;
		if (checkLowTSA && coldBeginCheck >= 5 && ttsa < CONF.getTSAmin())
		{
			hardware->getBeeper()->beep(1000, 500);
			logg.logging("TSA cold (" + String(ttsa) + "C) at " + getTimeStr());
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
		}
		else
		{
			if (tsa_alarms > 0) {
				logg.logging("TSA alarm reset (" + String(ttsa) + "C) at " + getTimeStr());
				tsa_alarms = 0;
			}
		}
		
		hardware->setAlarm1(evnt ? 3 : 3);
	}

	if (ttsa > CONF.getTSAcritical())
	{
		logg.logging("TSA critical T (" + String(ttsa) + "C) at " + getTimeStr());
		stop(PROCEND_FAULT);
	}

	if (hardware->getFloodWS()->isAlarmed()) {
		stop(PROCEND_FLOOD);
	}
}