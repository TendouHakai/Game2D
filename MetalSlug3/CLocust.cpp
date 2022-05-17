#include "CLocust.h"

void CLocust::Update(DWORD dt, vector<LPCGameObject>* coObjects)
{
	isLeftSize = CMarco::getInstance()->GetPosition().x > Obj_Position.x ? true : false;

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

	if (!isActivated)
	{
		CCollisionEvent* isActivate = this->SweptAABBEx(dt, CMarco::getInstance(), true);
		if (isActivate->t > 0)
		{
			DebugOut(L"Marco go into Rangeeeeeeeeeeeeeeeeeeeeeeeeee\n");
			this->isActivated = true;
			AttackTime = GetTickCount64() - 400;
			ischangingstates = true;
			states = Locust_states::flying;
			ischangingstates = true;
		}
	}
	else
	{
		if (AttackTime + 10000 > GetTickCount64())
		{
			if (abs(Obj_speed.x) > 2)
			{
				accelerationX = -accelerationX;
			}
			if (abs(Obj_speed.y) > 1)
			{
				if (Obj_speed.y > 1)
					Obj_speed.y = 1.000001;
				accelerationY = -accelerationY;
			}
			LockTarget = CMarco::getInstance()->GetPosition();
			attackSpeed = (LockTarget - Obj_Position) / 70;
			Obj_speed = Obj_speed + Vec2(accelerationX * dt, accelerationY * dt);
		}
		else if (!isEndAttack)
		{
			this->states = Locust_states::attack;
			Obj_speed = attackSpeed;
			if (Obj_Position.y < LockTarget.y - 50)
			{
				isEndAttack = true;
				this->states = Locust_states::flying;
				ischangingstates = true;
			}
			if (isColliding(this->getBoundingBox(), CMarco::getInstance()->getBoundingBox()))
			{
				if (!CMarco::getInstance()->isDead())
					CMarco::getInstance()->GotAttacked();
			}

		}
		else if (Obj_Position.y < 500)
		{
			Obj_speed.y = (500 - LockTarget.y) / 50;
			Obj_speed.x = 0;
		}
		else
		{
			AttackTime = GetTickCount64() + 5000;
			Obj_speed = Vec2(0, 0);
			isEndAttack = false;
		}
	}
	Obj_Position = Obj_Position + Obj_speed;
}

void CLocust::Render()
{
	DrawAnimation();
}

void CLocust::DrawAnimation()
{
	CurrentFrameTime = GetTickCount64();

	if (ischangingstates == true)
	{
		LastFrameTime = CurrentFrameTime;
		ischangingstates = false;
	}

	switch (states)
	{
	case Locust_states::flying:
		CAnimationManager::GetInstance()->Get("ani_Locust_flying").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0), CurrentFrameTime - LastFrameTime);
		break;
	case Locust_states::attack:
		CAnimationManager::GetInstance()->Get("ani_Locust_attack").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0), CurrentFrameTime - LastFrameTime);
		break;
	case Locust_states::preattack:
		CAnimationManager::GetInstance()->Get("ani_Locust_preattack").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0), CurrentFrameTime - LastFrameTime);
		break;
	case Locust_states::turn:
		CAnimationManager::GetInstance()->Get("ani_Locust_turn").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0), CurrentFrameTime - LastFrameTime);
		break;
	default:
		break;
	}
}

void CLocust::OnCollisionWithMarco()
{

}

RECT CLocust::getActiveRange()
{
	int range = 500;
	RECT r;
	r.left = this->Obj_Position.x - range;
	r.top = this->Obj_Position.y - range;
	r.right = this->Obj_Position.x + this->Obj_Size.x + range;
	r.bottom = this->Obj_Position.y + this->Obj_Size.y + range;
	return r;
}

