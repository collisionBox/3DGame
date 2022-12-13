#include "Director.h"
#include "DxLib.h"
Director* Director::instance = nullptr;

Director::Director()
{
	instance = nullptr;
}

Director::~Director()
{
	instance = nullptr;
}

void Director::Initalize()
{
	if (!instance)
	{
		instance = new Director;
	}
}

void Director::Finalize()
{
	if (instance)
	{
		delete instance;
	}
}

void Director::Update(float deltaTime)
{
}

void Director::Draw()
{
	
}
