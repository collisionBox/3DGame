#pragma once
#include "foundation.h"
#include "Map.h"
#include "MapModelBlock.h"
#include "MapModelCylinder.h"
#include "MapModelMoveBlockVertical.h"
class MapManager
{
public:
	MapManager(int mapNum);
private:
	const float adjustCylinder = 50.0f;
};

