#pragma once
#include "foundation.h"

class Director final
{
public:

	static void Initalize();// ������
	static void Finalize();// �I������
	static void Update();// �X�V
	static void OrderChangeScene();
private:
	Director();
	~Director();


	static int joypadNum;

	static Director* Instance;

};

