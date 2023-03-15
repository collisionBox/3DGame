#pragma once
#include "foundation.h"



class UI 
{
public:
	UI();
	~UI();
	void Draw(float deltaTime);
	void Winner(const PlayerBody* player);
private:
	void Debug();
	void DrawStringInTheCenter(string str);
	
};