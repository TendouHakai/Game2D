#pragma once
#include"GameObject.h"
#include "CChowmein.h"
class CGunBullet :
    public CGameObject
{
public:
    CGunBullet() : CGameObject() {};
    CGunBullet(Vec2 position, Vec2 speed) : CGameObject(position) { Obj_Position = position; Obj_speed = speed; Obj_Size = Vec2(12, 12); };

    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();

    int IsCollidable() { return 1; }
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
    int IsBlocking() { return 0; }

    void OnCollisionwithEnemies(LPCOLLISIONEVENT e);
};

