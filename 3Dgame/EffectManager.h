#pragma once
#include "SystemVariable.h"
#include "EffectBase.h"

class EffectManager final
{
public:

	static void Initialize();

	static void Entry(EffectBase* newEffect);
	static void Relese(EffectBase* releseEffevct);
	static void ReleseAllEffect();

	static void Update(float deltaTime);
	static void Draw();
	static void Finalize();
private:
	EffectManager();
	~EffectManager();
	vector<EffectBase*>pendingEffect;
	vector<EffectBase*>effects;
	static EffectManager* Instance;
};

