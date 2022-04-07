#pragma once
#include "CSprite.h"
#include "CTextureManager.h"
#include "TinyXML/tinyxml.h"
#include "TinyXML/tinystr.h"
#include "Debug.h"


class CSpriteManager
{
	CSpriteManager();
	static CSpriteManager* _Instance;

	unordered_map<string, Sprite> sprites;

public : 
	virtual Sprite Add(string id, int left, int top, int width, int height, int xpivot, int ypivot, LPDIRECT3DTEXTURE9 tex);

	virtual Sprite Get(string id);

	virtual void ImportFromXml(const char* filePath);

	static	CSpriteManager* GetInstance();
	~CSpriteManager();
};

