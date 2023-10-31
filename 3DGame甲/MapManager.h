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
	const float objLen = 100.0f;//�I�u�W�F�N�g�̋���

	const float adjustCylinder = 50.0f;// �~���I�u�W�F�N�g�̒���.
	const VECTOR moveBlockDirHorizon = VGet(1.0f, 0.0f, 0.0f);// ��������.
	std::vector<VECTOR>spawnPos;
	int sizeVector;
};

