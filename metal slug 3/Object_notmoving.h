#pragma once
#include "GameObject.h"
class Object_notmoving :
    public CGameObject
{
private:
    int Chowmein_Object;
public:
    Object_notmoving() : CGameObject() {};
    Object_notmoving(Vec2 position) : CGameObject(position)
    {
        Obj_speed.x = Obj_speed.y = 0;
        Obj_Size = Vec2(203, 224);
        this->type = GAME_MAP_OBJECT;
    };


    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();

};

