#pragma once
#include "foundation.h"
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

