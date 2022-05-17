#include "CAnimation.h"



CAnimation::CAnimation(int defaultFrameTime)
{
	this->defaultFrameTime = defaultFrameTime;
	this->playScale = 1.0f;
	this->lastFrameTime = 0;
	this->currentFrame = 0;
	this->frames.clear();
}

CAnimation::CAnimation(CAnimation* origin) : CAnimation(origin->defaultFrameTime)
{
	this->frames = vector<CAnimationFrame*>(origin->frames);
	this->lastFrameTime = origin->lastFrameTime;
	this->currentFrame = origin->currentFrame;
	this->defaultFrameTime = origin->defaultFrameTime;
	this->playScale = origin->playScale;
}

void CAnimation::AddFrame(Sprite sprite, DWORD frameTime)
{
	frameTime = frameTime == 0 ? defaultFrameTime : frameTime;
	CAnimationFrame* frame = new CAnimationFrame(sprite, frameTime);
	totalAniTime += frameTime;
	this->frames.push_back(frame);
}

void CAnimation::Render(Vec2 vec2,D3DCOLOR overlay, bool flag,Vec2 size, Vec2 translate, DWORD dt)
{
	
	int currentFrame2 = dt / frames[currentFrame]->GetTime();

	currentFrame2 = currentFrame2 % frames.size();

	frames[currentFrame2]->GetSprite()->Draw(vec2, overlay,flag,size, translate);
}

void CAnimation::Render(Vec2 vec2, D3DCOLOR overlay, bool flag, Vec2 size, Vec2 translate)
{
	DWORD now = GetTickCount64();

	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if ((now - lastFrameTime) * playScale > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}
	}
	frames[currentFrame]->GetSprite()->Draw(vec2, overlay, flag, size, translate);
}


CAnimation::~CAnimation()
{
	//delete this->transform;
}

shared_ptr<CAnimation> CAnimation::Clone()
{
	return make_shared<CAnimation>(this);
}
