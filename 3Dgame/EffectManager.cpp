#include "EffectManager.h"

EffectManager* EffectManager::Instance = nullptr;

EffectManager::EffectManager() :
	effects()
{
	Instance =  nullptr;
}

EffectManager::~EffectManager()
{
	ReleseAllEffect();
}

void EffectManager::Initialize()
{
	if (!Instance)
	{
		Instance = new EffectManager();
	}
}

void EffectManager::Entry(EffectBase* newEffect)
{
	Instance->pendingEffect.push_back(newEffect);
}

void EffectManager::Relese(EffectBase* releseEffevct)
{
	auto iter = find(Instance->pendingEffect.begin(), Instance->pendingEffect.end(), releseEffevct);
	if (iter != Instance->pendingEffect.end())
	{
		iter_swap(iter, Instance->pendingEffect.end() - 1);
		Instance->pendingEffect.pop_back();
		return;
	}
	iter = find(Instance->effects.begin(), Instance->effects.end(), releseEffevct);
	if (iter != Instance->effects.end())
	{
		iter_swap(iter, Instance->effects.end() - 1);
		delete Instance->effects.back();
	}
}

void EffectManager::ReleseAllEffect()
{
	while (!Instance->pendingEffect.empty())
	{
		delete Instance->pendingEffect.back();
		Instance->pendingEffect.pop_back();
	}

	while (!Instance->effects.empty())
	{
		delete Instance->effects.back();
		Instance->effects.pop_back();
	}
}

void EffectManager::Update(float deltaTime)
{
	for (int i = 0; i < Instance->effects.size() ; ++i)
	{
		Instance->effects[i]->Update(deltaTime);
	}

	for (auto pending : Instance->pendingEffect)
	{
		Instance->effects.emplace_back(pending);
	}
	Instance->pendingEffect.clear();

	vector<EffectBase*> invalidEffect;
	for (auto effect : Instance->effects )
	{
		if (!effect->GetValid())
		{
			invalidEffect.emplace_back(effect);
		}
	}
	Instance->effects.erase(remove_if(begin(Instance->effects), end(Instance->effects), [](EffectBase* a) { return !a->GetValid(); }), cend(Instance->effects));

	while (!invalidEffect.empty())
	{
		delete invalidEffect.back();
		invalidEffect.pop_back();
	}

}

void EffectManager::Draw()
{
	for (int i = 0; i < Instance->effects.size(); ++i)
	{
		if (Instance->effects[i]->GetValid())
		{
			Instance->effects[i]->Draw();
		}
	}
}

void EffectManager::Finalize()
{
	ReleseAllEffect();
	if (Instance)
	{
		delete Instance;
		Instance = nullptr;
	}
}
