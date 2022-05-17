#pragma once
#include "GameObject.h"
class CGameMap :
    public CGameObject
{
public:
	CGameMap() : CGameObject() {};
	CGameMap(Vec2 position) : CGameObject(position) {
		Obj_speed.x = Obj_speed.y = 0;
		Obj_Size = Vec2(572, 40);
		this->type = GAME_MAP_OBJECT;
	};
	void Update(DWORD dt, vector<LPCGameObject>* coObjects);
	void Render();
	void DrawAnimation();
	int IsBlocking() { return 1; }
};

