#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include "GameObject.h"
class CScene
{
protected:
	int id;
	LPCWSTR sceneFilePath;

public:
	CScene() {}
	CScene(int id, LPCWSTR filePath)
	{
		this->id = id;
		this->sceneFilePath = filePath;
	}

	virtual void Load() = 0;
	virtual void UnLoad() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void AddObject(int ObjectID, LPCGameObject obj = NULL) {}
	//virtual Vec2 GetSpeedPlayer() { return Vec2(0, 0); }
	//virtual void SetSpeedPlayer(Vec2 speed) {}
};
typedef CScene* LPSCENE;