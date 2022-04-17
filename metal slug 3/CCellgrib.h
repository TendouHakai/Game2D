#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "GameObject.h"
#include <unordered_map>
class CCellgrib
{
private:
	unordered_map<int, LPCGameObject> listGameObjects;
public:
	CCellgrib()
	{
		listGameObjects.clear();
	}
	CCellgrib(unordered_map<int, LPCGameObject> listGameObjects)
	{
		this->listGameObjects = listGameObjects;
	}
	void addGameObject(int ID, LPCGameObject GameObject)
	{
		listGameObjects.insert(pair<int, LPCGameObject>(ID, GameObject));
	}
	unordered_map<int, LPCGameObject> getlistGameObjects()
	{
		return listGameObjects;
	}

};

