#include "CMarco.h"
#include "CGame.h"
CMarco* CMarco::_Instance = NULL;

void CMarco::Update(DWORD dt, vector<LPCGameObject>* coObjects)
{
	if (HealBar == 0 && IsDead == false)
	{
		this->IsDead = true;
		DeadTime = GetTickCount64();
	}
	if (IsDead == true)
	{
		DebugOut(L"Marco is dead");

		return;
		//if (DeadTime + 110 * 20 < GetTickCount64())
		//	this->Delete();
	}


	this->IsCollisionStair = false;

	if(!isInWater)
		this->Obj_speed.y -= Marco_Speed_Y;
	//this->Obj_speed.x = 0;
	CGameObject::Update(dt);
	ProcessKeyboard();
	Vec2 speed = Obj_speed;

	//DebugOut(L"Marco speed : %f,%f			%f,%f\n	", Obj_speed.x, Obj_speed.y, speed.x, speed.y);

	if (body == Body_states::sitting)
	{
		Obj_speed.x = Obj_speed.x / 10;
		if (Weapon == Weapon_State::FIRING)
			Obj_speed.x = 0;
	}

	process(dt, coObjects);
	//this->Obj_Position += Obj_speed *dt;

	if (Obj_speed.x > 0)
		isLeftSize = false;
	else if (Obj_speed.x < 0)
		isLeftSize = true;
	if (IsOnStair)
	{
		float y = (direct.y * (Obj_Position.x - positionStair.x) / direct.x) + positionStair.y - 200;
		if (Obj_Position.y - Obj_Size.y < y)
		{
			if (body == Body_states::jumping)
			{
				body = Body_states::IDLE;
			}
			Obj_Position.y = y + Obj_Size.y;
			Obj_speed.y = 0;
		}
	}
	if (IsOnStair2)
	{
		if (Obj_Position.y - Obj_Size.y <= this->yStair2)
		{
			if (body == Body_states::jumping)
			{
				body = Body_states::IDLE;
			}
			Obj_Position.y = this->yStair2 + Obj_Size.y;
			Obj_speed.y = 0;
			this->IsOnStair2 = false;
			this->yStair2 = 0;
		}
	}
	if (IsCollisionStair && Obj_Position.y <= positionStair.y - 200 + Obj_Size.y)
	{
		Obj_Position.y = positionStair.y - 200 + Obj_Size.y;
		Obj_speed.y = 0;
	}
	if (Obj_Position.y <= 200)
	{
		if (body == Body_states::jumping)
		{
			body = Body_states::IDLE;
		}
		Obj_Position.y = 200;
		Obj_speed.y = 0;
	}
	if (Obj_Position.x < CCamera::GetInstance()->GetSceneStart().x)
	{
		Obj_Position.x = CCamera::GetInstance()->GetSceneStart().x;
	}

	if (Obj_speed.x != 0)
	{
		leg = leg_states::run;
	}
	else
	{
		leg = leg_states::stand;
	}
	Obj_speed.x = speed.x;


	if (Weapon == Weapon_State::FIRING)
	{
		int tickcount = GetTickCount64();
		if (tickcount >= FiringTime + 200)
		{
			float bullet_speed = Gun_Bullet_Speed;
			FiringTime = GetTickCount64();
			LPCGameObject obj;
			if (body == Body_states::looking_up)
			{
				if (isLeftSize)
					obj = new CGunBullet(Obj_Position + Vec2(25, 30), Vec2(0, bullet_speed));
				else
					obj = new CGunBullet(Obj_Position + Vec2(15, 30), Vec2(0, bullet_speed));
			}
			else if (body == Body_states::sitting)
			{
				if (isLeftSize)
					obj = new CGunBullet(Obj_Position + Vec2(0, -33), Vec2(-bullet_speed, 0));
				else
					obj = new CGunBullet(Obj_Position + Vec2(0, -33), Vec2(bullet_speed, 0));
			}
			else
			{
				if (isLeftSize)
					obj = new CGunBullet(Obj_Position + Vec2(0, -15), Vec2(-bullet_speed, 0));
				else
					obj = new CGunBullet(Obj_Position + Vec2(0, -15), Vec2(bullet_speed, 0));
			}
			string id = "11000" + to_string(bulletcount);
			CGame::GetInstance()->AddObjectsToCurrrentScene(stoi(id), obj);
			//Cplayscene::GetInstance()->AddObject(stoi(id), obj);
			bulletcount++;
		}
	}
	if (isInWater)
	{
		DebugOut(L"\n");
	}
	//DebugOut(L"Postion marco %f %f \n", Obj_Position.x, Obj_Position.y);
}

void CMarco::Render()
{
	DrawAnimation();
}

