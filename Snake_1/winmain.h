#pragma once

#include <Windows.h>
#include "snake.h"
#include "constants.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmd,
	int nCmdShow);

