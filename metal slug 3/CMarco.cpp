#include "CMarco.h"

void CMarco::Update(DWORD dt)
{
	ProcessKeyboard();
	this->Obj_speed.y -= 1;
	this->Obj_Position += this->Obj_speed;

	if (Obj_Position.y < 200)
	{
		body = Body_states::IDLE;
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
			CAnimationManager::GetInstance()->Get("Marco_body_stand").get()->Render(Obj_Position + Vec2(0,40), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
			break;
		case leg_states::run:
			CAnimationManager::GetInstance()->Get("Marco_leg_run").get()->Render(Obj_Position , D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
			CAnimationManager::GetInstance()->Get("Marco_body_run").get()->Render(Obj_Position + Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
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
			CAnimationManager::GetInstance()->Get("Marco_body_jump").get()->Render(Obj_Position + Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(7, 0));
			break;
		}
		case leg_states::run:
		{
			CAnimationManager::GetInstance()->Get("Marco_leg_run_jump").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(0, 0));
			CAnimationManager::GetInstance()->Get("Marco_body_run_jump").get()->Render(Obj_Position + Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), flag, Obj_Size, Vec2(-1.5, 0));
			break;
		}
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
		flag = true;
		break;
	}
	case DIK_RIGHT:
	{
		Obj_speed.x += Marco_Speed;
		flag = false;
		break;
	}
	case DIK_SPACE:
	{
		if (body != Body_states::jumping)
		{
			Obj_speed.y = 20;
			body = Body_states::jumping;
		}
	}
	default:
		break;
	}
}
