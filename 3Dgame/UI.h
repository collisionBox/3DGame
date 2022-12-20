#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include "ObjectTag.h"

const int white = GetColor(255, 255, 255);
const int black = GetColor(0, 0, 0);
const int red = GetColor(255, 0, 0);
const int green = GetColor(0, 255, 0);
const int blue = GetColor(0, 0, 255);

class UI final
{
public:
	UI();
	~UI();
	void Draw(float deltaTime);
	
private:
	void Debug();
	
};