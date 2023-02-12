#pragma once
#include "foundation.h"

class Director final
{
public:

	static void Initalize();// 初期化
	static void Finalize();// 終了処理
	static void Update();// 更新
	static void OrderChangeScene();
private:
	Director();
	~Director();


	//static int joypadNum;

	static Director* Instance;

};

