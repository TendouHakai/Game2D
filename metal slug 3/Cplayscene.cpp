#include "Cplayscene.h"

void Cplayscene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	int Objecttype = atoi(tokens[0].c_str());
	int ObjectID = atoi(tokens[1].c_str());
	float x = stof(tokens[2].c_str());
	float y = stof(tokens[3].c_str());
	float stairType;
	float directx;
	float directy;
	float a[10];

	LPCGameObject obj = NULL;
	switch (Objecttype)
	{
	case MARCO_OBJECT_TYPE:
		if (tokens.size() > 4)
		{
			obj = new CMarco(Vec2(x, y), true);
		}	
		else obj = new CMarco(Vec2(x, y));
		player = (CMarco*)obj;
		return;
	case CCHOWMEIN_OBJECT_TYPE:
		if (tokens.size() > 4)
		{
			a[1] = stof(tokens[4].c_str());
			CStair* stair = (CStair*)listGameMaps.at(a[1]);
			a[1] = stair->GetDirect().x;
			a[2] = stair->GetDirect().y;
			a[3] = stair->GetStairType();
			a[4] = stair->GetPosition().x;
			a[5] = stair->GetPosition().y;
			obj = new CChowmein(Vec2(x, y), Vec2(a[1], a[2]), a[3], Vec2(a[4], a[5]));
			break;
		}
		obj = new CChowmein(Vec2(x, y));
		break;
	case CLOCUST_OBJECT_TYPE:
		obj = new CLocust(Vec2(x, y));
		break;
	case FLY_KILLER_OBJECT_TYPE:
		obj = new Flying_Killer(Vec2(x, y));
		break;
	case HUGE_HERMIT_OBJECT_TYPE:
		obj = new CHuge_Hermit(Vec2(x, y));
		break;
	case REBEL_SOLIDER_OBJECT_TYPE:
		obj = new CRebel_Solider(Vec2(x, y));
		break;
	case OHUMEIN_CONGA_OBJECT_TYPE:
		obj = new COhumein_Conga(Vec2(x, y));
		break;
	case BOAT_OBJECT_TYPE:
		obj = new Object_notmoving(Vec2(x, y));
		break;
	case BLOCK_OBJECT_TYPE:
		obj = new CBlock(Vec2(x,y));
		break;
	case STAIR_OBJECT_TYPE:
		a[1] = stof(tokens[4].c_str());
		a[2] = stof(tokens[5].c_str());
		a[3] = stof(tokens[6].c_str());
		obj = new CStair(Vec2(x, y), a[1], Vec2(a[2], a[3]));
		break;
	case STAIR2_OBJECT_TYPE:
		a[1] = stof(tokens[4].c_str());
		a[2] = stof(tokens[5].c_str());
		obj = new CStair2(Vec2(x, y), Vec2(a[1], a[2]));
		break;
	case PLATFORM_OBJECT_TYPE:
		a[1] = stof(tokens[4].c_str());
		a[2] = stof(tokens[5].c_str());
		obj = new CPlatform(Vec2(x, y), Vec2(a[1], a[2]));
		break;
	case CHANGECAM_OBJECT_TYPE:
		a[1] = stof(tokens[4].c_str());
		a[2] = stof(tokens[5].c_str());
		a[3] = stof(tokens[6].c_str());
		obj = new CChangeCam(Vec2(x, y), Vec2(a[1], a[2]), a[3]);
		break;
	case PORTAL_OBJECT_TYPE:
		a[1] = stof(tokens[4].c_str());
		a[2] = stof(tokens[5].c_str());
		a[3] = atoi(tokens[6].c_str());
		obj = new CPortal(Vec2(x, y), Vec2(a[1], a[2]), a[3]);
		break;
	case Game_Map_Animation_ObjectType:
		obj = new CGameMap(Vec2(x, y));
		break;
	}
	if (obj->GetType() == GAME_MAP_OBJECT)
	{
		pair<int, LPCGameObject> GameObject(ObjectID, obj);
		listGameMaps.insert(GameObject);
	}
	else
	{
		pair<int, LPCGameObject> GameObject(ObjectID, obj);
		GameObjects.insert(GameObject);
	}
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

