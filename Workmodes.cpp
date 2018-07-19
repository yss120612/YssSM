// 
// 
// 

#include "Workmodes.h"


WorkModes::WorkModes()
{
	current = NULL;
}

WorkModes::~WorkModes()
{
}

void WorkModes::addMode(Mode * m)
{
	_modes.push_back(m);
}

void WorkModes::setup(Encoder * enc)
{
	encoder = enc;
}

void WorkModes::setCurrent(uint8_t i)
{
	if (i >= 0 && i < _modes.size())
	{
		current = _modes.get(i);
		encoder->setHandler(current);
		current->initDraw();
	}
}

Mode * WorkModes::getCurrent()
{
	return current;
}


WorkModes workMode;