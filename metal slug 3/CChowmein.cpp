#include "CChowmein.h"
#include "Cplayscene.h"

int CChowmein::bublecount = 0;

void CChowmein::Update(DWORD dt, vector<LPCGameObject>* coObjects)
{
	if (HealBar == 0 && IsDead == false)
	{
		this->IsDead = true;
		DeadTime = GetTickCount64();
		ischangingstates = true;
	}
	if (IsDead == true)
	{
		if (DeadTime + 110 * 19 < GetTickCount64())
		{
			this->Delete();
		}
		return;
	}

	this->IsCollisionStair = false;
	this->Obj_speed.y -= Marco_Speed_Y;

	Vec2 speed = Obj_speed;


	isLeftSize = CMarco::getInstance()->GetPosition().x > Obj_Position.x ? true : false;

	process(dt, coObjects);
	if (IsOnStair)
	{
		float y = (direct.y * (Obj_Position.x - positionStair.x) / direct.x) + positionStair.y - 200;
		if (Obj_Position.y - Obj_Size.y < y)
		{
			Obj_Position.y = y + Obj_Size.y;
			Obj_speed.y = 0;
		}
	}
	if (IsCollisionStair && Obj_Position.y <= positionStair.y - 200 + Obj_Size.y)
	{
		Obj_Position.y = positionStair.y - 200 + Obj_Size.y;
		Obj_speed.y = 0;
	}
	if (states == CChowmein_States::Walk)
	{
		if (abs(speed.x) >= 0.2f)
		{
			acceleration = -acceleration;
		}
		speed.x = speed.x - acceleration;
	}
	else
	{
		speed = Vec2(0, 0);
	}
	if (!isActivated)
	{

		CCollisionEvent* isActivate = this->SweptAABBEx(dt, CMarco::getInstance(), true);

		if (isActivate->t > 0)
		{
			DebugOut(L"Marco go into Range\n");
			this->states = CChowmein_States::Walk;
			this->isActivated = true;
			AttackTime = GetTickCount64() - 400;
			ischangingstates = true;
		}
		isActivate = this->SweptAABBEx(dt, CMarco::getInstance(), false);

		if (isActivate->t > 0)
		{
			DebugOut(L"Marco go into meleeRange\n");
			this->states = CChowmein_States::MeleeAttack;
			this->isActivated = true;
			AttackTime = GetTickCount64() - 400;
			ischangingstates = true;
		}

	}
	if (isActivated)
	{
		CCollisionEvent* isActivate = this->SweptAABBEx(dt, CMarco::getInstance(), true);

		isActivate = this->SweptAABBEx(dt, CMarco::getInstance(), true);

		if (isActivate->t > 0)
		{
			ischangingstates = true;
			this->states = CChowmein_States::RangeAttack;
			AttackTime = GetTickCount64() - 400;
		}


		if (this->states == CChowmein_States::RangeAttack)
		{
			if (GetTickCount64() > AttackTime + 13 * 100)
			{
				float BubleSpeed = CChowmein_Buble_Speed;
				AttackTime = GetTickCount64();
				LPCGameObject obj;
				if (isLeftSize)
					obj = new CChowmeinBuble(Obj_Position + Vec2(0, -15), Vec2(BubleSpeed, 0));
				else
					obj = new CChowmeinBuble(Obj_Position + Vec2(0, -15), Vec2(-BubleSpeed, 0));
				string id = "12000" + to_string(bublecount);
				CGame::GetInstance()->AddObjectsToCurrrentScene(stoi(id), obj);
				bublecount++;
				this->states = CChowmein_States::Walk;
				isActivated = false;
				ischangingstates = true;

			}
		}
		if (this->states == CChowmein_States::MeleeAttack)
		{
			if (GetTickCount64() > AttackTime + 13 * 100)
			{
				float BubleSpeed = CChowmein_Buble_Speed;
				AttackTime = GetTickCount64();
				LPCGameObject obj;
				if (isLeftSize)
					obj = new CChowmeinBuble(Obj_Position + Vec2(0, -15), Vec2(BubleSpeed, 0));
				else
					obj = new CChowmeinBuble(Obj_Position + Vec2(0, -15), Vec2(-BubleSpeed, 0));
				this->states = CChowmein_States::Walk;
				isActivated = false;
				ischangingstates = true;
				if (isColliding(this->getBoundingBox(), CMarco::getInstance()->getBoundingBox()))
				{
					CMarco::getInstance()->GotAttacked();
					DebugOut(L"Marco is dead");
				}
			}
		}
	}
	Obj_speed.x = speed.x;
	//DebugOut(L" position : %f,%f \n",Obj_Position.x,Obj_Position.y);
}

void CChowmein::Render()
{
	DrawAnimation();
	DebugOut(L"Chowmein position(%f, %f)\n", Obj_Position.x, Obj_Position.y);
}

void CChowmein::DrawAnimation()
{
	CurrentFrameTime = GetTickCount64();

	if (ischangingstates == true)
	{
		LastFrameTime = CurrentFrameTime;
		ischangingstates = false;
	}

	if (IsDead)
	{
		CAnimationManager::GetInstance()->Get("ani_chowmein_dead").get()->Render(Obj_Position - Vec2(0, 90), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 1), CurrentFrameTime - LastFrameTime);
		return;
	}

	switch (states)
	{
	case CChowmein_States::IDLE:
		CAnimationManager::GetInstance()->Get("ani_chowmein_IDLE").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size + Vec2(20, 0), Vec2(0, 0), CurrentFrameTime - LastFrameTime);
		break;
	case CChowmein_States::Walk:
		CAnimationManager::GetInstance()->Get("ani_chowmein_walk").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size + Vec2(20, 0), Vec2(0, 0), CurrentFrameTime - LastFrameTime);
		break;
	case CChowmein_States::MeleeAttack:
		CAnimationManager::GetInstance()->Get("ani_chowmein_melee_attack").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size + Vec2(20, 0), Vec2(0, 0), CurrentFrameTime - LastFrameTime);
		break;
	case CChowmein_States::RangeAttack:
		CAnimationManager::GetInstance()->Get("ani_chowmein_range_attack").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size + Vec2(20, 0), Vec2(0, 0), CurrentFrameTime - LastFrameTime);
		break;
	default:
		break;
	}
}

void CChowmein::OnNoCollision(DWORD dt)
{
	Obj_Position += Obj_speed;
}

void CChowmein::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		this->Obj_speed.y = 0;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{

	}

	// xữ lý va chạm với các đối tượng không BLOCK
	if (dynamic_cast<CStair*>(e->obj))
		OnCollisionWithStair(e);
	else if (dynamic_cast<CMarco*>(e->obj))
	{
		OnCollisionWithMarco(e);
	}

}

void CChowmein::OnCollisionWithMarco(LPCOLLISIONEVENT e)
{
	//DebugOut(L"on collision with marco\n");
	isActivated = true;
	totalActivateTime = GetTickCount64();
}

void CChowmein::OnCollisionWithStair(LPCOLLISIONEVENT e)
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

RECT CChowmein::getActiveRange()
{
	int range = 250;
	if (isActivated)
		range = 150;
	RECT r;
	r.left = this->Obj_Position.x - range;
	r.right = this->Obj_Position.x + this->Obj_Size.x + range;
	r.top = this->Obj_Position.y - this->Obj_Size.y - range;
	r.bottom = this->Obj_Position.y + range;
	return r;
}

void CChowmein::SetDirectOnStair(Vec2 direct, int stairType, Vec2 positionStair)
{
	this->direct = direct;
	this->stairType = stairType;
	this->positionStair = positionStair;
}