#pragma once
#include "GameObject.h"
#include "CMarco.h"
#include "CChowmein.h"
#include "CLocust.h"
#include "Flying_Killer.h"
#include "CHuge_Hermit.h"
#include "CRebel_Solider.h"
#include "CBlock.h"
#include "CStair.h"
#include "CPlatform.h"
#include "CChangeCam.h"
#include "CPortal.h"
#include "CGunBullet.h"
#include "CGameMap.h"
#include "COhumein_Conga.h"
#include "Object_notmoving.h"
#include "CGame.h"

#include "CScene.h"
#include "Utils.h"
#include "MS3GameInfo.h"
#include "Cgrib.h"
#include <fstream>


class Cplayscene :
    public CScene
{
private:
    int NextScene_ID;
    CMarco* player;
    LPDIRECT3DSURFACE9 map;
    int wMap, hMap;
    Cgrib* grib;
    unordered_map<int, LPCGameObject> GameObjects;
    unordered_map<int, LPCGameObject> listGameMaps;
    unordered_map<int, LPCGameObject> listGameObjectInCamera;

    unordered_map<int, LPCGameObject> ListWeaponSFX;
    /*void _ParseSection_SPRITES(string line);
    void _ParseSection_ANIMATIONS(string line);*/

    /* void _ParseSection_ASSETS(string line);*/
    void _ParseSection_OBJECTS(string line);
    void _ParseSection_MAP(string line);

    //void LoadAssets(LPSTR assetFile);
public:
    Cplayscene() {}
    Cplayscene(int id, LPCWSTR filePath) :CScene(id, filePath) { this->player = NULL; this->map = NULL; this->grib = NULL; this->NextScene_ID = -1; }
    Cplayscene(int id, LPCWSTR filePath, CMarco* player) :CScene(id, filePath), player(player) { this->map = NULL, this->grib = NULL; this->NextScene_ID = -1; }
    Cplayscene(int id, LPCWSTR filePath, int NextScene_ID) :CScene(id, filePath) { this->player = NULL; this->map = NULL; this->grib = NULL; this->NextScene_ID = NextScene_ID; }

    void setPlayer(CMarco* player);
    Vec2 GetSpeedPlayer() { return player->getSpeed(); }
    void SetSpeedPlayer(Vec2 speed) { player->SetSpeed(speed); }
    void Load();
    void Clear();
    void UnLoad();
    void Update(DWORD dt);
    void Render();

    void AddObject(int ObjectID, LPCGameObject obj = NULL);
    bool isObjectInCameraSize(RECT size);
    bool isHavePlayer();

    int GetIDNextScene();
    //Xữ lý phím (khi là IntroScene)
    void ProcessKeyboard();
    void OnKeyDown(int keycode);
};

