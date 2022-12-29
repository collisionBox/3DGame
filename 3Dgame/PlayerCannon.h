#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"


class PlayerCannon
{
public:
	PlayerCannon();
	~PlayerCannon();

	void Initialize(VECTOR pos, VECTOR dir);

	void Update(VECTOR pos, float deltaTime);// �X�V.
	void Draw();// �`��.

	void Input();
private:
	int modelHandle;
	VECTOR pos;
	VECTOR dir;
	VECTOR a;


};

