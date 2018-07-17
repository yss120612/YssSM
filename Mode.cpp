// 
// 
// 

#include "Mode.h"


Mode::Mode(Aggregates * a,Hardware * h)
{
	parent = NULL;
	agg = a;
	hardware = h;
	last_action = millis();
}

void Mode::drawImm(long m)
{
	if (!drawImmed) return;
	draw(m);
	drawImmed = false;
}
