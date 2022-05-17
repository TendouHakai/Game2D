#include "CChowmeinBuble.h"
#include "CGunBullet.h"

void CChowmeinBuble::Update(DWORD dt, vector<LPCGameObject>* coObjects)
{
	if (HealBar == 0)
		this->Delete();
	if (DamageTime != 0 && DamageTime + 50 < GetTickCount64())
	{
		this->Delete();
		CMarco::getInstance()->GotAttacked();
	}
	if (abs(Obj_speed.y) > 0.02f)
		BubleAcceleration = -BubleAcceleration;
	Obj_speed.y += BubleAcceleration;
	Obj_Position += Obj_speed * dt;
	process(dt, coObjects);
}

void CChowmeinBuble::Render()
{
	DrawAnimation();
}

void CChowmeinBuble::DrawAnimation()
{
	CAnimationManager::GetInstance()->Get("Chowmein_Buble").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
}

void CChowmeinBuble::OnNoCollision(DWORD dt)
{
}

void CChowmeinBuble::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMarco*>(e->obj))
	{
		OnCollisionwithMarco(e);
	}
	else if (dynamic_cast<CGunBullet*>(e->obj))
	{
		OnCollisionwithMarcoBullet(e);
	}

}

void CChowmeinBuble::OnCollisionwithMarco(LPCOLLISIONEVENT e)
{
	if (DamageTime != 0)
		DamageTime = GetTickCount64();
	//DebugOut(L"Oncollision with Marco");
}

void CChowmeinBuble::OnCollisionwithMarcoBullet(LPCOLLISIONEVENT e)
{
	e->obj->GotAttacked();
	this->GotAttacked();
}
