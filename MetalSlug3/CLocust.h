#pragma once
#include "GameObject.h" 
#include "CMarco.h"


class CLocust :
    public CGameObject
{
    Locust_states states = Locust_states::flying;

    float accelerationX = 0.003f;
    float accelerationY = 0.001f;

    DWORD AttackTime = 0;
    Vec2 LockTarget;
    Vec2 attackSpeed;
    bool isEndAttack = false;
public:
    CLocust() : CGameObject() {};
    CLocust(Vec2 position) : CGameObject(position)
    {
        Obj_speed.x = Obj_speed.y = 0;
        Obj_Size = Vec2(72 * 2, 55 * 2);
        HealBar = 3;
    };

    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();
    int IsBlocking() { return 0; }

    void OnCollisionWithMarco();

    RECT getActiveRange();
};

