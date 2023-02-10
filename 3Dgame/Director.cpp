#include "Director.h"

Director* Director::Instance = nullptr;

Director::Director()
{
	Instance = nullptr;
}

Director::~Director()
{
	Instance = nullptr;
}

void Director::Initalize()
{
	if (!Instance)
	{
		Instance = new Director;
	}
	joypadNum = 0;
}

void Director::Finalize()
{
	if (Instance)
	{
		delete Instance;
	}
}

void Director::Update()
{
	

}

void Director::OrderChangeScene()
{
	
}

