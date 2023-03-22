#pragma once
#include "ObjectBase.h"

class MapModelBlock :
	public ObjectBase
{
public:
	MapModelBlock(VECTOR initPos);
	~MapModelBlock();

	void Update(float deltaTime);
	void Draw();

private:


};

