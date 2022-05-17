#include "COhumein_Conga.h"
#include "Cplayscene.h"


void COhumein_Conga::Update(DWORD dt, vector<LPCGameObject>* coObjects)
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

	if (states == COhumein_Conga_states::walk)
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
			this->isActivated = true;
			states = COhumein_Conga_states::walk;
			AttackTime = GetTickCount64() - 400;
			ischangingstates = true;
		}
		isActivate = this->SweptAABBEx(dt, CMarco::getInstance(), false);
	}
	if (isActivated)
	{
		CCollisionEvent* isActivate = this->SweptAABBEx(dt, CMarco::getInstance(), true);

		if (isActivate->t > 0)
		{
			DebugOut(L"Marco go into Range\n");
			this->isActivated = true;
			states = COhumein_Conga_states::Melee_Attack;
			AttackTime = GetTickCount64();
			ischangingstates = true;
		}

		if (this->states == COhumein_Conga_states::Melee_Attack)
		{
			if (GetTickCount64() > AttackTime + 13 * 100)
			{
				LPCGameObject obj;
				isActivated = false;
				ischangingstates = true;
				if (isColliding(this->getBoundingBox(), CMarco::getInstance()->getBoundingBox()))
				{
					CMarco::getInstance()->GotAttacked();
					DebugOut(L"Marco is dead");
				}
			}
			else if (GetTickCount64() > AttackTime + 22 * 100)
			{
				AttackTime = GetTickCount64();
				this->states = COhumein_Conga_states::walk;
			}
		}


	}
	Obj_speed.x = speed.x;
	//DebugOut(L" position : %f,%f \n",Obj_Position.x,Obj_Position.y);
}

void COhumein_Conga::Render()
{
	DrawAnimation();
}

void COhumein_Conga::DrawAnimation()
{
	CurrentFrameTime = GetTickCount64();

	if (ischangingstates == true)
	{
		LastFrameTime = CurrentFrameTime;
		ischangingstates = false;
	}
	if (IsDead)
	{
		CAnimationManager::GetInstance()->Get("Ohumein_Conga_dead").get()->Render(Obj_Position - Vec2(0, 80*2), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 1), CurrentFrameTime - LastFrameTime);
		return;
	}
	switch (states)
	{
	case COhumein_Conga_states::walk:
		CAnimationManager::GetInstance()->Get("Ohumein_Conga_walk").get()->Render(Obj_Position - Vec2(0, 80 * 2), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 1), CurrentFrameTime - LastFrameTime);
		break;
	case COhumein_Conga_states::IDLE:
		CAnimationManager::GetInstance()->Get("Ohumein_Conga_IDLE").get()->Render(Obj_Position - Vec2(0, 80 * 2), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 1), CurrentFrameTime - LastFrameTime);
		break;
	case COhumein_Conga_states::Melee_Attack:
		CAnimationManager::GetInstance()->Get("Ohumein_Conga_Melee_attack").get()->Render(Obj_Position - Vec2(0, 80 * 2), D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 1), CurrentFrameTime - LastFrameTime);
		break;
	default:
		break;
	}
}

void COhumein_Conga::OnNoCollision(DWORD dt)
{
	Obj_Position += Obj_speed;
}

void COhumein_Conga::OnCollisionWith(LPCOLLISIONEVENT e)
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

void COhumein_Conga::OnCollisionWithMarco(LPCOLLISIONEVENT e)
{
	//DebugOut(L"on collision with marco\n");
	isActivated = true;
	totalActivateTime = GetTickCount64();
}

void COhumein_Conga::OnCollisionWithStair(LPCOLLISIONEVENT e)
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

RECT COhumein_Conga::getActiveRange()
{
	int range = 500;
	RECT r;
	r.left = this->Obj_Position.x - range;
	r.right = this->Obj_Position.x + this->Obj_Size.x + range;
	r.top = this->Obj_Position.y - this->Obj_Size.y - range;
	r.bottom = this->Obj_Position.y + range;
	return r;
}

void COhumein_Conga::SetDirectOnStair(Vec2 direct, int stairType, Vec2 positionStair)
{
	this->direct = direct;
	this->stairType = stairType;
	this->positionStair = positionStair;
}
