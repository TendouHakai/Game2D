#pragma once
#include "CCellgrib.h"
class Cgrib
{
private:
	int wCell, hCell;
	int rows, columns;
	CCellgrib** grib;
public:
	Cgrib()
	{
		grib = NULL;
	}
	void Build(unordered_map<int, LPCGameObject> listGameObjects, int wMap, int hMap);
	unordered_map<int, LPCGameObject> getlistGameObjectsInCamera();
	void getCellcontainGameObject(int &rowStart, int &columnStart, int &rowEnd, int &columnEnd, RECT getBoundingBox);
	void Release();
	
};

