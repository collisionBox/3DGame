#pragma once
#include "foundation.h"

class Director final
{
public:

	static void Initalize();// ‰Šú‰»
	static void Finalize();// I—¹ˆ—
	static void Update();// XV
	static void OrderChangeScene();
private:
	Director();
	~Director();


	static int joypadNum;

	static Director* Instance;

};

