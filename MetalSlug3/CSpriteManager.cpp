#include "CSpriteManager.h"

CSpriteManager* CSpriteManager::_Instance = NULL;

CSpriteManager::CSpriteManager()
{
}

Sprite CSpriteManager::Add(string id, int left, int top, int width, int height, int xpivot, int ypivot, LPDIRECT3DTEXTURE9 tex)
{
	Sprite sprite = new CSprite(id, left, top, width, height, xpivot, ypivot, tex);
	sprites[id] = sprite;
	return sprite;
}

Sprite CSpriteManager::Get(string id)
{
	if (sprites.find(id) == sprites.end()) return nullptr;
	return sprites[id];
}

void CSpriteManager::ImportFromXml(const char* filePath)
{
	TiXmlDocument doc(filePath);
	if (doc.LoadFile())
	{
		TiXmlElement* pRoot = doc.RootElement();

		if (pRoot)
		{
			for (TiXmlElement* sNode = pRoot->FirstChildElement("Textures"); sNode != NULL; sNode = sNode->NextSiblingElement("Textures"))
			{
				string textureId = sNode->Attribute("textureId");
				LPDIRECT3DTEXTURE9 texture = CTextureManager::GetInstance()->Get(textureId);

				for (TiXmlElement* pNode = sNode->FirstChildElement(); pNode != nullptr; pNode = pNode->NextSiblingElement()) {
					string id = pNode->Attribute("id");

					int left = 0, top = 0, width = 0, height = 0, xPivot = 0, yPivot = 0;
					pNode->QueryIntAttribute("x", &left);
					pNode->QueryIntAttribute("y", &top);
					pNode->QueryIntAttribute("w", &width);
					pNode->QueryIntAttribute("h", &height);
					if (pNode->Attribute("pX") != NULL) pNode->QueryIntAttribute("pX", &xPivot);
					if (pNode->Attribute("pY") != NULL) pNode->QueryIntAttribute("pY", &yPivot);

					CSpriteManager::GetInstance()->Add(id, left, top, width , height, xPivot, yPivot , texture);

					DebugOut(L"[INFO] Sprite loaded Ok : % s\n",ToLPCWSTR(id));
				}
			}
		}
	}
}

CSpriteManager* CSpriteManager::GetInstance()
{
	if (_Instance == nullptr) {
		_Instance = new CSpriteManager();
	}
	return _Instance;
}

CSpriteManager::~CSpriteManager()
{
}
