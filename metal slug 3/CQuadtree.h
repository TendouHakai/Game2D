#pragma once
#include "CQuadnode.h"
class CQuadtree
{
private:
	
	
public:
	CQuadnode* rootNode;
	unordered_map<int, LPCGameObject> listGameObjectInCamera;
	CQuadtree() {
		this->rootNode = NULL;
		this->listGameObjectInCamera.clear();
	}
	void setRootNode(unordered_map<int, LPCGameObject> GameObjects, int w, int h);
	void Build(CQuadnode* Node);
	void getListGameObjectInCamera(CQuadnode* Node);
};

