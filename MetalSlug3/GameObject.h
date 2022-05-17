#pragma once
#include "d3d9.h"
#include "d3dx9.h"
#include <string>
#include <algorithm>
#include "Transform.h"
#include "CAnimationManager.h"
#include "CCamera.h"
#include "Debug.h"
#include "MS3GameInfo.h"

using namespace std;
class CGameObject;
typedef CGameObject* LPCGameObject;
struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPCGameObject obj;			// the target object

	float t, nx, ny;

	float dx, dy;				// *RELATIVE* movement distance between this object and obj
	bool isDeleted;

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0,
		LPCGameObject obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
		this->isDeleted = false;
	}

	int WasCollided()
	{
		if (t >= 0.0f && t <= 1.0f)
			return true;
		return false;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};

class CGameObject
{
protected:
	int HealBar = 1;
	int type;
	DWORD DeadTime;

	Vec2 Obj_Position;
	Vec2 Obj_Size;
	Vec2 Obj_speed;

	bool IsDead = false;
	bool isLeftSize = false;
	bool ischangingstates = false;
	bool isActivated = false;
	DWORD totalActivateTime = 0;

	int nx;
	DWORD LastFrameTime = 0;
	DWORD CurrentFrameTime = 0;

	DWORD AnimationTime = 0;

	bool isDeleted;

public:
	virtual void SetPosition(Vec2 Position) { this->Obj_Position = Position; }
	virtual void SetSpeed(Vec2 Speed) { this->Obj_speed = Speed; }
	virtual Vec2 getSpeed() { return this->Obj_speed; }

	CGameObject();
	CGameObject(Vec2 Position) { this->Obj_Position = Position; this->isDeleted = false; }

	virtual void Update(DWORD dt, vector<LPCGameObject>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void Delete() { isDeleted = true; }
	bool IsDeleted() { return isDeleted; }
	bool isDead() { return IsDead; }

	virtual Vec2 GetPosition() { return Obj_Position; }

	virtual int GetType() { return this->type; }

	virtual void DrawAnimation() = 0;

	virtual RECT getBoundingBox() {
		RECT r;
		r.left = this->Obj_Position.x;
		r.right = this->Obj_Position.x + this->Obj_Size.x;
		r.top = this->Obj_Position.y - this->Obj_Size.y;
		r.bottom = this->Obj_Position.y;
		return r;
	};
	virtual RECT getActiveRange()
	{
		RECT r;
		r.left = this->Obj_Position.x;
		r.right = this->Obj_Position.x + this->Obj_Size.x;
		r.top = this->Obj_Position.y - this->Obj_Size.y;
		r.bottom = this->Obj_Position.y;
		return r;
	}
	// hàm xữ lý va chạm 
	void process(DWORD dt, vector<LPCGameObject>* coObjects);
	// các hàm hổ trợ xử lý va chạm 
	virtual int IsCollidable() { return 0; }; // hàm kiểm tra xem đối tượng có cần xét va chạm hay không? ví dụ ở trạng thái chết.
	virtual void OnNoCollision(DWORD dt) {}; // hàm xữ lý khi không có va chạm
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {}; // hàm xữ lý khi va chạm
	virtual int IsBlocking() { return 1; } // kiểm tra xem đối tượng có thể đi xuyên qua hay không?
	// các hàm kiểm tra va chạm
	static void SweptAABB(
		RECT movingObj,
		float dx,
		float dy,
		RECT staticObj,
		float& t,
		float& nx,
		float& ny);

	LPCOLLISIONEVENT SweptAABBEx(DWORD dt, LPCGameObject coO, bool isGetActiveRange = false);
	void CalcPotentialCollisions(
		DWORD dt, vector<LPCGameObject>* objDests, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		LPCOLLISIONEVENT& colX,
		LPCOLLISIONEVENT& colY,
		int filterBlock = 1,		// 1 = only filter block collisions, 0 = filter all collisions 
		int filterX = 1,			// 1 = process events on X-axis, 0 = skip events on X 
		int filterY = 1);
	bool isColliding(RECT thisRect, RECT otherRect);

	~CGameObject() {};
	void GotAttacked() { HealBar -= 1; }
};
typedef CGameObject* LPCGameObject;
