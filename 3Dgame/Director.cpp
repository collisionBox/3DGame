#include "Director.h"


void Director::Initialize()
{
	deltaWaitTime = 0.0f;

}

void Director::OrderChangeScene(SceneBase* nextScene)
{
	SCENEINSTANCE.SetScene(nextScene);
}

void Director::CheckHP(const ObjectBase* player[PlayerNum], float deltaTime)
{

	for (int i = 0; i < PlayerNum; i++)
	{
		if (player[i]->GetHP() <= 0)
		{
			
		}
	}
}

