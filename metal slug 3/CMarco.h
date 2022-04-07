#pragma once
#include "GameObject.h"
#include "CKeyBoard.h"
//dang su ly phan states
enum class leg_states {
   stand,
   run
};

enum class Weapon_State {
    IDLE,
    FIRING,
    BOMMING
};


#define Marco_Speed 5;

class CMarco :
    public CGameObject
{
    leg_states leg = leg_states::stand;
    Weapon_State Weapon = Weapon_State::IDLE;

public :

    CMarco() : CGameObject() {};
    CMarco(Vec2 position) : CGameObject(position) { Obj_speed.x = Obj_speed.y = 0; };
    void Update(DWORD dt);
    void Render();
    void DrawAnimation();

    void ProcessKeyboard();
    void OnKeyUp(int keycode);
    void OnKeyDown(int keycode);


};

