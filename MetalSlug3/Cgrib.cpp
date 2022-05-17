#include "Cgrib.h"

void Cgrib::Build(unordered_map<int, LPCGameObject> listGameObjects, int wMap = 0, int hMap = 0)
{
	this->wCell = CCamera::GetInstance()->GetCamSize().x / 2;
	this->hCell = CCamera::GetInstance()->GetCamSize().y / 2;
	this->rows = hMap / this->hCell;
	this->columns = wMap / this->wCell;
	grib = new CCellgrib * [rows +1];
	for (int i = 0; i <= rows; i++)
	{
		grib[i] = new CCellgrib[columns+1];
	}
	int rowStart, rowEnd, columnStart, columnEnd;
	for (auto x : listGameObjects)
	{
		getCellcontainGameObject(rowStart, columnStart, rowEnd, columnEnd, x.second->getActiveRange());
		for (int i = rowStart; i <= rowEnd; i++)
		{
			for (int j = columnStart; j <= columnEnd; j++)
			{
				grib[i][j].addGameObject(x.first, x.second);
			}
		}
	}
	DebugOut(L"Build girb comletely");
}

unordered_map<int, LPCGameObject> Cgrib::getlistGameObjectsInCamera()
{
	unordered_map<int, LPCGameObject> listGameObjectInCamera;
	listGameObjectInCamera.clear();
	int rowStart, rowEnd, columnStart, columnEnd;
	getCellcontainGameObject(rowStart, columnStart, rowEnd, columnEnd, CCamera::GetInstance()->getBoundingBox());
	for (int i = rowStart; i <= rowEnd; i++)
	{
		for (int j = columnStart; j <= columnEnd; j++)
		{
			if (grib[i][j].getlistGameObjects().size() != 0)
			{
				for (auto x : grib[i][j].getlistGameObjects())
				{
					if (listGameObjectInCamera.size() == 0)
					{
						listGameObjectInCamera.insert(x);
						continue;
					}
					if (listGameObjectInCamera.find(x.first) == listGameObjectInCamera.end())
						listGameObjectInCamera.insert(x);
					else
						continue;
				}
			}
			
		}
	}
	return listGameObjectInCamera;
}

void Cgrib::getCellcontainGameObject(int &rowStart, int &columnStart, int &rowEnd, int &columnEnd, RECT getBoundingBox)
{
	rowStart = getBoundingBox.top / hCell;
	if (rowStart < 0)
		rowStart = 0;
	rowEnd = getBoundingBox.bottom / hCell;
	if (rowEnd >= rows)
		rowEnd = rows - 1;
	columnStart = getBoundingBox.left / wCell;
	if (columnStart < 0)
		columnStart = 0;
	columnEnd = getBoundingBox.right / wCell;
	if (columnEnd >= columns)
		columnEnd = columns - 1;
}

void Cgrib::Release()
{
	for (int i = 0; i <= rows; i++)
		delete[] grib[i];
	delete[] grib;
}
