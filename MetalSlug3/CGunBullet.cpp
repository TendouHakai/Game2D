#include "CGunBullet.h"
#include "Flying_Killer.h"
#include "CLocust.h"
#include "COhumein_Conga.h"

void CGunBullet::Update(DWORD dt, vector<LPCGameObject>* coObjects)
{
	Obj_Position += Obj_speed*dt;
	process(dt, coObjects);
	if (this->HealBar == 0)
		this->Delete();

}

void CGunBullet::Render()
{
	DrawAnimation();
}

void CGunBullet::DrawAnimation()
{
	CAnimationManager::GetInstance()->Get("bullet").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
}

void CGunBullet::OnNoCollision(DWORD dt)
{
}

void CGunBullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
	// xữ lý va chạm với các đối tượng không BLOCK
	if (dynamic_cast<CChowmein*>(e->obj) || dynamic_cast<Flying_Killer*>(e->obj) || dynamic_cast<CLocust*>(e->obj) || dynamic_cast<COhumein_Conga*>(e->obj))
	{
		OnCollisionwithEnemies(e);
	}
}

void CGunBullet::OnCollisionwithEnemies(LPCOLLISIONEVENT e)
{

	if (e->obj->isDead())
		return;
	e->obj->GotAttacked();
	DebugOut(L"Oncollision with chowmein");
	//this->GotAttacked();
	this->Delete();
}
