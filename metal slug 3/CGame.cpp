#include "CGame.h"



CGame* CGame::_Instance = NULL;

bool CGame::_InitWindow()
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = _hInstance;

	wc.lpfnWndProc = (WNDPROC)_WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Game_Ball";
	wc.hIconSm = NULL;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(0, "Can not Register Class", "Error", MB_OK);
		return false;
	}

	_hWnd = CreateWindow(
		"Game_Ball",
		"Game Ball",
		WS_OVERLAPPEDWINDOW, 		// Window type
		CW_USEDEFAULT,			// Initial position
		CW_USEDEFAULT,
		_scrWidth,				// Width
		_scrHeight,				// Height
		NULL,
		NULL,
		_hInstance,			// Program instance
		NULL
	);
	if (!_hWnd)
	{
		return false;
	}
	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);

	return true;
}

LRESULT CGame::_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}

CGame::CGame()
{
}

CGame::CGame(HINSTANCE _hInstance, int _scrWidth, int _scrHeight, int _frameRate, bool _windowMode)
{
	_d3d = NULL;

	this->_hInstance = _hInstance;
	this->_scrWidth = _scrWidth;
	this->_scrHeight = _scrHeight;
	this->_frameRate = _frameRate;
	this->_windowMode = _windowMode;
	this->current_scene = this->next_scene = -1;

	_Instance = this;
}

CGame::~CGame()
{

}

void CGame::GameInit()
{
	_InitWindow();

	Graphic = new CGraphic(_hWnd, WINDOW_WIDTH, WINDOW_HEIGHT);
	Graphic->InitD3D();

	KeyBoard = CKeyBoard::GetInstance();
	KeyBoard->InitKeyboard(_hWnd);

	Camera->SetCamPosition(Vec2(0,WINDOW_HEIGHT+100));
	Camera->setCamSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	
	Load((LPSTR)"metal slug 3.txt");
	
	LoadResource();
	//LoadGameObject();
}

void CGame::GameRun()
{	
	Graphic->Begin();
	DebugOut(L"Game Run %d\n", current_scene);
	if (current_scene == 3)
	{
		DebugOut(L"\n");
	}
	GetcurrentScene()->Update(count_per_frame);
	GetcurrentScene()->Render();
	Graphic->End();
	SwitchScene();
}

void CGame::GameEnd()
{
	if (_d3d != NULL)
		_d3d->Release();
}

void CGame::LoadResource()
{
	TiXmlDocument doc("animation/ResourceData.xml");

	if (doc.LoadFile()) {
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* resources = root->FirstChildElement("Resources");

		TiXmlElement* textures = resources->FirstChildElement("Textures");
		TiXmlElement* sprites = resources->FirstChildElement("Sprites");
		TiXmlElement* animations = resources->FirstChildElement("Animations");


		for (TiXmlElement* node = textures->FirstChildElement("Texture"); node != nullptr; node = node->NextSiblingElement("Texture")) {
			CTextureManager::GetInstance()->Add(node->Attribute("id"), ToLPCWSTR(node->Attribute("path")), D3DCOLOR_XRGB(255, 255, 255));
		}

		for (TiXmlElement* node = sprites->FirstChildElement("Sprite"); node != nullptr; node = node->NextSiblingElement("Sprite")) {
			CSpriteManager::GetInstance()->ImportFromXml(node->Attribute("path"));
		}

		for (TiXmlElement* node = animations->FirstChildElement("Animation"); node != nullptr; node = node->NextSiblingElement("Animation")) {
			CAnimationManager::GetInstance()->ImportFromXml(node->Attribute("path"));
		}
	}
}
void CGame::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "start")
		next_scene = atoi(tokens[1].c_str());
	else
		DebugOut(L"[ERROR] Unknown game setting: %s\n", (LPSTR*)(tokens[0]).c_str());
}
void CGame::_ParseSection_SCENES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	int id = atoi(tokens[0].c_str());
	LPCWSTR path = ToLPCWSTR(tokens[1]);	// file: ASCII format (single-byte char) => Wide Char
	int nextsceneID = -1;
	LPSCENE scene = NULL;
	if (tokens.size() == 3)
	{
		nextsceneID = atoi(tokens[2].c_str());
		scene = new Cplayscene(id, path, nextsceneID);
	}
	else scene = new Cplayscene(id, path);
	scenes[id] = scene;
}
void CGame::Load(LPSTR gamePath)
{
	DebugOut(L"[INFO] Start loading game file : %s\n", gamePath);

	ifstream f;
	f.open(gamePath);
	char str[MAX_LINE];

	// current resource section flag
	int section = GAME_FILE_SECTION_UNKNOWN;
	while (f.getline(str, MAX_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") { section = GAME_FILE_SECTION_SETTINGS; continue; }
		if (line == "[SCENES]") { section = GAME_FILE_SECTION_SCENES; continue; }
		if (line[0] == '[')
		{
			section = GAME_FILE_SECTION_UNKNOWN;
			DebugOut(L"[ERROR] Unknown section: %s\n", ToLPCWSTR(line));
			continue;
		}

		//
		// data section
		//
		switch (section)
		{
		case GAME_FILE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		case GAME_FILE_SECTION_SCENES: _ParseSection_SCENES(line); break;
		}
	}
	f.close();

	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n", gamePath);

	SwitchScene();
}
void CGame::SwitchScene()
{
	if (next_scene < 0 || next_scene == current_scene) return;

	DebugOut(L"[INFO] Switching to scene %d\n", next_scene);
	Vec2 speed = Vec2(0, 0);
	Cplayscene* playscene = (Cplayscene*)scenes[current_scene];
	if (current_scene>=0)
	{
		if (playscene->isHavePlayer())
		{
			Cplayscene* playscene = (Cplayscene*)scenes[current_scene];
			speed = playscene->GetSpeedPlayer();
			scenes[current_scene]->UnLoad();
		}
	}

	current_scene = next_scene;
	if (current_scene >= 10)
		Camera->SetCamPosition(Vec2(0, WINDOW_HEIGHT));
	else Camera->SetCamPosition(Vec2(0, WINDOW_HEIGHT + 100));
	Camera->SetSceneStart(Vec2(0, 0));
	Cplayscene* s = (Cplayscene*)scenes[current_scene];
	if (current_scene == 3)
	{
		DebugOut(L"\n");
	}
	s->Load();
	if(speed != Vec2(0,0))
		s->SetSpeedPlayer(speed);
}
void CGame::SetNextScene(int nextScene)
{
	this->next_scene = nextScene;
}

void CGame::SetNextScene()
{
	Cplayscene* playscene = (Cplayscene*)scenes[current_scene];
	next_scene = playscene->GetIDNextScene();
}

CGame* CGame::GetInstance()
{
	if (_Instance == NULL) 
		_Instance = new CGame();
	return _Instance;
}

LPSCENE CGame::GetcurrentScene()
{
	return scenes[current_scene];
}

void CGame::AddObjectsToCurrrentScene(int ObjectID, LPCGameObject obj)
{
	scenes[current_scene]->AddObject(ObjectID, obj);
}




