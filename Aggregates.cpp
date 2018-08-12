// 
// 
// 

#include "Aggregates.h"
#include "Const.h"

Aggregates::Aggregates(Hardware * ha)
{
	hard = ha;
}

Aggregates::~Aggregates()
{
}

void Aggregates::init()
{
	kran.setup(hard, KRAN_CLOSE_PIN, KRAN_OPEN_PIN);
	heater.setup(hard, HEAT_DRV_PIN, HEAT_REL_PIN);
	cool.setup(hard, TRIAC_COOL_PIN);
	//cool.setParams(CONF.getTriakCoolerTemp(),CONF.getTriakCoolerGist());
}

void Aggregates::timed_process(long ms)
{
	cool.process(ms);
}

void Aggregates::process(long ms)
{
	kran.process(ms);
}
