#include "CMarco.h"

void CMarco::Update(DWORD dt)
{
	ProcessKeyboard();
	this->Obj_speed.y -= 1;
	Vec2 speed = Obj_speed;
	if (body == Body_states::sitting)
	{
		speed = speed / 10;
		if (Weapon == Weapon_State::FIRING)
			speed = Vec2(0, 0);
	}
	
	this->Obj_Position += speed;

	if (Obj_speed.x > 0)
		flag = false;
	else if (Obj_speed.x < 0)
		flag = true;
	if (Obj_Position.y < 200)
	{
		if (body == Body_states::jumping)
		{
			body = Body_states::IDLE;
		}
		Obj_Position.y = 200;
	}
	
	if (Obj_speed.x !=0)
	{
		leg = leg_states::run;
	}
	else
	{
		leg = leg_states::stand;
	}

}

void CMarco::Render()
{
	DrawAnimation();
}

void CMarco::DrawAnimation()
{
	switch (body)
	{
	case Body_states::IDLE:
	{
		switch (leg)
		{
		case leg_states::stand:
			CAnimationManager::GetInstance()->Get("Marco_leg_stand").get()->Render(Obj_Position  , D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
			switch (Weapon)
			{
			case Weapon_State::IDLE:
				CAnimationManager::GetInstance()->Get("Marco_body_stand").get()->Render(Obj_Position + Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
				break;
			case Weapon_State::FIRING:
				CAnimationManager::GetInstance()->Get("Marco_Body_shooting").get()->Render(Obj_Position + Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
				break;
			default:
				break;
			}
			break;
		case leg_states::run:
			CAnimationManager::GetInstance()->Get("Marco_leg_run").get()->Render(Obj_Position , D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
			switch (Weapon)
			{
			case Weapon_State::IDLE:
				CAnimationManager::GetInstance()->Get("Marco_body_run").get()->Render(Obj_Position + Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
				break;
			case Weapon_State::FIRING:
				CAnimationManager::GetInstance()->Get("Marco_Body_shooting").get()->Render(Obj_Position + Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	}
	case Body_states::jumping:
	{
		switch (leg)
		{
		case leg_states::stand:
		{
			CAnimationManager::GetInstance()->Get("Marco_leg_jump").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
			switch (Weapon)
			{
			case Weapon_State::IDLE:
				CAnimationManager::GetInstance()->Get("Marco_body_jump").get()->Render(Obj_Position + Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(7, 0));
				break;
			case Weapon_State::FIRING:
				CAnimationManager::GetInstance()->Get("Marco_Body_shooting").get()->Render(Obj_Position + Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
				break;
			default:
				break;
			}
			break;
		}
		case leg_states::run:
		{
			CAnimationManager::GetInstance()->Get("Marco_leg_run_jump").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
			switch (Weapon)
			{
			case Weapon_State::IDLE:
				CAnimationManager::GetInstance()->Get("Marco_body_run_jump").get()->Render(Obj_Position + Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(-1.5, 0));
				break;
			case Weapon_State::FIRING:
				CAnimationManager::GetInstance()->Get("Marco_Body_shooting").get()->Render(Obj_Position + Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(-1.5, 0));
				break;
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
		break;
	}
	case Body_states::sitting:
	{
		switch (Weapon)
		{
		case Weapon_State::IDLE:
			switch (leg)
			{
			case leg_states::stand:
				CAnimationManager::GetInstance()->Get("Marco_sitting").get()->Render(Obj_Position + Vec2(0, 15), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(7, 0));
				break;
			case leg_states::run:
				CAnimationManager::GetInstance()->Get("Marco_sitting_move").get()->Render(Obj_Position + Vec2(0, 15), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(7, 0));
				break;
			default:
				break;
			}
			break;
		case Weapon_State::FIRING:
			CAnimationManager::GetInstance()->Get("Marco_sitting_firing").get()->Render(Obj_Position + Vec2(0, 15), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
			break;
		default:
			break;
		}	
		break;
	}
	case Body_states::looking_up:
	{
		switch (leg)
		{
		case leg_states::stand:
			CAnimationManager::GetInstance()->Get("Marco_leg_stand").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
			switch (Weapon)
			{
			case Weapon_State::IDLE:
				CAnimationManager::GetInstance()->Get("Marco_Body_up2").get()->Render(Obj_Position + Vec2(0, 45), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(1.5, 0));
				break;
			case Weapon_State::FIRING:
				CAnimationManager::GetInstance()->Get("Marco_Body_up_shooting").get()->Render(Obj_Position + Vec2(0, -3), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(1.5, 1));
				break;
			default:
				break;
			}
			break;
		case leg_states::run:
			CAnimationManager::GetInstance()->Get("Marco_leg_run").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
			switch (Weapon)
			{
			case Weapon_State::IDLE:
				CAnimationManager::GetInstance()->Get("Marco_Body_up2").get()->Render(Obj_Position + Vec2(0, 45), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(1.5, 0));
				break;
			case Weapon_State::FIRING:
				CAnimationManager::GetInstance()->Get("Marco_Body_shooting").get()->Render(Obj_Position + Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(-1.5, 0));
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}	
}

void CMarco::ProcessKeyboard()
{
	DIDEVICEOBJECTDATA KeyData[KEYBOARD_BUFFER_SIZE];
	DWORD* dwElements = new DWORD[KEYBOARD_BUFFER_SIZE];
	if (CKeyBoard::GetInstance()->GetKeyboardData(KeyData,dwElements) == 0)
	{
		return;
	}	
	DWORD dwElementsData = *dwElements;
	for (DWORD i = 0; i < dwElementsData; i++)
	{
		int KeyCode = KeyData[i].dwOfs;
		int KeyState = KeyData[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);		
	}
}

void CMarco::OnKeyUp(int keycode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", keycode);
	switch (keycode)
	{
	case DIK_LEFT:
	{
		Obj_speed.x += Marco_Speed;
		break;
	}
	case DIK_RIGHT:
	{
		Obj_speed.x -= Marco_Speed;
		break;
	}
	case DIK_UP:
	{
		body = Body_states::IDLE;
		break;
	}
	case DIK_DOWN:
	{
		body = Body_states::IDLE;
		break;
	}
	case DIK_A:
	{
		Weapon = Weapon_State::IDLE;
	}
	default:
		break;
	}
}

void CMarco::OnKeyDown(int keycode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", keycode);
	switch (keycode)
	{
	case DIK_LEFT:
	{
		Obj_speed.x -= Marco_Speed;
		break;
	}
	case DIK_RIGHT:
	{
		Obj_speed.x += Marco_Speed;
		break;
	}
	case DIK_A:
	{
		Weapon = Weapon_State::FIRING;
	}
	default:
		break;
	}

	if (body != Body_states::jumping)
	{
		switch (keycode)
		{
		case DIK_SPACE:
			Obj_speed.y = 20;
			body = Body_states::jumping;
			break;
		case DIK_DOWN : 
			body = Body_states::sitting;
			break;
		case DIK_UP : 
			body = Body_states::looking_up;
			break;
		default:
			break;
		}		
	}
}
