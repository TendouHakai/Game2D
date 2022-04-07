#pragma once

#include <string>
#include<string.h>
#include "Transform.h"
#include "CGraphic.h"

using namespace std;

class CSprite
{
public:
	string id = "";

	int left = 0;
	int top = 0;
	int width = 0;
	int height = 0;

	D3DXVECTOR3 pivot;

	LPDIRECT3DTEXTURE9 texture = NULL;

public:
	CSprite(string id, int left, int top, int width, int height, int xPivot, int yPivot, LPDIRECT3DTEXTURE9 texture);

	virtual void Draw(Vec2 Position, D3DCOLOR overlay);
};

typedef CSprite* Sprite;