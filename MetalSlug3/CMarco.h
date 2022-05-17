#pragma once
#include "GameObject.h"
#include "CKeyBoard.h"
#include "CBlock.h"
#include "CStair.h"
#include "CChangeCam.h"
#include "CStair2.h"
//dang su ly phan states


#define Marco_Speed_X 0.2f;
#define Marco_Speed_Y 0.04f;


class CMarco :
    public CGameObject
{
    leg_states leg = leg_states::stand;
    Weapon_State Weapon = Weapon_State::IDLE;
    Body_states body = Body_states::IDLE;
    bool isInWater;

    Vec2 direct;
    Vec2 positionStair;
    int stairType;
    bool IsOnStair;
    bool IsCollisionStair;
    bool IsOnStair2;
    float yStair2;

    static CMarco* _Instance;
    DWORD FiringTime;

    int bulletcount = 0;

public :

    CMarco() : CGameObject() {};
    CMarco(Vec2 position) : CGameObject(position) 
    { 
        Obj_speed.x = Obj_speed.y = 0;
        Obj_Size = Vec2(24 * 2, 37 * 2);
        _Instance = this;
        direct = Vec2(0, 0);
        this->IsOnStair = false;
        this->IsOnStair2 = false;
        stairType = 0;
        this->IsCollisionStair = false;
        this->isInWater = false;
        HealBar = 1;
        FiringTime = 0;
    };
    CMarco(Vec2 position, bool isInWater) : CGameObject(position)
    {
        Obj_speed.x = Obj_speed.y = 0;
        Obj_Size = Vec2(24 * 2, 37 * 2);
        _Instance = this;
        direct = Vec2(0, 0);
        this->IsOnStair = false;
        this->IsOnStair2 = false;
        stairType = 0;
        this->IsCollisionStair = false;
        this->isInWater = isInWater;
        HealBar = 1000;
        FiringTime = 0;
    }
    void Update(DWORD dt, vector<LPCGameObject>* coObjects);
    void Render();
    void DrawAnimation();
    void SetDirectOnStair(Vec2 driect, int stairType, Vec2 positionStair);

    void ProcessKeyboard();
    void OnKeyUp(int keycode);
    void OnKeyDown(int keycode);
    
    // các hàm hỗ trợ xữ lý va chạm
    int IsCollidable() { return 1; }
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
    int IsBlocking() { return 0; }
    // các hàm xữ lý khi va chạm vào các đối tượng
    void OnCollisionWithStair(LPCOLLISIONEVENT e);
    void OnCollisionWithStair2(LPCOLLISIONEVENT e);
    void OnCollisionWithChangeCam(LPCOLLISIONEVENT e);
    void OnCollisionWithPortal(LPCOLLISIONEVENT e);

    RECT getBoundingBox();
    RECT getActiveRange();
    bool GetIsInWater();
    static CMarco* getInstance();
};

