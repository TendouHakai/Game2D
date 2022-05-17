#pragma once
#include "GameObject.h"


class Flying_Killer :
    public CGameObject
{
    Flying_killer_states states = Flying_killer_states::jump;
    DWORD AttackTime = 0;
public:
    Flying_Killer() : CGameObject() {};
    Flying_Killer(Vec2 position) : CGameObject(position)
    {
        Obj_speed.y = 0;
        Obj_speed.x = 0;
        Obj_Size = Vec2(36 * 2, 26 * 2);
        HealBar = 1;
    };

    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();

    int IsCollidable() { return 1; }
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);

    void OnCollisionWithMarco(LPCOLLISIONEVENT e);
    RECT getActiveRange();

};

