#include "CHelper_1.h"

void CHelper_1::Update(DWORD dt)
{
}

void CHelper_1::Render()
{
	DrawAnimation();
}

void CHelper_1::DrawAnimation()
{
	switch (state)
	{
	case CHelper_1_state::catched:
		CAnimationManager::GetInstance()->Get("ani_Helper_1_catch").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
		break;
	case CHelper_1_state::drop_items:
		CAnimationManager::GetInstance()->Get("ani_Helper_1_drop_items").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
		break;
	case CHelper_1_state::release:
		CAnimationManager::GetInstance()->Get("ani_Helper_1_release").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
		break;
	case CHelper_1_state::walk:
		CAnimationManager::GetInstance()->Get("ani_Helper_1_walk").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
		break;
	default:
		break;
	}
}
