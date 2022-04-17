#pragma once
#include "GameObject.h"
#include "CMarco.h"
#include "CChowmein.h"
#include "CLocust.h"
#include "Flying_Killer.h"
#include "CScene.h"
#include "Utils.h"
#include "Marcoinfo.h"
#include "Cgrib.h"
#include <fstream>
class Cplayscene :
    public CScene
{
private:
    CMarco* player;
    LPDIRECT3DSURFACE9 map;
    int wMap, hMap;
    Cgrib* grib;
    unordered_map<int, LPCGameObject> GameObjects;
    unordered_map<int, LPCGameObject> listGameObjectInCamera;
    /*void _ParseSection_SPRITES(string line);
    void _ParseSection_ANIMATIONS(string line);*/

    /* void _ParseSection_ASSETS(string line);*/
    void _ParseSection_OBJECTS(string line);
    void _ParseSection_MAP(string line);
    //void _ParseSection_QUADTREE(LPSTR filePath);

    //void LoadAssets(LPSTR assetFile);
public:
    Cplayscene(int id, LPSTR filePath) :CScene(id, filePath) { this->player = NULL; this->map = NULL; this->grib = NULL; }
    Cplayscene(int id, LPSTR filePath, CMarco* player) :CScene(id, filePath), player(player) { this->map = NULL, this->grib = NULL; }

    void setPlayer(CMarco* player);
    void Load();
    void Clear();
    void Update(DWORD dt);
    void Render();
};

