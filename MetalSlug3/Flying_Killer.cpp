#include "Flying_Killer.h"
#include "CMarco.h"

void Flying_Killer::Update(DWORD dt, vector<LPCGameObject>* coObjects)
{
	if (HealBar == 0 && IsDead == false)
	{
		ischangingstates = true;
		this->IsDead = true;
		DeadTime = GetTickCount64();
	}
	if (IsDead == true)
	{
		this->Obj_Position += isLeftSize ? Vec2(-3, -0.5) : Vec2(3, -0.5);
		if (DeadTime + 80 * 14 < GetTickCount64())
		{
			this->Delete();
		}
		return;
	}

	process(dt, coObjects);
	if (!isActivated)
	{
		CCollisionEvent* isActivate = this->SweptAABBEx(dt, CMarco::getInstance(), true);
		if (isActivate->t > 0)
		{
			isActivated = true;
			AttackTime = GetTickCount64();
			DebugOut(L"Flying killer activating");
			isLeftSize = CMarco::getInstance()->GetPosition().x > Obj_Position.x ? true : false;
			Obj_speed.x = -Flying_killer_speed;
			if (isLeftSize)
				Obj_speed.x = Flying_killer_speed;
			Obj_speed.y = Flying_killer_jump;

		}
	}
	if (isActivated)
	{
		if (AttackTime + 1000 < GetTickCount64())
		{
			Obj_Position += Vec2(Obj_speed.x, 0) * dt;
			states = Flying_killer_states::attack;
		}
		else
			Obj_Position += Vec2(0, Obj_speed.y) * dt;
	}
}

void Flying_Killer::Render()
{
	if (isActivated)
	{
		DrawAnimation();
	}
}
void Flying_Killer::DrawAnimation()
{
	CurrentFrameTime = GetTickCount64();

	if (ischangingstates == true)
	{
		LastFrameTime = CurrentFrameTime;
		ischangingstates = false;
	}

	if (IsDead)
	{
		CAnimationManager::GetInstance()->Get("Flying_killer_dead").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0), CurrentFrameTime - LastFrameTime);
		return;
	}
	switch (states)
	{
	case Flying_killer_states::jump:
		CAnimationManager::GetInstance()->Get("ani_Flying_killer_jump").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0), CurrentFrameTime - LastFrameTime);
		break;
	case Flying_killer_states::attack:
		CAnimationManager::GetInstance()->Get("ani_Flying_killer_attack").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0), CurrentFrameTime - LastFrameTime);
		break;
	default:
		break;
	}
}

void Flying_Killer::OnNoCollision(DWORD dt)
{
}

void Flying_Killer::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMarco*>(e->obj))
	{
		OnCollisionWithMarco(e);
	}
}

void Flying_Killer::OnCollisionWithMarco(LPCOLLISIONEVENT e)
{
	e->obj->GotAttacked();
}

RECT Flying_Killer::getActiveRange()
{
	int range = 100;
	RECT r;
	r.left = this->Obj_Position.x - range;
	r.right = this->Obj_Position.x + this->Obj_Size.x + range;
	r.top = this->Obj_Position.y - this->Obj_Size.y - range;
	r.bottom = this->Obj_Position.y + range;
	return r;
}
