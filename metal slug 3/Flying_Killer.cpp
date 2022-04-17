#include "Flying_Killer.h"

void Flying_Killer::Update(DWORD dt, vector<LPCGameObject>* coObjects)
{
	DWORD now = GetTickCount64();
	/*if (states == Flying_killer_states::jump)
	{
		if (now - frame_time > 100 * 11)
		{
			Obj_speed.x = -Flying_killer_speed;
			Obj_speed.y = 0;
			states = Flying_killer_states::attack;
		}
	}
	Obj_Position = Obj_Position + Obj_speed;*/
}

void Flying_Killer::Render()
{
	DrawAnimation();
}

void Flying_Killer::DrawAnimation()
{
	switch (states)
	{
	case Flying_killer_states::jump:
		CAnimationManager::GetInstance()->Get("ani_Flying_killer_jump").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
		break;
	case Flying_killer_states::attack:
		CAnimationManager::GetInstance()->Get("ani_Flying_killer_attack").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0,0));
		break;
	default:
		break;
	}
}
