#include "Director.h"
#include "DxLib.h"
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
}

void Director::Finalize()
{
	if (Instance)
	{
		delete Instance;
	}
}

void Director::Update(float deltaTime)
{
}

void Director::Draw()
{
	
}
