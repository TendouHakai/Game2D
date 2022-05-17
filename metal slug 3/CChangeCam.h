#pragma once
#include "GameObject.h"
class CChangeCam :
    public CGameObject
{
private:
    float y;
public:
    CChangeCam():CGameObject(){}
    CChangeCam(Vec2 position, Vec2 size, float y) : CGameObject(position) { Obj_speed.x = Obj_speed.y = 0; this->Obj_Size = size, this->y = y; }

    void Update(DWORD dt, vector<LPCGameObject>* coObjects){}
    void Render() {}
    void DrawAnimation() {}
    int IsBlocking() { return 0; }

    float GetCamY() { return y; }
};

