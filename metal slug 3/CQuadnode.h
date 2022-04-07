#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <unordered_map>
#include "GameObject.h"
#include "CGraphic.h"

using namespace std;
class CQuadnode
{
public:
	int ltx, lty, rbx, rby;
	CQuadnode* lt, * lb, * rt, * rb;
	unordered_map<int, LPCGameObject> Objects;
	CQuadnode() {}
	CQuadnode(int ltx, int lty, int rbx, int rby, unordered_map<int, LPCGameObject> GameOjects, bool isroot)
	{
		this->ltx = ltx;
		this->lty = lty;
		this->rbx = rbx;
		this->rby = rby;
		this->lt = NULL;
		this->lb = NULL;
		this->rb = NULL;
		this->rt = NULL;
		if (isroot)
		{
			Objects = GameOjects;
		}
		else
		{
			for (auto x : GameOjects)
			{
				if (IsContain(x.second))
				{
					Objects.insert(x);
				}
			}
		}
	}
	bool IsContain(LPCGameObject GameObjects);
	int getWidth();
	int getHeight();
	RECT getBoudingBox();
};

