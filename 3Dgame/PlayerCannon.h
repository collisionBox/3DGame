#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"


class PlayerCannon : public ObjectBase
{
public:
	// 動的シングルトン.
	static PlayerCannon& Instance() { return *instance; }
	static void CreateInstance();
	static void DereteInstance();

	PlayerCannon();
	~PlayerCannon();

	void Initialize(VECTOR pos, VECTOR dir);

	//void Update(VECTOR bodyPos, VECTOR camDir, float deltaTime);// 更新.
	void Update(float deltaTime) override;
	void Draw();// 描画.

	void Input();

	VECTOR GetPos() const { return pos; }
	VECTOR GetDir() const { return dir; }
private:
	bool GetRightDir(VECTOR camDir);

	/*int modelHandle;
	VECTOR pos;
	VECTOR dir;*/

	static PlayerCannon* instance;

};


