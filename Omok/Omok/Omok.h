#pragma once

#ifndef OMOK__H
#define OMOK__H
#include "resource.h"

#define X_COUNT			19
#define Y_COUNT			19

#define START_X			50
#define START_Y			50

#define INTERVAL		26
#define HALF_INTERVAL	INTERVAL/2

#define XPOS(x)			(START_X + (x) * INTERVAL)
#define YPOS(Y)			(START_Y + (Y) * INTERVAL)

unsigned char g_dol[Y_COUNT][X_COUNT];
unsigned char g_step;

#endif // !OMOK__H


