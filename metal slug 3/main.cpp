#include "CGame.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;
	CGame Game(hInstance, WINDOW_WIDTH, WINDOW_HEIGHT, FRAME_RATE, true);
	Game.GameInit();
	ZeroMemory(&msg, sizeof(msg));
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Game.GameRun();
	}
	Game.GameEnd();
	return 0;
}