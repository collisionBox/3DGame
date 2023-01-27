#pragma once
#include "foundation.h"

const int mapObjectNumZ = 10;
const int mapObjectNumX = 10;

class Map1 :
    public ObjectBase
{
public:
    Map1();
    ~Map1();

    void Update(float deltaTime)override;
    void Draw()override;
private:
    char map[mapObjectNumX][mapObjectNumZ] =
	{
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,1,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
	};
};

