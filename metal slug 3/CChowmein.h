#pragma once

#include "GameObject.h"
#include "CMarco.h"
#include "CChowmeinBuble.h"

class CChowmein :
    public CGameObject
{
    CChowmein_States states = CChowmein_States::IDLE;

    Vec2 direct;
    Vec2 positionStair;
    int stairType;
    bool IsOnStair;
    bool IsCollisionStair;
    bool IsOnStair2;
    float yStair2;

    float acceleration = 0.001f;

    DWORD AttackTime = 0;
    static int bublecount;
public:
    CChowmein() : CGameObject() {};
    CChowmein(Vec2 position) : CGameObject(position) {
        Obj_speed.x = 0;
        Obj_speed.y = 0;
        this->states = CChowmein_States::IDLE;
        Obj_Size = Vec2(50 * 2, 45 * 2);
        direct = Vec2(0, 0);
        this->IsOnStair = false;
        this->IsOnStair2 = false;
        stairType = 0;
        this->IsCollisionStair = false;
        HealBar = 3;
    };
    CChowmein(Vec2 position, Vec2 direct, int StairType, Vec2 StairPosition) : CGameObject(position)
    {
        Obj_speed.x = 0;
        Obj_speed.y = 0;
        this->states = CChowmein_States::IDLE;
        Obj_Size = Vec2(50 * 2, 45 * 2);
        this->IsOnStair = true;
        this->IsOnStair2 = false;
        SetDirectOnStair(direct, StairType, StairPosition);
        this->IsCollisionStair = false;
        HealBar = 3;
    }

    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();

    int IsCollidable() { return 1; }
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);

    void OnCollisionWithMarco(LPCOLLISIONEVENT e);
    void OnCollisionWithStair(LPCOLLISIONEVENT e);
    void OnCollisionWithStair2(LPCOLLISIONEVENT e);

    RECT getActiveRange();
    void SetDirectOnStair(Vec2 direct, int stairType, Vec2 positionStair);

    int IsBlocking() { return 0; }
};
