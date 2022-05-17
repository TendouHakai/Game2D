#pragma once
#include "GameObject.h"
class CBlock :
    public CGameObject
{
public:
    CBlock() : CGameObject() {};
    CBlock(Vec2 position) : CGameObject(position) { Obj_speed.x = Obj_speed.y = 0; Obj_Size = Vec2(32, 32); this->type = GAME_MAP_OBJECT; };


    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();
};

