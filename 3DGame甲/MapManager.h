#pragma once
#include "DxLib.h"
#include <vector>
#include <map>
#include <string>

class MapManager
{
public:
	MapManager(int mapNum);
private:
	const float objLen = 100.0f;//�I�u�W�F�N�g�̋���

	const float adjustCylinder = 50.0f;// �~���I�u�W�F�N�g�̒���.
	const VECTOR moveBlockDirHorizon = VGet(1.0f, 0.0f, 0.0f);// ��������.
	const VECTOR moveBlockDirVirtical = VGet(0.0f, 0.0f, 1.0f);// ��������.
	std::vector<VECTOR>spawnPos;
	std::vector<VECTOR>enemySpawnPos;
	int enemySpawnNum;// �G�X�|�[����.
	const VECTOR LookRight = VGet(-1.0f, 0.0f, 0.0f);
	const VECTOR LookLeft = VGet(1.0f, 0.0f, 0.0f);
};
static const int mapObjectNumX = 19;
static const int mapObjectNumZ = 10;

static const std::string Block = "1";// �u���b�N�̈ʒu�ԍ�.
static const std::string Cylinder = "2";// �~���}�b�v�I�u�W�F�N�g�̈ʒu�ԍ�.
static const std::string MoveBlockVirtical = "3";// �����ɓ����u���b�N�}�b�v�I�u�W�F�N�g�̈ʒu�ԍ�.
static const std::string MoveBlockHolizon = "4";// �����ɓ����u���b�N�}�b�v�I�u�W�F�N�g�̈ʒu�ԍ�.
static const std::string PlayerSpawnPos = "P";// �v���C���[�X�|�[���ʒu�ԍ�.
static const std::string EnemySpawnPos = "E";// �G�X�|�[���ʒu�ԍ�.
static const std::vector<std::string>MapDataPath = 
{ "map0.csv","map1.scv","map2.scv","map3.csv"};

