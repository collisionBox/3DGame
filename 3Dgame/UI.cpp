#include "UI.h"
#include "PlayerBody.h"

UI::~UI()
{
	
}

void UI::Draw(float deltaTime)
{
	Debug();
}

void UI::Debug()
{
	//VECTOR pPos = PlayerBody::instance().GetPos();
	DrawFormatString(0, 0, white, "%f\n%f\n%f", pPos.x, pPos.y, pPos.z);
}
