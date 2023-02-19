#pragma once
#include "SceneManager.h"
#include "ObjectBase.h"
class Director
{
public:
	static Director& GetInstance()
	{
		static Director instance;
		return instance;
	}
	void OrderChangeScene(SceneBase* nextScene);
	void CheckWinner();
private:




};
#define DIRECTORINSTANCE Director::GetInstance()
