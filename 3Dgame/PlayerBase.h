#pragma once
#include "Envaironment.h"
class PlayerBase
{
public:
	static PlayerBase& GetInstance();//インスタンスを取得.

	PlayerBase();
	~PlayerBase();

	void Update();
	void Draw();
	const VECTOR& GetPos()const { return pos; }
	const VECTOR& GetDir()const { return dir; }

private:
	int modelHandle;//モデルハンドル.
	int copyModelHandle;//コピーハンドル.
	VECTOR pos;//ポジション.
	VECTOR dir;//回転方向.
	VECTOR velocity;//移動量.
	float hitRadius;



};

