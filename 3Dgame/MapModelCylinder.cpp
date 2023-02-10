#include "MapModelCylinder.h"

MapModelCylinder::MapModelCylinder(VECTOR initPos):
	ObjectBase(ObjectTag::BackGround)
{
	modelHandle = MV1LoadModel("data/map/cylinder.mv1");
	MV1SetScale(modelHandle, VGet(0.24f, 0.3f, 0.24f));// �T�C�Y��100*100�ɂ���.
	colModel = modelHandle;
	pos = initPos;
	MV1SetPosition(modelHandle, initPos);
	CollisionUpdate();
}

MapModelCylinder::~MapModelCylinder()
{
	AssetManager::DeleteMesh(modelHandle);
}

void MapModelCylinder::Update(float deltaTime)
{
}

void MapModelCylinder::Draw()
{
	MV1DrawModel(modelHandle);
}