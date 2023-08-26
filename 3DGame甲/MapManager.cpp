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
						{MoveBlock, new MapModelMoveBlockVertical(VGet(x, 0.0f, z), moveBlockDirHorizon)}
					};
					for (int l = 0; l < sizeof mapObj / sizeof mapObj[0]; l++)
					{
						if (MapData[k].Data[j][i] == PlayerSpawnPos)
						{
							auto itr = spawnPos.begin();
							spawnPos.insert(itr, VGet(x, 0.0f, z));
							break;
						}
						else if (MapData[k].Data[j][i] == EnemySpawnPos)
						{
							spawnPos.push_back(VGet(x, 0.0f, z));
							break;
						}
						else if (MapData[k].Data[j][i] == mapObj[l].objectNum)
						{
							obj.push_back(mapObj[l].mapObj);
						}
					}
				}
			}
			break;
		}
	}

	// �I�u�W�F�N�g�}�l�[�W���[�ɓo�^.
	for (auto& i : obj)
	{
		ObjectManager::Entry(i);
	}

	sizeVector = spawnPos.size();
}

