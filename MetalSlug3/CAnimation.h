#pragma once
#include"CAnimationFrame.h"
#include"Transform.h"
#include<vector>
#include<memory>

class CAnimation
{
	DWORD lastFrameTime;
	int currentFrame;
	int defaultFrameTime;

	int totalAniTime = 0;

	float playScale;

	vector<CAnimationFrame*> frames;

public:
	CAnimation(int defaultFrameTime = 100);
	CAnimation(CAnimation* origin);

	virtual void AddFrame(Sprite sprite, DWORD frameTime = 0);

	virtual void Render(Vec2 vec2,D3DCOLOR overlay, bool flag,Vec2 size, Vec2 translate, DWORD dt );

	virtual void Render(Vec2 vec2, D3DCOLOR overlay, bool flag, Vec2 size, Vec2 translate);

	virtual float GetPlayScale() { return this->playScale; }

	virtual void SetPlayScale(float scale) { this->playScale = scale; }

	virtual DWORD GetTotalAniTime() { return this->totalAniTime; };

	virtual shared_ptr<CAnimation> Clone();

	~CAnimation();
};

typedef shared_ptr<CAnimation> Animation;