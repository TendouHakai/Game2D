#include "CGraphic.h"

CGraphic* CGraphic::_Instance = NULL;

CGraphic::CGraphic(HWND hwnd, int W, int H)
{
	this->hWnd = hwnd;
	this->Width = W;
	this->Height = H;
	this->d3d = NULL;
	this->d3ddev = NULL;
	this->d3dxSprite = NULL;

	_Instance = this;
}

CGraphic::CGraphic()
{
}

bool CGraphic::InitD3D()
{
	//tao mot doi tuong Direct3D
	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!this->d3d)
		return false;
	//tao thiet bi ve
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferWidth = this->Width;
	d3dpp.BackBufferHeight = this->Height;
	d3dpp.hDeviceWindow = this->hWnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;
	HRESULT hr = this->d3d->CreateDevice(D3DADAPTER_DEFAULT,//chon thiet bi ve mac dinh
		D3DDEVTYPE_HAL,//su dung ho tro cua phan cung
		this->hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&this->d3ddev);
	if (FAILED(hr))
	{
		return false;
	}
	hr = D3DXCreateSprite(this->d3ddev, &this->d3dxSprite);
	if (FAILED(hr))
		return false;
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	return true;
}

CGraphic::~CGraphic(void)
{
}

void CGraphic::Begin()
{
	//MAC DINH LA MAU TRANG
	d3ddev->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(255, 255, 255));
	this->d3ddev->BeginScene();
	this->d3dxSprite->Begin(D3DXSPRITE_ALPHABLEND);
}
void CGraphic::End()
{
	this->d3dxSprite->End();
	this->d3ddev->EndScene();
	this->d3ddev->Present(NULL, NULL, NULL, NULL);
}

PDIRECT3DSURFACE9 CGraphic::Loadsurface(LPSTR filePath, D3DCOLOR transcolor)
{
	LPDIRECT3DSURFACE9 image = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result;
	result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
		return NULL;
	result = d3ddev->CreateOffscreenPlainSurface(
		info.Width, //width of the surface
		info.Height, //height of the surface
		D3DFMT_X8R8G8B8, //surface format
		D3DPOOL_DEFAULT, //memory pool to use
		&image, //pointer to the surface
		NULL); //reserved (always NULL)
	if (result != D3D_OK)
		return NULL;
	//load surface from file into newly created surface
	result = D3DXLoadSurfaceFromFile(
		image,
		NULL,
		NULL,
		filePath,
		NULL,
		D3DX_DEFAULT,
		transcolor,
		NULL);
	if (result != D3D_OK)
		return NULL;
	return image;
}

void CGraphic::DrawSurface(LPDIRECT3DSURFACE9 surface, RECT* rectSource, RECT* rectDestination)
{
	d3ddev->StretchRect(surface, rectSource, backbuffer, rectDestination, D3DTEXF_NONE);
}

void CGraphic::DrawTexture(LPDIRECT3DTEXTURE9 texture, Vec2 postion, D3DCOLOR color)
{

	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, 2.0f, 2.0f, .0f);
	d3dxSprite->SetTransform(&matScale);

	D3DXVECTOR3 p(postion.x, postion.y, 0);
	this->d3dxSprite->Draw(texture, NULL, NULL, &p, color);
}

void CGraphic::DrawTexture(LPDIRECT3DTEXTURE9 texture, RECT source, Vec2 postion, D3DCOLOR color)
{

	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, 2.0f, 2.0f, .0f);
	d3dxSprite->SetTransform(&matScale);

	D3DXVECTOR3 p(postion.x, postion.y, .0f);
	this->d3dxSprite->Draw(texture, &source, NULL, &p, color);
}

bool CGraphic::Collision(RECT rect1, RECT rect2)
{
	RECT dest;

	return IntersectRect(&dest, &rect2, &rect2);
}

LPDIRECT3DDEVICE9 CGraphic::GetDevice()
{
	return this->d3ddev;
}

CGraphic* CGraphic::GetInstance()
{
	if (_Instance == NULL)
	{
		_Instance = new CGraphic();
	}
	return _Instance;
}

