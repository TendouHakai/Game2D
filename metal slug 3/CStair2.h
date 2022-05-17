#pragma once
#include "GameObject.h"
class CStair2 :
    public CGameObject
{
public:
    CStair2() : CGameObject() {}
    CStair2(Vec2 position, Vec2 size) : CGameObject(position) { Obj_speed.x = Obj_speed.y = 0; Obj_Size = size; this->type = GAME_MAP_OBJECT; }

    void Update(DWORD dt, vector<LPCGameObject>* coObjects){}
    void Render();
    void DrawAnimation();
    int IsBlocking() { return 0; }
};

