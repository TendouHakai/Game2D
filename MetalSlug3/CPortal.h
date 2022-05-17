#pragma once
#include "GameObject.h"
class CPortal :
    public CGameObject
{
private:
    int scene_id;
public:
    CPortal() :CGameObject() { this->scene_id = -1; }
    CPortal(Vec2 postion, Vec2 size, int scene_id ) : CGameObject(postion) { this->Obj_speed.x = this->Obj_speed.y = 0; this->Obj_Size = size; this->scene_id = scene_id;}

    void Update(DWORD dt, vector<LPCGameObject>* coObjects) {}
    void Render() { DrawAnimation(); }
    void DrawAnimation()
    { 
        //CAnimationManager::GetInstance()->Get("stair").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0)); 
    }
    int IsBlocking() { return 0; }

    int GetScene_id();
};

