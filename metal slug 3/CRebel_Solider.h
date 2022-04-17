#pragma once
#include "GameObject.h"

enum class CRebel_Solider_states
{
    IDLE,
    Drop_down,
    Dead_drop_down,
    Dead, 
    Throw_bomb
};

class CRebel_Solider :
    public CGameObject
{
private:
    CRebel_Solider_states states = CRebel_Solider_states::Drop_down;
public:
    CRebel_Solider() : CGameObject() {};
    CRebel_Solider(Vec2 position) : CGameObject(position)
    {
        Obj_speed.x = Obj_speed.y = 0;
        Obj_Size = Vec2(73, 50);
    };

    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();
};

