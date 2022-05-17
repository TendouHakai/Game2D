#pragma once
#include"GameObject.h"
#include "CMarco.h"
class CChowmeinBuble :
    public CGameObject
{
    float BubleAcceleration = 0.001f;
    float DamageTime = 0;
public:
    CChowmeinBuble() : CGameObject() {};
    CChowmeinBuble(Vec2 position, Vec2 speed) : CGameObject(position) { Obj_Position = position; Obj_speed = speed; Obj_Size = Vec2(16 * 2, 16 * 2); };

    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();

    int IsCollidable() { return 1; }
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);

    void OnCollisionwithMarco(LPCOLLISIONEVENT e);
    void OnCollisionwithMarcoBullet(LPCOLLISIONEVENT e);

};

