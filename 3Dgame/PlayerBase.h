#pragma once
#include "Envaironment.h"
class PlayerBase
{
public:
	static PlayerBase& GetInstance();//�C���X�^���X���擾.

	PlayerBase();
	~PlayerBase();

	void Update();
	void Draw();
	const VECTOR& GetPos()const { return pos; }
	const VECTOR& GetDir()const { return dir; }

private:
	int modelHandle;//���f���n���h��.
	int copyModelHandle;//�R�s�[�n���h��.
	VECTOR pos;//�|�W�V����.
	VECTOR dir;//��]����.
	VECTOR velocity;//�ړ���.
	float hitRadius;



};

