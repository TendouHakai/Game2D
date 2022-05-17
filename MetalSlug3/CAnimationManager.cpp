#include "CAnimationManager.h"


CAnimationManager* CAnimationManager::_Instance = NULL;

void CAnimationManager::Add(string id, Animation animation)
{
	this->animations[id] = animation;
}

Animation CAnimationManager::Get(string id)
{
	if (animations.find(id) == animations.end()) return nullptr;
	return animations[id];
}

void CAnimationManager::ImportFromXml(const char* filePath)
{
	TiXmlDocument doc(filePath);
	if (doc.LoadFile())
	{
		TiXmlElement* pRoot = doc.RootElement();

		if (pRoot)
		{
			TiXmlElement* pObj = pRoot->FirstChildElement();

			DebugOut(L"Object ID: %s\n", ToLPCWSTR(pObj->Attribute("gameObjectId")));

			for (TiXmlElement* aniNode = pObj->FirstChildElement(); aniNode != nullptr; aniNode = aniNode->NextSiblingElement()) {
				int animationDefaultFrameTime = 100;
				aniNode->QueryIntAttribute("frameTime", &animationDefaultFrameTime);

				Animation ani = make_shared<CAnimation>(animationDefaultFrameTime);

				for (TiXmlElement* spriteNode = aniNode->FirstChildElement(); spriteNode != nullptr; spriteNode = spriteNode->NextSiblingElement())
				{
					string id = spriteNode->Attribute("id");
					Sprite sprite = CSpriteManager::GetInstance()->Get(id);
					ani->AddFrame(sprite, animationDefaultFrameTime);
				}

				this->Add(aniNode->Attribute("aniId"), ani);
				DebugOut(L"Animation loaded. Id = %s\n", ToLPCWSTR(aniNode->Attribute("aniId")));
			}
		}
	}
	else
	{
		DebugOut(L"Failed to load file \"%s\"\n", ToLPCWSTR(filePath));
	}
}

CAnimationManager* CAnimationManager::GetInstance()
{
	if (_Instance == nullptr)
	{
		_Instance = new CAnimationManager();
	}
	return _Instance;
}
CAnimationManager::~CAnimationManager()
{
}
