#pragma once
#include "foundation.h"
#include "MapModelBlock.h"
#include "MapModelCylinder.h"
const int mapObjectNumZ = 10;
const int mapObjectNumX = 10;

class Map1
{
public:
    Map1();

private:
    char map[mapObjectNumX][mapObjectNumZ] =
	{
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,1,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
	};

	
};

