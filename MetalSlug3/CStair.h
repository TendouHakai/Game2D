#pragma once
#include "GameObject.h"
#define BOTTOM_STAIR 1
#define TOP_STAIR 2
class CStair :
    public CGameObject
{
private:
    Vec2 direct;
    int stair;
public:
    CStair() : CGameObject() {}
    CStair(Vec2 position) : CGameObject(position) { Obj_speed.x = Obj_speed.y = 0; Obj_Size = Vec2(16 * 2, 100 * 2); this->type = GAME_MAP_OBJECT; }

    CStair(Vec2 position, int stair, Vec2 direct) : CGameObject(position) { Obj_speed.x = Obj_speed.y = 0; this->stair = stair; this->direct = direct; Obj_Size = Vec2(32, 200); this->type = GAME_MAP_OBJECT; }
    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();
    int IsBlocking() { return 0; }

    Vec2 GetDirect();
    int GetStairType() { return stair; }
};

