#pragma once
#include"d3dx9.h"
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

typedef D3DXVECTOR2 Vec2;

class CTransform
{
public:
	Vec2 Position;
	Vec2 Scale;
	float Rotation;

	CTransform() { this->Rotation = 0.0f; this->Scale = Vec2(1.0f, 1.0f); };
	CTransform(Vec2 scale, float rotation) { this->Scale = scale; this->Rotation = rotation;}

};



