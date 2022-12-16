#pragma once
#include "DxLib.h"
#include "ObjectTag.h"
class ObjectBase
{
public:
	ObjectBase(ObjectTag tag);
	ObjectBase(ObjectTag tag, VECTOR pos);

	virtual ~ObjectBase();


	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }

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
	ObjectTag tag;
	VECTOR pos;
	int modelHandle;
	bool visible;
	bool alive;

};

