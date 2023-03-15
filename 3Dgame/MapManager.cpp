#include "MapManager.h"

MapManager::MapManager(int mapNum)
{
	const float objLen = 100;//オブジェクトの距離

	vector<ObjectBase*> obj;
	//struct MAPOBJECT
	//{
	//	int objectNum;
	//	ObjectBase* mapObj;
	//};
	
	for (int i = 0; i < mapObjectNumX; i++)
	{
		for (int j = 0; j < mapObjectNumZ; j++)
		{
			float x = WindowSizeXMin + objLen * i;
			float z = WindowSizeZMax - objLen * j;
			// マップオブジェクトのナンバリング.
			//MAPOBJECT mapObj[] =
			//{
			//	{1, new MapModelBlock(VGet(x, 0, z)) },
			//	{2, new MapModelCylinder(VGet(x + adjustCylinder, 0, z - adjustCylinder))},
			//	{3, new MapModelMoveBlockVertical(VGet(x, 0.0f, z)) }
			//};
			// 以下未確認
			for (int k = 0; k < sizeof MapChip / sizeof MapChip[0]; k++)
			{
				if (MapChip[k].mapNum == mapNum)
				{
					//for (int l = 0; l < sizeof mapObj / sizeof mapObj[0]; l++)
					//{
					//	if (MapChip[k].mapChip[j][i] == mapObj[l].objectNum)
					//	{
					//		obj.push_back(mapObj[l].mapObj);
					//		break;
					//	}

					//}
				}
			}
			
			
		}
	}


	for (auto& i : obj)
	{
		ObjectManager::Entry(i);
	}
}

