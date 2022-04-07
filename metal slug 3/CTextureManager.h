#pragma once
#include <unordered_map>
#include <string>
#include "d3dx9.h"
#include "CGraphic.h"

using namespace std;

class CTextureManager
{
	static CTextureManager* _Instance;
	unordered_map<string, LPDIRECT3DTEXTURE9> textures;

public : 
	CTextureManager();
	virtual void Add(string id, LPCWSTR filePath, D3DCOLOR transparentColor);

	virtual LPDIRECT3DTEXTURE9 createTextureFromFile(LPCWSTR filepath, D3DCOLOR transparentColor);

	virtual LPDIRECT3DTEXTURE9 Get(string i);

	static CTextureManager* GetInstance();
	~CTextureManager();
};


