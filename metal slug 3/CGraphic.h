#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Transform.h"


class CGraphic
{
private:
	static CGraphic* _Instance;
	CGraphic();
	//DOI TUONG DIRECTX
	LPDIRECT3D9 d3d;
	//THIET BI VE
	LPDIRECT3DDEVICE9 d3ddev;
	//SPRITE
	LPD3DXSPRITE d3dxSprite;
	LPDIRECT3DSURFACE9 backbuffer;
	//HWND
	HWND hWnd;
	int Width;
	int Height;
public:
	bool InitD3D();

	CGraphic(HWND, int, int);
	~CGraphic(void);

	void Begin();
	void End();

	PDIRECT3DSURFACE9 Loadsurface(LPSTR filePath, D3DCOLOR transcolor);
	void DrawSurface(LPDIRECT3DSURFACE9 surface, RECT* rectSource, RECT* rectDestination);
	void DrawTexture(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 postion, D3DCOLOR color);
	//void DrawTexture(LPDIRECT3DTEXTURE9 texture, RECT source, D3DXVECTOR2 postion, D3DCOLOR color, bool flag);
	void DrawTexture(LPDIRECT3DTEXTURE9 texture, RECT source, D3DXVECTOR2 postion, D3DCOLOR color, bool flag,Vec2 size, Vec2 translate);

	bool Collision(RECT rect1, RECT rect2);
	LPDIRECT3DDEVICE9 GetDevice();

	static CGraphic* GetInstance();
};

