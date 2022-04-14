#pragma once
#include"GameObject.h"

enum class CHelper_1_state
{
    catched,
    drop_items,
    release,
    walk
};
class CHelper_1 : 
	CGameObject
{
    CHelper_1_state state = CHelper_1_state::catched;
public:
    CHelper_1() : CGameObject() {};
    CHelper_1(Vec2 position) : CGameObject(position) { Obj_speed.x = Obj_speed.y = 0; Obj_Size = Vec2(33, 38); };

    void Update(DWORD dt);
    void Render();
    void DrawAnimation();

};

