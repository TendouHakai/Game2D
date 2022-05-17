#pragma once
#include <math.h>
#include"Transform.h"
#define CAM_SPEED_X 0.2f
class CCamera
{
	static CCamera* _Instance;

	Vec2 Cam_Position;
	Vec2 Cam_Size;

	float xSceneStart;
	float ySceneStart;
	Vec2 directChanging;
	bool IsChanging;
public:

	CCamera() { Cam_Position = Vec2(0, 0); this->xSceneStart = this->ySceneStart = 0; this->IsChanging = false; this->directChanging = Vec2(0, 0); };
	CCamera(Vec2 posi, Vec2 size);

	Vec2 GetCamPosition();
	void SetCamPosition(Vec2 posi);
	void setCamSize(Vec2 Size);

	void SetCamFollow(Vec2 posi, int wMap);
	void SetCamFollow2(Vec2 posi, int wMap);
	void SetSceneStart(Vec2 sceneStart);
	Vec2 GetSceneStart();
	Vec2 GetCamSize();
	void Update(DWORD dt, Vec2 position, int wMap, bool IsInWater);

	bool IsFollow();

	Vec2 TransForm(Vec2 Position);

	RECT getBoundingBox();

	static CCamera* GetInstance();

	~CCamera();
};

