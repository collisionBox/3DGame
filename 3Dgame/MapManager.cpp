#include "MapManager.h"

MapManager::MapManager()
{
	const float objLen = 100;//オブジェクトの距離
	vector<ObjectBase*> obj;
	for (int i = 0; i < mapObjectNumX; i++)
	{
		for (int j = 0; j < mapObjectNumZ; j++)
		{
			float x = windowSizeXMin + objLen * i;
			float z = windowSizeZMax - objLen * j;
			if (map1[j][i] == 1)
			{
				obj.push_back(new MapModelBlock(VGet(x, 0, z)));
			}
			else if (map1[j][i] == 2)
			{
				obj.push_back(new MapModelCylinder(VGet(x+50, 0, z-50)));
			}
		}
	}
	
	

	for (auto& i : obj)
	{
		ObjectManager::Entry(i);
	}
}
