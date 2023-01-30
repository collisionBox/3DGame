#include "MapModelCylinder.h"

MapModelCylinder::MapModelCylinder():
	ObjectBase(ObjectTag::BackGround)
{
	modelHandle = MV1LoadModel("data/map/cylinder.mv1");
	MV1SetScale(modelHandle, VGet(0.3f, 0.3f, 0.3f));
	colModel = modelHandle;

	MV1SetPosition(modelHandle, VGet(100.0f, 0.0f, 200.0f));
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
