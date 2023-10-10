#include "MapManager.h"
#include <vector>
#include "ObjectManager.h"
#include "MapModelBlock.h"
#include "MapModelCylinder.h"
#include "MapModelMoveBlockVertical.h"
#include "MapData.h"

using namespace std;

MapManager::MapManager(int mapNum)
{
	vector<ObjectBase*> obj;
	

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
						{Block, new MapModelBlock(VGet(x, 0, z)) },
						{Cylinder, new MapModelCylinder(VGet(x + adjustCylinder, 0, z - adjustCylinder))},
						{VerticalMoveBlock, new MapModelMoveBlockVertical(VGet(x, 0.0f, z), moveBlockDirHorizon)}
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
			break;
		}
	}

	// オブジェクトマネージャーに登録.
	for (auto& i : obj)
	{
		ObjectManager::Entry(i);
	}
}

