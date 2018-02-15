#ifndef _winmain_cpp
#define _winmain_cpp
#define TIMER_ID 1

#include "winmain.h"
#include "Game.h"

LPBYTE lpBits;
RECT rectBoundary;
extern int score;
extern deque <BLOCK> snake;
int moveResult;


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmd,
	int nCmdShow)
{
	MSG msg;
	HWND hWnd;
	WNDCLASS WndClass;

	WndClass.style = NULL;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = NULL;
	WndClass.lpszMenuName = TEXT("SNAKEMENU");
	WndClass.lpszClassName = TEXT("Snake");
	if (!RegisterClass(&WndClass)) return 0;

	int window_x = (GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2;
	int window_y = (GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2;

	hWnd = CreateWindow(TEXT("Snake"),
		TEXT("Snake GDI"),
		WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
		window_x, window_y, WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hWnd) return NULL; 
	ShowWindow(hWnd, nCmdShow); 
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	tagPAINTSTRUCT ps;
	HFONT hFont;

	switch (message) 
	{
	case WM_CREATE:
		lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, WINDOW_HEIGHT*WINDOW_WIDTH * 4);
		SetTimer(hWnd, TIMER_ID, 250, (TIMERPROC)NULL);
		InitSnake();
		SpawnFood();
		rectBoundary.left = BORDER;
		rectBoundary.top = BORDER;
		rectBoundary.right = BORDER + SNAKE_CELL_SIZE*(CELLS_X + 1);
		rectBoundary.bottom = BORDER + SNAKE_CELL_SIZE*(CELLS_Y + 1);

		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		DrawSnakeAndFood(hWnd, hdc, rectBoundary);
		hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Courier"));
		SelectObject(hdc, hFont);
		SetTextColor(hdc, RGB(44, 46, 27));
		SetBkColor(hdc, RGB(170, 202, 136));

		char buf[30];
		wsprintf((LPWSTR)buf, L"Score: %d", score);
		TextOut(hdc, (rectBoundary.left), rectBoundary.bottom + BORDER,
			(LPWSTR)buf, lstrlen((LPWSTR)buf));

		EndPaint(hWnd, &ps);
		break;

	case WM_TIMER:
		moveResult = SnakeMove();
		if (moveResult == -1)
		{
			KillTimer(hWnd, TIMER_ID);
			MessageBox(0, L"Game Over", L"Game Over", 0);
			ExitProcess(0);
		}

		if (moveResult == 1) {
			KillTimer(hWnd, TIMER_ID);
			SetTimer(hWnd, TIMER_ID, 200, (TIMERPROC)NULL);
		}


		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		break;
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_LEFT:
			SetDirection(SNAKE_LEFT);
			break;
		case VK_RIGHT:
			SetDirection(SNAKE_RIGHT);
			break;
		case VK_UP:
			SetDirection(SNAKE_UP);
			break;
		case VK_DOWN:
			SetDirection(SNAKE_DOWN);
			break;
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0); 
		break;
	default: return DefWindowProc(hWnd, 
		message,
		wParam,
		lParam);
	}
	return 0L;
}

#endif