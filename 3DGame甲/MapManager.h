#pragma once
#include "DxLib.h"
#include <vector>
class MapManager
{
public:
	MapManager(int mapNum);
	const VECTOR GetSpawnPos(int i) { return spawnPos[i]; }
	const int GetSizeSpawnPosVector() { return sizeVector; }
private:
	const float objLen = 100.0f;//オブジェクトの距離

	const float adjustCylinder = 50.0f;// 円柱オブジェクトの調整.
	const VECTOR moveBlockDirHorizon = VGet(1.0f, 0.0f, 0.0f);// 水平方向.
	std::vector<VECTOR>spawnPos;
	int sizeVector;
};

