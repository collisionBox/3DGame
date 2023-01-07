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
	ObjectTag tag;// �o�^��(�o�^�[).
	VECTOR pos;// �ʒu�x�N�g��.
	VECTOR dir;// �����x�N�g��.
	int modelHandle;// ���f���n���h��.
	bool visible;// �\�����邩�ǂ����̃n���h���i�������Ȃ���Ε\���j.
	bool alive;// �����Ă��邩�ǂ����̃n���h��.

	const VECTOR initVec = VGet(0.0f, 0.0f, 0.0f);// ����������p�x�N�g��.
};

