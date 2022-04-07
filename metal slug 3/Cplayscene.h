#pragma once
#include "GameObject.h"
#include "CMarco.h"
#include "CChowmein.h"
#include "CLocust.h"
#include "Flying_Killer.h"
#include "CQuadtree.h"
#include "CScene.h"
#include "Utils.h"
#include "Marcoinfo.h"
#include <fstream>
class Cplayscene :
    public CScene
{
private:
    CMarco * player;
    LPDIRECT3DSURFACE9 map;
    int wMap, hMap;
    CQuadtree* tree;
    unordered_map<int, LPCGameObject> GameObjects;
    /*void _ParseSection_SPRITES(string line);
    void _ParseSection_ANIMATIONS(string line);*/

   /* void _ParseSection_ASSETS(string line);*/
    void _ParseSection_OBJECTS(string line);
    void _ParseSection_MAP(string line);
    //void _ParseSection_QUADTREE(LPSTR filePath);

    //void LoadAssets(LPSTR assetFile);
public:
    Cplayscene(int id, LPSTR filePath) :CScene(id, filePath) { this->player = NULL; this->map = NULL; this->tree = NULL; }
    Cplayscene(int id, LPSTR filePath, CMarco* player) :CScene(id, filePath), player(player) { this->map = NULL, this->tree = NULL; }

    void setPlayer(CMarco* player);
    void Load();
    void Clear();
    void Update(DWORD dt);
    void Render();
};

