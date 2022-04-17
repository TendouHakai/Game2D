#include "Cplayscene.h"

void Cplayscene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	int Objecttype = atoi(tokens[0].c_str());
	int ObjectID = atoi(tokens[1].c_str());
	int x = atoi(tokens[2].c_str());
	int y = atoi(tokens[3].c_str());

	LPCGameObject obj = NULL;
	switch (Objecttype)
	{
	case CCHOWMEIN_OBJECT_TYPE:
		obj = new CChowmein(Vec2(x, y));
		break;
	case CLOCUST_OBJECT_TYPE:
		obj = new CLocust(Vec2(x, y));
		break;
	case FLY_KILLER_OBJECT_TYPE:
		obj = new Flying_Killer(Vec2(x, y));
		break;
	default:
		break;
	}
	pair<int, LPCGameObject> GameObject(ObjectID, obj);
	GameObjects.insert(GameObject);
}

void Cplayscene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);
	LPSTR filePath = (LPSTR)tokens[0].c_str();
	int red = atoi(tokens[1].c_str());
	int green = atoi(tokens[2].c_str());
	int blue = atoi(tokens[3].c_str());
	map = CGraphic::GetInstance()->Loadsurface(filePath, D3DCOLOR_XRGB(red, green, blue));
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(filePath, &info);
	this->wMap = info.Width;
	this->hMap = info.Height;
}

void Cplayscene::setPlayer(CMarco* player)
{
	this->player = player;
}

void Cplayscene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_LINE];

	while (f.getline(str, MAX_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		//if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; }
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; }
		if (line == "[MAP]") { section = SCENE_SECTION_MAP; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
			//case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		}
	}
	f.close();
	grib = new Cgrib();
	grib->Build(GameObjects, wMap, hMap);
	DebugOut(L"Load scene is completed\n");
}

void Cplayscene::Clear()
{
	if (map != NULL)
		map->Release();
	if (grib != NULL)
	{
		grib->Release();
	}
	GameObjects.clear();
}

void Cplayscene::Update(DWORD dt)
{
	listGameObjectInCamera.clear();
	listGameObjectInCamera = grib->getlistGameObjectsInCamera();
	for (auto x : listGameObjectInCamera)
		x.second->Update(dt, nullptr);

	//Convert objects in current cell to vector
	vector<LPCGameObject> objectInCell;

	for (const auto& g : listGameObjectInCamera)
		objectInCell.push_back(g.second);

	player->Update(dt, &objectInCell);
	CCamera::GetInstance()->SetCamFollow(player->GetPosition(), wMap, hMap);
}

void Cplayscene::Render()
{
	for (auto x : listGameObjectInCamera)
	{
		x.second->Render();
		DebugOut(L"Object %d\n", x.first);
	}
	player->Render();
	RECT rect;
	rect.left = CCamera::GetInstance()->GetCamPosition().x;
	rect.right = rect.left + CCamera::GetInstance()->GetCamSize().x;
	rect.top = hMap - CCamera::GetInstance()->GetCamPosition().y;
	rect.bottom = rect.top + CCamera::GetInstance()->GetCamSize().y;
	CGraphic::GetInstance()->DrawSurface(map, &rect, NULL);
}

