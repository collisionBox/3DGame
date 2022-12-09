#include "ObjectBase.h"
#include "AssetManager.h"

ObjectBase::ObjectBase(ObjectTag tag)
	:tag(tag)
	,pos()
	,modelHandle(-1)
	,visible(true)
	,alive(true)
{
}

ObjectBase::ObjectBase(ObjectTag tag, VECTOR pos)
	:tag(tag)
	,pos()
	,modelHandle(-1)
	,alive(true)
{
	this->pos = pos;
}

ObjectBase::~ObjectBase()
{
	if (modelHandle != -1)
	{
		AssetManager::DeleteMesh(modelHandle);
		modelHandle = -1;
	}
}

void ObjectBase::Draw()
{
}
