#include "Object_notmoving.h"
void Object_notmoving::Update(DWORD dt, vector<LPCGameObject>* coObjects)
{
	if (isActivated)
	{

	}
}

void Object_notmoving::Render()
{
	DrawAnimation();
}

void Object_notmoving::DrawAnimation()
{
	CAnimationManager::GetInstance()->Get("Old_Boat").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
	CAnimationManager::GetInstance()->Get("Old_plank").get()->Render(Obj_Position - Vec2(-100,316), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));

}
