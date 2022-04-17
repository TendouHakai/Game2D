#pragma once
#include "GameObject.h"
enum class CHuge_Hermit_States
{
    IDLE,
    Walk,
    Run,
    Deploying,
    Deployed,
    UnDeploying,
    Cannon_firing,
    Firing,
    Dead
};




class CHuge_Hermit :
    public CGameObject
{
private:
    CHuge_Hermit_States States = CHuge_Hermit_States::IDLE;

public:
    CHuge_Hermit() : CGameObject() {};
    CHuge_Hermit(Vec2 position) : CGameObject(position) { Obj_speed.x = Obj_speed.y = 0;  Obj_Size = Vec2(230, 206); };

    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();

};

