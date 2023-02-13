#pragma once
#include "SceneManager.h"
class Director
{
public:
	static Director& GetInstance()
	{
		static Director instance;
		return instance;
	}
	void OrderChangeScene();
private:




};
#define DIRECTORINSTANCE Director::GetInstance()
