#include "CHuge_Hermit.h"

void CHuge_Hermit::Update(DWORD dt, vector<LPCGameObject>* coObjects)
{
}

void CHuge_Hermit::Render()
{
	DrawAnimation();
}

void CHuge_Hermit::DrawAnimation()
{
	switch (States)
	{
	case CHuge_Hermit_States::IDLE:
		CAnimationManager::GetInstance()->Get("Huge_Hermit_walk").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
		break;
	case CHuge_Hermit_States::Walk:
		CAnimationManager::GetInstance()->Get("Huge_Hermit_walk").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
		break;
	case CHuge_Hermit_States::Run:
		CAnimationManager::GetInstance()->Get("Huge_Hermit_walk").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
		break;
	case CHuge_Hermit_States::Deploying:
		CAnimationManager::GetInstance()->Get("Huge_Hermit_deploy_cannon").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
		break;
	case CHuge_Hermit_States::Deployed:
		CAnimationManager::GetInstance()->Get("Huge_Hermit_walk_cannon").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
		break;
	case CHuge_Hermit_States::UnDeploying:
		CAnimationManager::GetInstance()->Get("Huge_Hermit_undeploy_cannon").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
		break;
	case CHuge_Hermit_States::Cannon_firing:
		CAnimationManager::GetInstance()->Get("Huge_Hermit_firing_cannon").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
		break;
	case CHuge_Hermit_States::Firing:
		CAnimationManager::GetInstance()->Get("Huge_Hermit_firing").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
		break;
	case CHuge_Hermit_States::Dead:
		CAnimationManager::GetInstance()->Get("Huge_Hermit_destroyded").get()->Render(Obj_Position, D3DCOLOR_XRGB(255, 255, 255), isLeftSize, Obj_Size, Vec2(0, 0));
		break;
	default:
		break;
	}
}
