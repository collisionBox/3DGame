#pragma once
#include "ObjectBase.h"

class MapModelCylinder :
	public ObjectBase
{
public:
	MapModelCylinder(VECTOR initPos);
	~MapModelCylinder();

	void Update(float deltaTime);
	void Draw();


private:


};

