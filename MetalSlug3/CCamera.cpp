#include "CCamera.h"

CCamera* CCamera::_Instance = NULL;

CCamera::CCamera(Vec2 posi, Vec2 size)
{
    Cam_Position = posi;
    Cam_Size = size;
    this->xSceneStart = 0;
    this->ySceneStart = 0;
    this->directChanging = Vec2(0, 0);
    this->IsChanging = false;
    _Instance = this;
}

Vec2 CCamera::GetCamPosition()
{
    return Cam_Position;
}

void CCamera::SetCamPosition(Vec2 posi)
{
    Cam_Position = posi;
}

void CCamera::setCamSize(Vec2 Size)
{
    this->Cam_Size = Size;
}

void CCamera::SetCamFollow(Vec2 posi, int wMap)
{
    Cam_Position.x = posi.x - WINDOW_WIDTH *1 / 3;
    //Cam_Position.y = posi.y + (WINDOW_HEIGHT / 3) * 2 -70;
    if (Cam_Position.x <= xSceneStart)
        Cam_Position.x = xSceneStart;
    else if (Cam_Position.x + WINDOW_WIDTH >= wMap)
        Cam_Position.x = wMap - WINDOW_WIDTH;
}

void CCamera::SetCamFollow2(Vec2 posi, int wMap)
{
    Cam_Position.y = posi.y + WINDOW_HEIGHT / 2;
    if (Cam_Position.x <= xSceneStart)
        Cam_Position.x = xSceneStart;
    else if (Cam_Position.x + WINDOW_WIDTH >= wMap)
        Cam_Position.x = wMap - WINDOW_WIDTH;
}

void CCamera::SetSceneStart(Vec2 sceneStart)
{
    this->xSceneStart = sceneStart.x;
    this->ySceneStart = sceneStart.y;
    float x = (xSceneStart - Cam_Position.x) / (ySceneStart - Cam_Position.y);
    if ((ySceneStart - Cam_Position.y)>0)
        directChanging = Vec2(x, 1);
    else directChanging = Vec2(fabs(x), -1);
    if((xSceneStart - Cam_Position.x)>0)
        IsChanging = true; 
}

Vec2 CCamera::GetSceneStart()
{
    return Vec2(xSceneStart, ySceneStart);
}

Vec2 CCamera::GetCamSize()
{
    return Cam_Size;
}

void CCamera::Update(DWORD dt, Vec2 position, int wMap, bool IsInWater)
{
    if (IsChanging)
    {
        if (xSceneStart - Cam_Position.x > 0)
        {
            this->Cam_Position.x += CAM_SPEED_X *dt;
            float vy = CAM_SPEED_X * directChanging.y / directChanging.x;
            this->Cam_Position.y += vy * dt;
        }
        else
        {
            this->Cam_Position.y = ySceneStart;
            IsChanging = false;
        }
    }
    else
    {
        if (IsInWater)
            SetCamFollow2(position, wMap);
        else SetCamFollow(position, wMap);
    }
}

Vec2 CCamera::TransForm(Vec2 Position)
{
    return Vec2(( - Cam_Position.x+Position.x)/2,(Cam_Position.y - Position.y)/2);
}

RECT CCamera::getBoundingBox()
{
    RECT rect;
    rect.left = this->Cam_Position.x;
    rect.right = rect.left + this->Cam_Size.x;
    rect.top = this->Cam_Position.y - this->Cam_Size.y;
    rect.bottom = this->Cam_Position.y;
    return rect;
}

CCamera* CCamera::GetInstance()
{
    if (_Instance == NULL)
    {
        _Instance = new CCamera();
    }
    return _Instance;
}

CCamera::~CCamera()
{
}
