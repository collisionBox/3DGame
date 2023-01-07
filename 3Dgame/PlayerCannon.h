#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include <vector>

class PlayerCannon : public ObjectBase
{
public:
	// ���I�V���O���g��.
	/*static PlayerCannon& Instance() { return *instance; }
	static void CreateInstance();
	static void DereteInstance();*/

	PlayerCannon(ObjectBase* body);
	~PlayerCannon();


	//void Update(VECTOR bodyPos, VECTOR camDir, float deltaTime);// �X�V.
	void Update(float deltaTime) override;
	void Draw();// �`��.

	void Input();

	VECTOR GetPos() const { return pos; }
	VECTOR GetDir() const { return dir; }
private:
	bool GetCross(VECTOR camDir);
	VECTOR dirVec;

	//static PlayerCannon* instance;
};


