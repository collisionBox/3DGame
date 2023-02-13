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
	void OrderChangeScene(SceneBase* nextScene);
private:




};
#define DIRECTORINSTANCE Director::GetInstance()
