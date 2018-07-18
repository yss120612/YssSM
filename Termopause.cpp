// 
// 
// 

#include "Termopause.h"

TermoPause::TermoPause()
{
}

TermoPause::~TermoPause()
{
}

void TermoPause::setup(int p, uint8_t t)
{
	_minutes = p;
	_temperature = t;
}

