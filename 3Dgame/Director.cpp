#include "Director.h"


void Director::OrderChangeScene(SceneBase* nextScene)
{
	SCENEINSTANCE.SetScene(nextScene);
}

void Director::CheckWinner()
{
}

