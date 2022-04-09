#include "CChowmein.h"

void CChowmein::Update(DWORD dt)
{
}

void CChowmein::Render()
{
	DrawAnimation();
}

void CChowmein::DrawAnimation()
{
	switch (states)
	{
	case CChowmein_States::IDLE:
		CAnimationManager::GetInstance()->Get("ani_chowmein_IDLE").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0,0));
		break;
	case CChowmein_States::Walk:
		CAnimationManager::GetInstance()->Get("ani_chowmein_walk").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
		break;
	case CChowmein_States::MeleeAttack:
		CAnimationManager::GetInstance()->Get("ani_chowmein_melee_attack").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
		break;
	case CChowmein_States::RangeAttack:
		CAnimationManager::GetInstance()->Get("ani_chowmein_range_attack").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
		break;
	case CChowmein_States::Dead:		
		CAnimationManager::GetInstance()->Get("ani_chowmein_dead").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
		break;
	default:
		break;
	}
}

void CChowmein::SetState(CChowmein_States state)
{
	this->states = state;
}
