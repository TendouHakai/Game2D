#pragma once
#include"Transform.h"
class CCamera
{
	static CCamera* _Instance;

	Vec2 Cam_Position;
	Vec2 Cam_Size;

public:

	CCamera() { Cam_Position = Vec2(0,0); };
	CCamera(Vec2 posi, Vec2 size);

	Vec2 GetCamPosition();
	void SetCamPosition(Vec2 posi);
	void setCamSize(Vec2 Size);

	void SetCamFollow(Vec2 posi, int w, int h);

	Vec2 GetCamSize();

	bool IsFollow();

	Vec2 TransForm(Vec2 Position);

	RECT getBoundingBox();

	static CCamera* GetInstance();

	~CCamera();
};

