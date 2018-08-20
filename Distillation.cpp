// 
// 
// 

#include "Distillation.h"


Distillation::Distillation(Aggregates * a, Hardware *h) : Mode(a,h)
{
	makeMenu();
}

Distillation::~Distillation()
{
}

void Distillation::draw(long m)
{
	hardware->getDisplay()->clear();
	hardware->getDisplay()->setTextAlignment(TEXT_ALIGN_LEFT);
	if (ss_active || m - last_action > CONF.getScrSavMin() * 60000) {
		ss_active = true;
		showState();
	}
	else {

		if (menu != NULL && menu->isActive()) {
			hardware->getDisplay()->drawString(0, 0, "Distillation");
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

void Distillation::initDraw()
{
	last_action = millis();
	ss_active = false;
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
	
	//hardware->getDisplay()->drawString(x, y+29, "DEF=" + String(hardware->getTTsarga()->getTemp()));
	//hardware->getDisplay()->drawString(x, y+45, "KUB=" + String(hardware->getTKube()->getTemp()));
	
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

		//	break;
		//case DS_TTSA:
		//	return String(hardware->getTTSA()->getTemp(), 1);
		//	break;
		default:
			return "";
		break;
		}
		
	}
	return Mode::getData(w);
}




void Distillation::left()
{
	Mode::left();
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
#ifdef ENCODER_LOG
	logg.logging("Distillation left");
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

void Distillation::right()
{
	Mode::right();
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
#ifdef ENCODER_LOG
	logg.logging("Distillation right");
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

void Distillation::press()
{
	Mode::press();
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
#ifdef ENCODER_LOG
	logg.logging("Distillation press");
#endif

	if (menu->isActive())
	{
		processMenuPress();
	}
	else {//MENU IS NOT ACTIVE


	}
	drawImmed = true;
}

void Distillation::long_press()
{
	Mode::long_press();
	if (ss_active) {
		ss_active = false;
		last_action = millis();
		drawImmed = true;
		return;
	}
#ifdef ENCODER_LOG
	logg.logging("Distillation long_press");
#endif
	if (menu->isActive()) {
		processMenuLong();
	}
	else {
		menu->setActive(true);
	}
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
	readTime();
	switch (end_reason)
	{
	case PROCEND_FAULT:
		logg.logging("Distill fault and finished at " + String(tim));
		break;
	case PROCEND_MANUAL:
		logg.logging("Distill manually stopped at " + String(tim));
		break;
	case PROCEND_TEMPERATURE:
		logg.logging("Distill normal finished at " + String(tim));
		break;
	default:
		break;
	}
	agg->getHeater()->setPower(0);
	agg->getHeater()->stop();
	agg->getKran()->forceClose();
	mcmd->setName("Start");
}

void Distillation::start() {
	work_mode = PROC_FORSAJ;
	err = PROCERR_OK;
	end_reason = PROCEND_NO;
	agg->getHeater()->setPower(98);
	agg->getHeater()->start();
	mcmd->setName("Stop");
	TSAchecked = 0;
	TSAcheckedCold = 0;
	coldBeginCheck = 0;
	tsa_alarms = 0;
	readTime();
	logg.logging("Distill process started at " + String(tim));
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
			readTime();
			logg.logging("Distill forsaj finished at "+String(tim));
			work_mode = PROC_WORK;
		}
		break;
	case PROC_WORK:
		if (tcube > CONF.getDistStopTemp()) {//end of forsaj
			stop(PROCEND_TEMPERATURE);
		}
		if (coldBeginCheck == 0) coldBeginCheck = ms + 1000 * 60 * 15;//через 15 минут проверяем на минимум
		break;
	}


	if (coldBeginCheck > 0 && ms- coldBeginCheck > 0 && ttsa < CONF.getTSAmin()) {
		if (TSAcheckedCold == 0 || (ms - TSAcheckedCold) > checkTSA) {
			readTime();
			logg.logging("TSA cold (" + String(ttsa) + "C) at " + String(tim));
			agg->getHeater()->shiftPower(3);
			//agg->getKran()->shiftQuantum(-0.5);
			TSAcheckedCold = ms;
		}
	}
	else {
		TSAcheckedCold= 0;
	}

	if (ttsa > CONF.getTSAmax()) {
		if (TSAchecked == 0 || (ms - TSAchecked) > checkTSA){
		readTime();
		logg.logging("TSA alarm ("+String(ttsa)+"C) at " + String(tim));
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

}