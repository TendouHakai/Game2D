#include "CRebel_Solider.h"

void CRebel_Solider::Update(DWORD dt, vector<LPCGameObject>* coObjects)
{
}

void CRebel_Solider::Render()
{
	DrawAnimation();
}

void CRebel_Solider::DrawAnimation()
{
	switch (states)
	{
	case CRebel_Solider_states::IDLE:
		CAnimationManager::GetInstance()->Get("Rebel_Solider_IDLE").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
		break;
	case CRebel_Solider_states::Drop_down:
		CAnimationManager::GetInstance()->Get("Rebel_Solider_drop_down").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
		break;
	case CRebel_Solider_states::Dead_drop_down:
		CAnimationManager::GetInstance()->Get("Rebel_Solider_dead_dropdown").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
		break;
	case CRebel_Solider_states::Dead:
		CAnimationManager::GetInstance()->Get("Rebel_Solider_dead").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
		break;
	case CRebel_Solider_states::Throw_bomb:
		CAnimationManager::GetInstance()->Get("Rebel_Solider_throw_bomb").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
		break;
	default:
		break;
	}
}
