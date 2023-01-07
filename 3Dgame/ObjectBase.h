#pragma once
#include "DxLib.h"
#include "ObjectTag.h"
class ObjectBase
{
public:
	ObjectBase();
	ObjectBase(ObjectTag tag);
	ObjectBase(ObjectTag tag, VECTOR pos);

	virtual ~ObjectBase();


	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }

	const VECTOR& GetDir() const { return dir; }
	//void SetPos(const VECTOR set) { dir = set; }

	bool GetVidible() const { return visible; }
	void SetVisible(bool set) { visible = set; }

	bool GetAlive() const { return alive; }
	void SetAlive(bool setFlag) { alive = setFlag; }

	virtual void OnCollisionEnter(const ObjectBase* other) {};
	virtual void Collition(ObjectBase* other) {};

	virtual void Update(float deltaTime) = 0;
	virtual void Draw();

	ObjectTag GetTag() const { return tag; }

protected:
	ObjectTag tag;// 登録名(登録票).
	VECTOR pos;// 位置ベクトル.
	VECTOR dir;// 方向ベクトル.
	int modelHandle;// モデルハンドル.
	bool visible;// 表示するかどうかのハンドル（何もしなければ表示）.
	bool alive;// 生きているかどうかのハンドル.

	const VECTOR initVec = VGet(0.0f, 0.0f, 0.0f);// 初期化代入用ベクトル.
};

