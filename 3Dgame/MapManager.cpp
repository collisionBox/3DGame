#include "MapManager.h"

MapManager::MapManager(int mapNum)
{
	const float objLen = 100;//オブジェクトの距離

	const float adjustCylinder = 50.0f;

	static const int mapObjectNumX = 20;
	static const int mapObjectNumZ = 10;
	vector<ObjectBase*> obj;
	struct MapChip
	{
		int Num;
		const int Data[mapObjectNumZ][mapObjectNumX];
	};
	MapChip MapData[] =
	{
		{1,
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
		0,0,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
		0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,1,0,0,0,0,3,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,}}
	};


	struct MAPOBJECT
	{
		int objectNum;
		ObjectBase* mapObj;
	};
	for (int k = 0; k < sizeof MapData / sizeof MapData[0]; k++)
	{
		if (MapData[k].Num == mapNum)
		{
			for (int i = 0; i < mapObjectNumX; i++)
			{
				for (int j = 0; j < mapObjectNumZ; j++)
				{
					float x = WindowSizeXMin + objLen * i;
					float z = WindowSizeZMax - objLen * j;
					MAPOBJECT mapObj[] =
					{
						{1, new MapModelBlock(VGet(x, 0, z)) },
						{2, new MapModelCylinder(VGet(x + adjustCylinder, 0, z - adjustCylinder))},
						{3, new MapModelMoveBlockVertical(VGet(x, 0.0f, z)) }
					};
					for (int l = 0; l < sizeof mapObj / sizeof mapObj[0]; l++)
					{
						if (MapData[k].Data[j][i] == mapObj[l].objectNum)
						{
							obj.push_back(mapObj[l].mapObj);
						}

					}

				}
			}

		}
	}
	


	for (int i = 0; i < mapObjectNumX; i++)
	{
		for (int j = 0; j < mapObjectNumZ; j++)
		{
			float x = WindowSizeXMin + objLen * i;
			float z = WindowSizeZMax - objLen * j;
			MAPOBJECT mapObj[] =
			{
				{1, new MapModelBlock(VGet(x, 0, z)) },
				{2, new MapModelCylinder(VGet(x + adjustCylinder, 0, z - adjustCylinder))},
				{3, new MapModelMoveBlockVertical(VGet(x, 0.0f, z)) }
			};
			for (int l = 0; l < sizeof mapObj / sizeof mapObj[0]; l++)
			{
				
				if (map2[j][i] == mapObj[l].objectNum)
				{
					//obj.push_back(mapObj[l].mapObj);
				}
			}

		}
	}


	for (auto& i : obj)
	{
		ObjectManager::Entry(i);
	}
}

