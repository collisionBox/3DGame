#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include <vector>

class PlayerCannon : public ObjectBase
{
public:
	// 動的シングルトン.
	/*static PlayerCannon& Instance() { return *instance; }
	static void CreateInstance();
	static void DereteInstance();*/

	PlayerCannon(ObjectBase* body);
	~PlayerCannon();


	//void Update(VECTOR bodyPos, VECTOR camDir, float deltaTime);// 更新.
	void Update(float deltaTime) override;
	void Draw();// 描画.

	void Input();

	VECTOR GetPos() const { return pos; }
	VECTOR GetDir() const { return dir; }
private:
	bool GetCross(VECTOR camDir);
	VECTOR dirVec;

	//static PlayerCannon* instance;
};


