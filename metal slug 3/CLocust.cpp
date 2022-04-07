#include "CLocust.h"

void CLocust::Update(DWORD dt)
{
}

void CLocust::Render()
{
	DrawAnimation();
}

void CLocust::DrawAnimation()
{
	switch (states)
	{
	case Locust_states::flying:
		CAnimationManager::GetInstance()->Get("ani_Locust_flying").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Locust_states::attack:
		CAnimationManager::GetInstance()->Get("ani_Locust_attack").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Locust_states::preattack:
		CAnimationManager::GetInstance()->Get("ani_Locust_preattack").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Locust_states::turn:
		CAnimationManager::GetInstance()->Get("ani_Locust_turn").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255));
		break;
	default:
		break;
	}
}

void CLocust::SetState(Locust_states state)
{
	this->states = state;
}
