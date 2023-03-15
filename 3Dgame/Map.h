#pragma once
#include "foundation.h"
#include "MapModelBlock.h"
#include "MapModelCylinder.h"
const int mapObjectNumX = 20;
const int mapObjectNumZ = 10;
struct MAPCHIP
{
	int mapNum;
	const char mapChip[mapObjectNumZ][mapObjectNumX];
};

const char map1[mapObjectNumZ][mapObjectNumX] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
	0,0,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
	0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,1,0,0,0,0,3,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};


const MAPCHIP MapChip[] =
 {
	 {1, map1[mapObjectNumZ][mapObjectNumX]}
 };
