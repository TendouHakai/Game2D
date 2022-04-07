#include "CCamera.h"

CCamera* CCamera::_Instance = NULL;

CCamera::CCamera(Vec2 posi, Vec2 size)
{
    Cam_Position = posi;
    Cam_Size = size;
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

void CCamera::SetCamFollow(Vec2 posi, int w, int h)
{
    Cam_Position.x = posi.x - WINDOW_WIDTH / 2;
    if (Cam_Position.x <= 0)
        Cam_Position.x = 0;
    else if (Cam_Position.y > w)
        Cam_Position.y = w;
}

Vec2 CCamera::GetCamSize()
{
    return Cam_Size;
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
