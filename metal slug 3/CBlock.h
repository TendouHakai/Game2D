#pragma once
#include "GameObject.h"
class CBlock :
    public CGameObject
{
public:
    CBlock() : CGameObject() {};
    CBlock(Vec2 position) : CGameObject(position) { Obj_speed.x = Obj_speed.y = 0;Obj_Size = Vec2(10, 10); };

    void Update(DWORD dt);
    void Render();
    void DrawAnimation();
};

