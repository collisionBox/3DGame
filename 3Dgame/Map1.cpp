#include "Map1.h"

Map1::Map1()
{
	MapModelBlock* block = new MapModelBlock;
	ObjectManager::Entry(block);
	
	MapModelCylinder* cylinder = new MapModelCylinder;
	ObjectManager::Entry(cylinder);
}

