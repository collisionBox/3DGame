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
	const float OnShootingDownWaitTime = 5.0f;// 被撃墜時待機時間.
	float deltaWaitTime;// 待機時間.




};
#define DIRECTORINSTANCE Director::GetInstance()
