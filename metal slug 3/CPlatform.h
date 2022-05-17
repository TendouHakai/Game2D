#pragma once
#include "GameObject.h"
class CPlatform :
    public CGameObject
{
public:
    CPlatform() :CGameObject() {}
    CPlatform(Vec2 position, Vec2 size) : CGameObject(position) { Obj_speed.x = Obj_speed.y = 0; Obj_Size = size; this->type = GAME_MAP_OBJECT; }

    void Update(DWORD dt, vector<LPCGameObject>* coObjects) {}
    void Render() {}
    void DrawAnimation() {}
};

