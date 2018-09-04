#include "Rectify.h"

Rectify::Rectify(Aggregates * a, Hardware *h) : Mode(a, h)
{
	MyName = "Rectify";
	makeMenu();
}

Rectify::~Rectify()
{
	delete mcmd;
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
				return "WORKING";
				break;
			case PROC_GET_HEAD:
				return "GET HEAD";
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
	hardware->getDisplay()->drawString(x, 0, "Dist");
	hardware->getDisplay()->drawString(x + 40, 0, "PW="+String(agg->getHeater()->getPower()));

	hardware->getDisplay()->drawString(x, y + 13, "TSA=" + String(hardware->getTTSA()->getTemp()));
	hardware->getDisplay()->drawString(x, y + 29, "DEF=" + String(hardware->getTTsarga()->getTemp()));
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

	setup->add(wSelf);
	setup->add(pwHWork);
	setup->add(pwHKran);
	setup->add(pwWork);
	setup->add(pwKran);
	setup->add(tFor);
	setup->add(tEnd);

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

void Rectify::start()
{
	work_mode = PROC_FORSAJ;
	err = PROCERR_OK;
	end_reason = PROCEND_NO;
	agg->getHeater()->setPower(98);
	agg->getHeater()->start();
	//hardware->getUrovenWS()->arm(25);
	hardware->getFloodWS()->arm(25);
	mcmd->setName("Stop");
	TSAchecked = 0;
	TSAcheckedCold = 0;
	coldBeginCheck = 0;
	tsa_alarms = 0;
	readTime();
	logg.logging("Distill process started at " + String(tim));
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
	}
}

void Rectify::acceptParams(MenuParameter * mp)
{
	if (mp == NULL) return;
	switch (mp->getId())
	{
	case 10:
		CONF.setRectHeadPower(((MenuIParameter *)mp)->getCurrent());
		if (work_mode == PROC_GET_HEAD) {
			agg->getHeater()->setPower(CONF.getRectHeadPower());
		}
		break;
	case 11:
		CONF.setRectHeadKranOpened(((MenuFParameter *)mp)->getCurrent());
		if (work_mode == PROC_GET_HEAD) {
			agg->getKran()->openQuantum(CONF.getRectHeadKranOpened());
		}
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
	case 14:
		CONF.setRectForsajTemp(((MenuIParameter *)mp)->getCurrent());
		break;
	case 15:
		CONF.setRectStopTemp(((MenuFParameter *)mp)->getCurrent());
		break;
	case 16:
		CONF.setRectWorkSelf(((MenuFParameter *)mp)->getCurrent());
		break;
	
	}
}

void Rectify::next() {
	switch (work_mode) {
	case PROC_WAIT_SELF:
		work_mode = PROC_GET_HEAD;
		hardware->getUrovenWS()->arm(25);
		cont->setVisible(false);
		break;
	case PROC_WAIT_HEAD:
		work_mode = PROC_WORK;
		agg->getHeater()->setPower(CONF.getRectWorkPower());
		agg->getKran()->openQuantum(CONF.getRectKranOpened());
		hardware->getUrovenWS()->disarm();
		cont->setVisible(false);
		break;
}
}


void Rectify::process(long ms)
{
	if (work_mode == PROC_OFF) return;
	if (last_time + test_time - ms > 0) return;
	last_time = ms;
	
	tcube = hardware->getTKube()->getTemp();
	ttsa = hardware->getTTSA()->getTemp();
	tdef = hardware->getTTsarga()->getTemp();

	switch (work_mode) {
	case PROC_FORSAJ:
		if (tdef > CONF.getRectForsajTemp()) {//end of forsaj
			agg->getHeater()->setPower(CONF.getRectHeadPower());
			agg->getKran()->openQuantum(CONF.getRectHeadKranOpened());
			readTime();
			logg.logging("Rectify forsaj finished at " + String(tim));
			work_mode = PROC_SELF_WORK;
			workSelf = ms + 1000 * 60 * CONF.getRectWorkSelf();//через 15 мин заканчиваем работать на себя
		}
		break;
	case PROC_SELF_WORK:
		if (ms-workSelf>0){
			readTime();
			logg.logging("Rectify Work Self finished at " + String(tim));
			work_mode = PROC_WAIT_SELF;
			hardware->getBeeper()->beep(1000, 5000);
			workSelf = ms + 1000 * 60 * 10;//10 минут
			cont->setVisible(true);
			menu->setActive(true);
		}
		break;
	case PROC_WAIT_SELF:
		if (ms - workSelf > 0) {//если за 10 минут никто не подошел
		stop(PROCEND_NO_ATT_SELF);
		}
		break;
	case PROC_GET_HEAD: 
		if (hardware->getUrovenWS()->isAlarmed()) {
			readTime();
			logg.logging("Rectify collect head finished at " + String(tim));
			work_mode = PROC_WAIT_HEAD;
			hardware->getBeeper()->beep(1000, 5000);
			workSelf = ms + 1000 * 60 * 10;//10 минут
			cont->setVisible(true);
			menu->setActive(true);
		}
		break;
	case PROC_WAIT_HEAD: 
		if (ms - workSelf > 0) {//если за 10 минут никто не подошел
			stop(PROCEND_NO_ATT_HEAD);
		}
		break;
	case PROC_WORK:
		if (tdef > CONF.getRectStopTemp()) {//end of forsaj
			stop(PROCEND_TEMPERATURE);
		}
		//if (coldBeginCheck == 0) coldBeginCheck = ms + 1000 * 60 * 15;//через 15 минут проверяем на минимум
		break;
	}


	//if (coldBeginCheck > 0 && ms - coldBeginCheck > 0 && ttsa < CONF.getTSAmin()) {
	//	if (TSAcheckedCold == 0 || (ms - TSAcheckedCold) > checkTSA) {
	//		readTime();
	//		logg.logging("TSA cold (" + String(ttsa) + "C) at " + String(tim));
	//		agg->getHeater()->shiftPower(3);
	//		//agg->getKran()->shiftQuantum(-0.5);
	//		TSAcheckedCold = ms;
	//	}
	//}
	//else {
	//	TSAcheckedCold = 0;
	//}

	if (ttsa > CONF.getTSAmax()) {
		if (TSAchecked == 0 || (ms - TSAchecked) > checkTSA) {
			readTime();
			logg.logging("TSA alarm (" + String(ttsa) + "C) at " + String(tim));
			agg->getHeater()->shiftPower(-10);
			//agg->getKran()->shiftQuantum(0.5);
			TSAchecked = ms;
			tsa_alarms++;
		}
	}
	else {
		if (tsa_alarms > 0)
		{
			readTime();
			logg.logging("TSA alarm reset (" + String(ttsa) + "C) at " + String(tim));
			tsa_alarms = 0;
		}
		TSAchecked = 0;
	}

	if (tsa_alarms > 3)
	{
		readTime();
		logg.logging("TSA max alarms (" + String(ttsa) + "C) at " + String(tim));
		stop(PROCEND_FAULT);
	}

	if (ttsa > CONF.getTSAcritical())
	{
		readTime();
		logg.logging("TSA critical T (" + String(ttsa) + "C) at " + String(tim));
		stop(PROCEND_FAULT);
	}

	if (hardware->getFloodWS()->isAlarmed()) {
		stop(PROCEND_FLOOD);
	}
}