#include "CStair.h"

void CStair::Update(DWORD dt, vector<LPCGameObject>* coObjects)
{
}

void CStair::Render()
{
	//this->DrawAnimation();

}

void CStair::DrawAnimation()
{
	//CAnimationManager::GetInstance()->Get("stair").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
}

Vec2 CStair::GetDirect()
{
	return direct;
}
