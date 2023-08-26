#pragma once
#include "ObjectBase.h"
#include "SceneBase.h"
enum class GameModeStatus
{
	Single,
	Multi,
};
class Director
{
public:
	static Director& GetInstance()
	{
		static Director instance;
		return instance;
	}
	void Initialize();
	void SelectGameMode(GameModeStatus select);
	const GameModeStatus GetGameMode() { return gameMode; }
	void OrderChangeScene(SceneBase* nextScene);
	void CheckHP(const ObjectBase* player[], float deltaTime);
private:
	const float OnShootingDownWaitTime = 5.0f;// ”íŒ‚’ÄŽž‘Ò‹@ŽžŠÔ.
	float deltaWaitTime;// ‘Ò‹@ŽžŠÔ.
	GameModeStatus gameMode;



};
#define DIRECTORINSTANCE Director::GetInstance()
