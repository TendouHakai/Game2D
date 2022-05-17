#pragma once
#include"GameObject.h"


class CHelper_1 : 
	CGameObject
{
    CHelper_1_state state = CHelper_1_state::catched;
public:
    CHelper_1() : CGameObject() {};
    CHelper_1(Vec2 position) : CGameObject(position) { Obj_speed.x = Obj_speed.y = 0; Obj_Size = Vec2(40*2, 45*2); };

    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();

};

