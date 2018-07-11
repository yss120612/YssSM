// 
// 
// 

#include "Mode.h"


Mode::Mode(Aggregates * a,Hardware * h)
{
	parent = NULL;
	agg = a;
	hardware = h;
}

void Mode::drawImm()
{
	if (!drawImmed) return;
	draw();
	drawImmed = false;
}
