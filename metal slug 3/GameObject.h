#pragma once
#include "d3d9.h"
#include "d3dx9.h"
#include <string>
#include "Transform.h"
#include "CAnimationManager.h"
#include "CCamera.h"
#include "Debug.h"

using namespace std;

class CGameObject
{
protected:
	Vec2 Obj_Position;
	Vec2 Obj_Size;
	Vec2 Obj_speed;
	bool flag = true;
	
	float dt;
    	float dx;	// dx = vx*dt
    	float dy;	// dy = vy*dt
	
	int nx;

	string state;
public:
	virtual void SetPosition(Vec2 Position) { this->Obj_Position = Position; }
	virtual void SetSpeed(Vec2 Speed) { this->Obj_speed = Speed; }

	virtual void SetState(string state) { this->state = state; }
	virtual string GetState() { return this->state; }

	CGameObject();
	CGameObject(Vec2 Position) { this->Obj_Position = Position;}

	virtual void Update(DWORD dt) = 0;
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

	~CGameObject() {};
};
typedef CGameObject* LPCGameObject;


