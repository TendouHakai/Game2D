#pragma once
#include "GameObject.h"

#define Flying_killer_jump 2;
#define Flying_killer_speed 5;

enum class Flying_killer_states
{
    jump,
    attack
};

class Flying_Killer :
    public CGameObject
{
    Flying_killer_states states = Flying_killer_states::jump;

    DWORD frame_time;

public:
    Flying_Killer() : CGameObject() {};
    Flying_Killer(Vec2 position) : CGameObject(position)
    {
        frame_time = GetTickCount64();
        /*Obj_speed.y = Flying_killer_jump;*/
        Obj_speed.y = 0;
        Obj_speed.x = 0;
        Obj_Size = Vec2(33, 33);
    };

    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();
};

