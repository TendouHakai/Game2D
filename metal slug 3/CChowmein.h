#pragma once

#include "GameObject.h"

enum class CChowmein_States {
    IDLE,
    Walk,
    MeleeAttack,
    RangeAttack,
    Dead
};

class CChowmein :
    public CGameObject
{
    CChowmein_States states = CChowmein_States::IDLE;
public:
    CChowmein() : CGameObject() {};
    CChowmein(Vec2 position) : CGameObject(position) { Obj_speed.x = Obj_speed.y = 0; this->states = CChowmein_States::IDLE; Obj_Size = Vec2(50, 45); };

    void Update(DWORD dt);
    void Render();
    void DrawAnimation();

    void SetState(CChowmein_States state);
};
