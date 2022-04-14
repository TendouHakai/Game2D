#include "CSprite.h"
#include "CGame.h"

CSprite::CSprite(string id, int left, int top, int width, int height, int xPivot, int yPivot, LPDIRECT3DTEXTURE9 texture)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	this->pivot = D3DXVECTOR3((float)xPivot, (float)yPivot, 0);
	this->texture = texture;
}

void CSprite::Draw(Vec2 Position, D3DCOLOR overlay, bool flag,Vec2 size, Vec2 translate)
{
	RECT r;
	r.left = this->left;
	r.top = this->top;
	r.right = this->left + this->width;
	r.bottom = this->top + this->height;

	Vec2 New_Position = CCamera::GetInstance()->TransForm(Position);

	CGraphic::GetInstance()->DrawTexture(texture, r, New_Position, overlay, flag,size, translate);
}
