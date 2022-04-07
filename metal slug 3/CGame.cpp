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
	

	scene = new Cplayscene(01,(LPSTR)"scene1.txt", Marco);
	scene->Load();
	LoadResource();
	//LoadGameObject();
}

void CGame::GameRun()
{	
	
	Graphic->Begin();

	/*Marco->Update(count_per_frame);

	Camera->SetCamFollow(Marco->GetPosition());
	Marco->Render();
	for (int i = 0; i < GameObject.size(); i++)
	{
		GameObject[i]->Update(count_per_frame);
		GameObject[i]->Render();
	}*/
	scene->Update(count_per_frame);
	scene->Render();
	Graphic->End();
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

//void CGame::LoadGameObject()
//{
//	CChowmein* chowmein = new CChowmein(Vec2(100, 100));
//	chowmein->SetState(CChowmein_States::Walk);
//	GameObject.push_back(chowmein);
//
//	chowmein = new CChowmein(Vec2(200, 200));
//	chowmein->SetState(CChowmein_States::IDLE);
//	GameObject.push_back(chowmein);
//
//	chowmein = new CChowmein(Vec2(300, 300));
//	chowmein->SetState(CChowmein_States::MeleeAttack);
//	GameObject.push_back(chowmein);
//
//	 chowmein = new CChowmein(Vec2(400, 400));
//	chowmein->SetState(CChowmein_States::RangeAttack);
//	GameObject.push_back(chowmein);
//
//	chowmein = new CChowmein(Vec2(500, 500));
//	chowmein->SetState(CChowmein_States::Dead);
//	GameObject.push_back(chowmein);
//
//	CLocust* Locust = new CLocust(Vec2(200, 100));
//	Locust->SetState(Locust_states::attack);
//	GameObject.push_back(Locust);
//
//	Locust = new CLocust(Vec2(300, 200));
//	Locust->SetState(Locust_states::preattack);
//	GameObject.push_back(Locust);
//
//	Locust = new CLocust(Vec2(400, 300));
//	Locust->SetState(Locust_states::flying);
//	GameObject.push_back(Locust);
//
//	Locust = new CLocust(Vec2(500, 400));
//	Locust->SetState(Locust_states::turn);
//	GameObject.push_back(Locust);
//
//	Flying_Killer* Flying_killer = new Flying_Killer(Vec2(300, 0));
//	GameObject.push_back(Flying_killer);
//}

CGame* CGame::GetInstance()
{
	if (_Instance == NULL) 
		_Instance = new CGame();
	return _Instance;
}




