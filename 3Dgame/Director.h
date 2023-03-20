#pragma once
#include "SceneManager.h"
#include "ObjectBase.h"
#include "PlayerBody.h"
class Director
{
public:
	static Director& GetInstance()
	{
		static Director instance;
		return instance;
	}
	void Initialize();
	void OrderChangeScene(SceneBase* nextScene);
	void CheckHP(const ObjectBase* player[], float deltaTime);
private:
	const float OnShootingDownWaitTime = 5.0f;// ”íŒ‚’ÄŽž‘Ò‹@ŽžŠÔ.
	float deltaWaitTime;// ‘Ò‹@ŽžŠÔ.




};
#define DIRECTORINSTANCE Director::GetInstance()
