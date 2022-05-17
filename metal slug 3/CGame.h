#pragma once
#include <Windows.h>
#include <csignal>
#include "d3d9.h"
#include "d3dx9.h"
#include "CGraphic.h"
#include "CKeyBoard.h"
#include"CCamera.h"

#include "MS3GameInfo.h"
#include "CAnimationManager.h"
#include"CAnimation.h"
#include"CSpriteManager.h"
#include "CTextureManager.h"

#include "CScene.h"
#include "Cplayscene.h"
#define FRAME_RATE 30

class CGame
{
private:

	static CGame* _Instance;
	LPDIRECT3D9 _d3d;

	HWND _hWnd;
	HINSTANCE _hInstance;

	DWORD frame_start = GetTickCount();
	DWORD count_per_frame = 1000 / FRAME_RATE;

	int y;
	int flag = 0;
	int degree = 0;

	int			_scrWidth;
	int			_scrHeight;
	int			_frameRate;
	bool		_windowMode;

	bool		_InitWindow();
	//bool		_InitDirectX();
	/*bool		_Initkeyboard();*/
	CGraphic* Graphic;
	CKeyBoard* KeyBoard;
	CMarco* Marco = new CMarco(Vec2(100,400));
	vector<CGameObject*> GameObject;

	CCamera* Camera = CCamera::GetInstance();

	CScene* scene;
	unordered_map<int, LPSCENE> scenes;
	int current_scene;
	int next_scene;

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);
public:

	static LRESULT CALLBACK _WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	CGame();
	CGame(HINSTANCE _hInstance, int _srcWidth, int _srcHeight, int _frameRate, bool _windowMode);
	~CGame();

	void Restart();
	void GameInit();
	void GameRun();
	void GameEnd();

	void LoadResource();
	void Load(LPSTR gamePath);
	void SwitchScene();
	void SetNextScene(int nextScene);
	void SetNextScene();
	LPSCENE GetcurrentScene();
	void AddObjectsToCurrrentScene(int ObjectID, LPCGameObject obj = NULL);
	//void LoadGameObject();

	static CGame* GetInstance();

};

