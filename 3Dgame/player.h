#pragma once
#include "DxLib.h"
class Player
{
public:
	static Player& GetInstance();//インスタンスを取得.

	Player();
	~Player();

	void Update();
	void Draw();
	int GetModelHandle() { return modelHandle; }
	const VECTOR& GetPos()const { return pos; }
	const VECTOR& GetDir()const { return dir; }

private:
	int modelHandle;//モデルハンドル.
	VECTOR pos;//ポジション.
	VECTOR dir;//回転方向.
	VECTOR velocity;//移動量.
	float hitRadius;



};

