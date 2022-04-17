#pragma once
#include "GameObject.h" 

enum class Locust_states {
    flying,
    attack,
    preattack,
    turn
};

class CLocust :
	public CGameObject
{
    Locust_states states = Locust_states::flying;
public:
    CLocust() : CGameObject() {};
    CLocust(Vec2 position) : CGameObject(position)
    { 
            Obj_speed.x = Obj_speed.y = 0; 
            Obj_Size = Vec2(73, 50);
    };

    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();

    void SetState(Locust_states state);
};

