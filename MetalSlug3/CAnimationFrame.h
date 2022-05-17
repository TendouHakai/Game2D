#pragma 
#include"CSprite.h"

class CAnimationFrame
{
	Sprite sprite;
	DWORD time;

public:
	CAnimationFrame(Sprite sprite, int time) { this->sprite = sprite; this->time = time; }
	virtual DWORD GetTime() { return time; }
	virtual Sprite GetSprite() { return sprite; }
};
