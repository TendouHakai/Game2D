#pragma once
#include<d3d9.h>
#include<d3dx9.h>
class CScene
{
protected:
	int id;
	LPSTR sceneFilePath;

public:
	CScene(int id, LPSTR filePath)
	{
		this->id = id;
		this->sceneFilePath = filePath;
	}

	virtual void Load() = 0;
	virtual void Clear() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
typedef CScene* LPSCENE;