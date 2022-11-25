#pragma once
#include "DxLib.h"
class player
{
public:
	static player& GetInstance();//�C���X�^���X���擾.

	player();
	~player();

	void Update();
	void Draw();
	int GetModelHandle() { return modelHandle; }
	const VECTOR& GetPos()const { return pos; }
	const VECTOR& GetDir()const { return dir; }

private:
	int modelHandle;//���f���n���h��.
	VECTOR pos;//�|�W�V����.
	VECTOR dir;//��]����.
	VECTOR velocity;//�ړ���.
	float hitRadius;



};