void Cplayscene::UnLoad()
{
	if (map != NULL)
		map->Release();
	if (grib != NULL)
	{
		grib->Release();
	}
	for (size_t i = 0; i < GameObjects.size(); i++)
		delete GameObjects[i];
	for (size_t i = 0; i < listGameMaps.size(); i++)
		delete listGameMaps[i];
	for (size_t i = 0; i < ListWeaponSFX.size(); i++)
		delete ListWeaponSFX[i];

	GameObjects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

void Cplayscene::Update(DWORD dt)
{
	listGameObjectInCamera.clear();
	listGameObjectInCamera = grib->getlistGameObjectsInCamera();

	if (NextScene_ID >= 0 && player==NULL)
	{
		ProcessKeyboard();
	}

	std::vector<int> needs_removing;
	for (auto&& pair : ListWeaponSFX)
	{
		if (pair.second->IsDeleted() == true || isObjectInCameraSize(pair.second->getBoundingBox()))
			needs_removing.push_back(pair.first);
	}
	for (auto&& key : needs_removing)
		ListWeaponSFX.erase(key);

	for (auto&& pair : listGameObjectInCamera)
	{
		if (pair.second->IsDeleted() == true)
			needs_removing.push_back(pair.first);
	}
	for (auto&& key : needs_removing)
		listGameObjectInCamera.erase(key);

	//Convert objects in current cell to vector
	vector<LPCGameObject> objectInCell;

	for (const auto& g : listGameObjectInCamera)
		objectInCell.push_back(g.second);
	for (const auto& g : ListWeaponSFX)
		objectInCell.push_back(g.second);
	for (const auto& g : listGameMaps)
		objectInCell.push_back(g.second);

	if(player!=NULL)
		player->Update(dt, &objectInCell);

	objectInCell.push_back(player);

	for (auto x : listGameObjectInCamera)
	{
		x.second->Update(dt, &objectInCell);
	}
	for (auto x : ListWeaponSFX)
		x.second->Update(dt, &objectInCell);

	if(player!=NULL)
		CCamera::GetInstance()->Update(dt, player->GetPosition(), wMap, player->GetIsInWater());
}

void Cplayscene::Render()
{
	RECT rect;
	rect.left = CCamera::GetInstance()->GetCamPosition().x;
	rect.right = rect.left + CCamera::GetInstance()->GetCamSize().x;
	rect.top = hMap - CCamera::GetInstance()->GetCamPosition().y;
	rect.bottom = rect.top + CCamera::GetInstance()->GetCamSize().y;
	CGraphic::GetInstance()->DrawSurface(map, &rect, NULL);
	for (auto x : listGameMaps)
	{
		x.second->Render();
	}
	for (auto x : listGameObjectInCamera)
	{
		/*if (x.second->IsBlocking())
			continue;*/
		x.second->Render();
		//DebugOut(L"rect (%d,%d,%d,%d)\n", x.second->getActiveRange().left, x.second->getActiveRange().right, x.second->getActiveRange().top, x.second->getActiveRange().bottom);
	}
	
	for (auto x : ListWeaponSFX)
	{
		/*if (x.second->IsBlocking())
			continue;*/
		x.second->Render();
		//DebugOut(L"rect (%d,%d,%d,%d)\n", x.second->getActiveRange().left, x.second->getActiveRange().right, x.second->getActiveRange().top, x.second->getActiveRange().bottom);
	}
	if (player != NULL)
	{
		player->Render();
		//DebugOut(L"rect marco (%d, %d, %d, %d)\n", player->getActiveRange().left, player->getActiveRange().right, player->getActiveRange().top, player->getActiveRange().bottom);
	}
}

void Cplayscene::AddObject(int ObjectID, LPCGameObject obj)
{
	pair<int, LPCGameObject> GameObject(ObjectID, obj);
	ListWeaponSFX.insert(GameObject);
}

bool Cplayscene::isObjectInCameraSize(RECT size)
{
	RECT CamRect = CCamera::GetInstance()->getBoundingBox();

	return	!(size.left < CamRect.right&& size.right > CamRect.left && size.top < CamRect.bottom&& size.bottom> CamRect.top);
}

bool Cplayscene::isHavePlayer()
{
	if (this->player != NULL)
		return true;
	return false;
}

int Cplayscene::GetIDNextScene()
{
	return NextScene_ID;
}

void Cplayscene::ProcessKeyboard()
{
	DIDEVICEOBJECTDATA KeyData[KEYBOARD_BUFFER_SIZE];
	DWORD* dwElements = new DWORD[KEYBOARD_BUFFER_SIZE];
	if (CKeyBoard::GetInstance()->GetKeyboardData(KeyData, dwElements) == 0)
	{
		return;
	}
	DWORD dwElementsData = *dwElements;
	for (DWORD i = 0; i < dwElementsData; i++)
	{
		int KeyCode = KeyData[i].dwOfs;
		int KeyState = KeyData[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
	}
}

void Cplayscene::OnKeyDown(int keycode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", keycode);
	switch (keycode)
	{
	case DIK_RETURN:
		CGame::GetInstance()->SetNextScene(NextScene_ID);
		break;
	default:
		break;
	}
}

