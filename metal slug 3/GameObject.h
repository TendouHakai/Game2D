#pragma once
#include "d3d9.h"
#include "d3dx9.h"
#include <string>
#include <algorithm>
#include "Transform.h"
#include "CAnimationManager.h"
#include "CCamera.h"
#include "Debug.h"

using namespace std;
class CGameObject;
typedef CGameObject* LPCGameObject;
struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPCGameObject obj;
	float t, nx, ny;
	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPCGameObject obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};

class CGameObject
{
protected:
	int type;
	Vec2 Obj_Position;
	Vec2 Obj_Size;
	Vec2 Obj_speed;
	bool flag = true;
	int nx;

	float dt;
	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	string state;
public:
	virtual void SetPosition(Vec2 Position) { this->Obj_Position = Position; }
	virtual void SetSpeed(Vec2 Speed) { this->Obj_speed = Speed; }
	virtual Vec2 getSpeed() { return this->Obj_speed; }

	virtual void SetState(string state) { this->state = state; }
	virtual string GetState() { return this->state; }

	CGameObject();
	CGameObject(Vec2 Position) { this->Obj_Position = Position;}

	virtual void Update(DWORD dt, vector<LPCGameObject>* coObjects = NULL);
	virtual void Render() = 0;

	virtual Vec2 GetPosition() { return Obj_Position; }

	virtual void DrawAnimation() = 0;

	virtual RECT getBoundingBox() {
		RECT r;
		r.left = this->Obj_Position.x;
		r.top = this->Obj_Position.y - this->Obj_Size.y;
		r.right = this->Obj_Position.x + this->Obj_Size.x;
		r.bottom = this->Obj_Position.y;
		return r;
	};

	static void SweptAABB(
		RECT movingObj,
		float dx,
		float dy,
		RECT staticObj,
		float& t,
		float& nx,
		float& ny);

	LPCOLLISIONEVENT SweptAABBEx(LPCGameObject coO);
	void CalcPotentialCollisions(
		vector<LPCGameObject>* coObjects,
		vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);
	bool isColliding(RECT thisRect, RECT otherRect);

	~CGameObject() {};
};
typedef CGameObject* LPCGameObject;


