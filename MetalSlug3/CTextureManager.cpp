#include "CTextureManager.h"
#include "CGame.h"
#include "Debug.h"

CTextureManager* CTextureManager::_Instance = NULL;

CTextureManager::CTextureManager()
{
}

void CTextureManager::Add(string id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	this->textures[id] = createTextureFromFile(filePath,transparentColor);
}

LPDIRECT3DTEXTURE9 CTextureManager::createTextureFromFile(LPCWSTR filepath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DDEVICE9 d3ddv = CGraphic::GetInstance()->GetDevice();
	HRESULT result = D3DXGetImageInfoFromFileW(filepath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filepath);
		return NULL;
	}

	result = D3DXCreateTextureFromFileExW(
		d3ddv,								// Pointer to Direct3D device object
		filepath,						// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,			// Transparent color
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] CreateTextureFromFile failed. File: %s\n", filepath);
		return NULL;
	}

	DebugOut(L"[INFO] Texture loaded Ok: %s \n", filepath);
	return texture;
}

LPDIRECT3DTEXTURE9 CTextureManager::Get(string i)
{
	if (textures.find(i) == textures.end()) return NULL;
	return textures[i];
}

CTextureManager* CTextureManager::GetInstance()
{
	if (_Instance == NULL)
	{
		_Instance = new CTextureManager();
	}
	return _Instance;

}

CTextureManager::~CTextureManager()
{
	textures.clear();
	_Instance = NULL;
}
