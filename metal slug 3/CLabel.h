#pragma once
#include "GameObject.h"
class CLabel :
    public CGameObject
{
    CLabel() : CGameObject() {};
    CLabel(Vec2 position) : CGameObject(position) { Obj_speed.x = Obj_speed.y = 0; Obj_Size = Vec2(32, 32); };

    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();
};

