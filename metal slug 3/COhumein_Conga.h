#pragma once
#include "GameObject.h"
class COhumein_Conga :
    public CGameObject
{
    COhumein_Conga_states states = COhumein_Conga_states::IDLE;

    Vec2 direct;
    Vec2 positionStair;
    int stairType;
    bool IsOnStair;
    bool IsCollisionStair;

    float acceleration = 0.001f;

    DWORD AttackTime = 0;
public:
    COhumein_Conga() : CGameObject() {};
    COhumein_Conga(Vec2 position) : CGameObject(position) {
        Obj_speed.x = 0;
        Obj_speed.y = 0;
        Obj_Size = Vec2(108 * 2, 80 * 2);
        direct = Vec2(0, 0);
        this->IsOnStair = false;
        stairType = 0;
        this->IsCollisionStair = false;
        HealBar = 10;
    };

    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();

    int IsCollidable() { return 1; }
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);

    void OnCollisionWithMarco(LPCOLLISIONEVENT e);
    void OnCollisionWithStair(LPCOLLISIONEVENT e);

    RECT getActiveRange();
    void SetDirectOnStair(Vec2 direct, int stairType, Vec2 positionStair);

    int IsBlocking() { return 0; }

};