void CMarco::DrawAnimation()
{
	if (IsDead)
	{
		CAnimationManager::GetInstance()->Get("Marco_dead").get()->Render(Obj_Position - Vec2(0, 45 * 2), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(1.5, 1));
		return;
	}
	switch (body)
	{
	case Body_states::IDLE:
	{
		switch (leg)
		{
		case leg_states::stand:
			CAnimationManager::GetInstance()->Get("Marco_leg_stand").get()->Render(Obj_Position - Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
			switch (Weapon)
			{
			case Weapon_State::IDLE:
				CAnimationManager::GetInstance()->Get("Marco_body_stand").get()->Render(Obj_Position , D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
				break;
			case Weapon_State::FIRING:
				CAnimationManager::GetInstance()->Get("Marco_Body_shooting").get()->Render(Obj_Position , D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
				break;
			default:
				break;
			}
			break;
		case leg_states::run:
			CAnimationManager::GetInstance()->Get("Marco_leg_run").get()->Render(Obj_Position - Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
			switch (Weapon)
			{
			case Weapon_State::IDLE:
				CAnimationManager::GetInstance()->Get("Marco_body_run").get()->Render(Obj_Position , D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
				break;
			case Weapon_State::FIRING:
				CAnimationManager::GetInstance()->Get("Marco_Body_shooting").get()->Render(Obj_Position , D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
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
			CAnimationManager::GetInstance()->Get("Marco_leg_jump").get()->Render(Obj_Position - Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
			switch (Weapon)
			{
			case Weapon_State::IDLE:
				CAnimationManager::GetInstance()->Get("Marco_body_jump").get()->Render(Obj_Position , D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(7, 0));
				break;
			case Weapon_State::FIRING:
				CAnimationManager::GetInstance()->Get("Marco_Body_shooting").get()->Render(Obj_Position , D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
				break;
			default:
				break;
			}
			break;
		}
		case leg_states::run:
		{
			CAnimationManager::GetInstance()->Get("Marco_leg_run_jump").get()->Render(Obj_Position - Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
			switch (Weapon)
			{
			case Weapon_State::IDLE:
				CAnimationManager::GetInstance()->Get("Marco_body_run_jump").get()->Render(Obj_Position , D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(-1.5, 0));
				break;
			case Weapon_State::FIRING:
				CAnimationManager::GetInstance()->Get("Marco_Body_shooting").get()->Render(Obj_Position , D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(-1.5, 0));
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
				CAnimationManager::GetInstance()->Get("Marco_sitting").get()->Render(Obj_Position + Vec2(0, 20) - Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(7, 0));
				break;
			case leg_states::run:
				CAnimationManager::GetInstance()->Get("Marco_sitting_move").get()->Render(Obj_Position + Vec2(0, 20) - Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(7, 0));
				break;
			default:
				break;
			}
			break;
		case Weapon_State::FIRING:
			CAnimationManager::GetInstance()->Get("Marco_sitting_firing").get()->Render(Obj_Position + Vec2(0, 20) - Vec2(0, 40), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
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
			CAnimationManager::GetInstance()->Get("Marco_leg_stand").get()->Render(Obj_Position - Vec2(0, 45), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
			switch (Weapon)
			{
			case Weapon_State::IDLE:
				CAnimationManager::GetInstance()->Get("Marco_Body_up2").get()->Render(Obj_Position , D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(1.5, 0));
				break;
			case Weapon_State::FIRING:
				CAnimationManager::GetInstance()->Get("Marco_Body_up_shooting").get()->Render(Obj_Position + Vec2(0, -3) - Vec2(0,45), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(1.5, 1));
				break;
			default:
				break;
			}
			break;
		case leg_states::run:
			CAnimationManager::GetInstance()->Get("Marco_leg_run").get()->Render(Obj_Position - Vec2(0, 45), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
			switch (Weapon)
			{
			case Weapon_State::IDLE:
				CAnimationManager::GetInstance()->Get("Marco_Body_up2").get()->Render(Obj_Position , D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(1.5, 0));
				break;
			case Weapon_State::FIRING:
				CAnimationManager::GetInstance()->Get("Marco_Body_up_shooting").get()->Render(Obj_Position + Vec2(0, -3), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(1.5, 1));
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

void CMarco::SetDirectOnStair(Vec2 direct, int stairType, Vec2 positionStair)
{
	this->direct = direct;
	this->stairType = stairType;
	this->positionStair = positionStair;
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
		Obj_speed.x += Marco_Speed_X;
		break;
	}
	case DIK_RIGHT:
	{
		Obj_speed.x -= Marco_Speed_X;
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
		Obj_speed.x -= Marco_Speed_X;
		if (IsOnStair && body != Body_states::jumping)
		{
			Obj_speed.y = direct.y * Obj_speed.x / direct.x;
		}
		break;
	}
	case DIK_RIGHT:
	{
		Obj_speed.x += Marco_Speed_X; 
		if (IsOnStair && body != Body_states::jumping)
		{
			Obj_speed.y = direct.y * Obj_speed.x / direct.x;
		}
		break;
	}
	case DIK_A:
	{
		Weapon = Weapon_State::FIRING;
		break;
	}
	case DIK_RETURN:
	{
		CGame::GetInstance()->SetNextScene();
		break;
	}
	default:
		break;
	}

	if (body != Body_states::jumping)
	{
		switch (keycode)
		{
		case DIK_SPACE:
			Obj_speed.y = 0.6;
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

void CMarco::OnNoCollision(DWORD dt)
{
	this->Obj_Position.x += this->Obj_speed.x * dt;
	this->Obj_Position.y += this->Obj_speed.y * dt;
}

void CMarco::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		this->Obj_speed.y = 0;
		if (body == Body_states::jumping)
		{
			body = Body_states::IDLE;
		}
	}
	else 
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			
		}

	// xữ lý va chạm với các đối tượng không BLOCK
	if (dynamic_cast<CStair*>(e->obj))
		OnCollisionWithStair(e);
	else if (dynamic_cast<CStair2*>(e->obj))
		OnCollisionWithStair2(e);
	else if (dynamic_cast<CChangeCam*>(e->obj))
		OnCollisionWithChangeCam(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
}


void CMarco::OnCollisionWithStair(LPCOLLISIONEVENT e)
{
	this->IsCollisionStair = true;
	CStair* stair = (CStair*)e->obj;
	if (stair->GetStairType() != this->stairType)
	{
		if (IsOnStair)
		{
			IsOnStair = false;
			this->SetDirectOnStair(stair->GetDirect(), stair->GetStairType(), stair->GetPosition());
		}
		else
		{
			IsOnStair = true;
			this->SetDirectOnStair(stair->GetDirect(), stair->GetStairType(), stair->GetPosition());
		}
	}
	else
	{
		if (stair->GetDirect().x * this->Obj_speed.x >= 0)
		{
			if (IsOnStair)
			{
				this->SetDirectOnStair(stair->GetDirect(), stair->GetStairType(), stair->GetPosition());
			}
			else
			{
				IsOnStair = true;
				this->SetDirectOnStair(stair->GetDirect(), stair->GetStairType(), stair->GetPosition());
			}
		}
		else
		{
			if (IsOnStair)
			{
				IsOnStair = false;
				this->SetDirectOnStair(stair->GetDirect(), stair->GetStairType(), stair->GetPosition());
			}
		}
	}
}

void CMarco::OnCollisionWithStair2(LPCOLLISIONEVENT e)
{
	this->IsOnStair2 = true;
	CStair2* stair = (CStair2*)e->obj;
	if(e->ny != 0 && Obj_speed.y < 0)
		this->yStair2 = stair->GetPosition().y;
}

void CMarco::OnCollisionWithChangeCam(LPCOLLISIONEVENT e)
{
	CChangeCam* changeCam = (CChangeCam*)e->obj;
	CCamera::GetInstance()->SetSceneStart(Vec2(changeCam->GetPosition().x - 125, changeCam->GetCamY()));
	changeCam->Delete();
}

void CMarco::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* portal = (CPortal*)e->obj;
	CGame::GetInstance()->SetNextScene(portal->GetScene_id());
}

RECT CMarco::getBoundingBox()
{
	RECT r;
	if (body == Body_states::sitting)
	{
		r.left = this->Obj_Position.x;
		r.right = this->Obj_Position.x + this->Obj_Size.x;
		r.top = this->Obj_Position.y - this->Obj_Size.y;
		r.bottom = this->Obj_Position.y - this->Obj_Size.y / 2;
		return r;
	}
	r.left = this->Obj_Position.x;
	r.right = this->Obj_Position.x + this->Obj_Size.x;
	r.top = this->Obj_Position.y - this->Obj_Size.y;
	r.bottom = this->Obj_Position.y;
	return r;
}

RECT CMarco::getActiveRange()
{
	RECT r;
	if (body == Body_states::sitting)
	{
		r.left = this->Obj_Position.x;
		r.right = this->Obj_Position.x + this->Obj_Size.x;
		r.top = this->Obj_Position.y - this->Obj_Size.y;
		r.bottom = this->Obj_Position.y - this->Obj_Size.y / 2;
		return r;
	}
	r.left = this->Obj_Position.x;
	r.right = this->Obj_Position.x + this->Obj_Size.x;
	r.top = this->Obj_Position.y - this->Obj_Size.y;
	r.bottom = this->Obj_Position.y;
	return r;
}

bool CMarco::GetIsInWater()
{
	return isInWater;
}

CMarco* CMarco::getInstance()
{
	return _Instance;
}

