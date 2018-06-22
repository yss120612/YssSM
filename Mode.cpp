// 
// 
// 

#include "Mode.h"


Mode::Mode(Hardware * h)
{
	parent = NULL;
	hardware = h;
}

void Mode::drawImm()
{
	if (!drawImmed) return;
	draw();
	drawImmed = false;
}
