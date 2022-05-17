#include "CGameMap.h"

void CGameMap::Update(DWORD dt, vector<LPCGameObject>* coObjects)
{
}

void CGameMap::Render()
{
	DrawAnimation();
}

void CGameMap::DrawAnimation()
{
	CAnimationManager::GetInstance()->Get("Sea_Map0").get()->Render(Obj_Position + Vec2(0,39.5), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
	CAnimationManager::GetInstance()->Get("Sea_Map1").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
}
