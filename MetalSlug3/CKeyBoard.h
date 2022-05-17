#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include "Debug.h"
#include <d3dx9.h>
#include <dinput.h>
#define KEYBOARD_BUFFER_SIZE 1024
class CKeyBoard
{
	static CKeyBoard* _Instance;

	LPDIRECTINPUT8       di;								// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;								// The keyboard device 

	BYTE  keyStates[256];									// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

public:
	CKeyBoard();

	void InitKeyboard(HWND hWnd);

	void ProcessKeyboard();

	int GetKeyboardData(DIDEVICEOBJECTDATA KeyData[KEYBOARD_BUFFER_SIZE],DWORD* dwElements);

	/*bool IsKeyDown(int keyCode);
	bool IsKeyUp(int keyCode);*/

	static CKeyBoard* GetInstance();

	~CKeyBoard();
};

