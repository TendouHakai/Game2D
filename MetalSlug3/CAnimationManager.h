#pragma once
#include"CAnimation.h"
#include<unordered_map>
#include "TinyXML/tinyxml.h"
#include "Debug.h"
#include "TinyXML/tinystr.h"
#include "CSpriteManager.h"
#include"CSprite.h"

class CAnimationManager
{
	CAnimationManager() {}
	static CAnimationManager* _Instance;

	unordered_map<string, Animation> animations;
	
public:
	virtual void Add(string id, Animation animation);

	virtual Animation Get(string id);

	virtual void ImportFromXml(const char* filePath);

	static CAnimationManager* GetInstance();

	~CAnimationManager();
};

