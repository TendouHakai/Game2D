#include "CQuadnode.h"

bool CQuadnode::IsContain(LPCGameObject GameObjects)
{
	RECT rect;
	rect.left = ltx;
	rect.right = rbx;
	rect.top = rby;
	rect.bottom = lty;
	
    return CGraphic::GetInstance()->Collision(rect, GameObjects->getBoundingBox());
}

int CQuadnode::getWidth()
{
	return abs(rbx - ltx);
}

int CQuadnode::getHeight()
{
	return abs(lty - rby);
}

RECT CQuadnode::getBoudingBox()
{
	RECT rect;
	rect.left = ltx;
	rect.right = rbx;
	rect.top = rby;
	rect.bottom = lty;
	return rect;
}
