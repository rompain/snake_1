#include "winmain.h"

#include "Game.h"
#include "shared\Drawer.h"

extern deque <BLOCK> snake;
extern BLOCK food;
extern LPBYTE lpBits;

deque <BLOCK>::iterator sn_pos;

extern int score;

void DrawSnakeAndFood(HWND hWnd, HDC hdc, RECT rectBoundary) {
	HDC  hMemDC;
	HBITMAP hbmp;
	BITMAPINFO bif;
	HBITMAP bm;

	bif.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bif.bmiHeader.biBitCount = 32;
	bif.bmiHeader.biWidth = WINDOW_WIDTH;
	bif.bmiHeader.biPlanes = 1;
	bif.bmiHeader.biHeight = -WINDOW_HEIGHT;
	bif.bmiHeader.biCompression = BI_RGB; 

	Drawer drawer(WINDOW_WIDTH);

	drawer.setColor(170, 202, 136);
	drawer.Rectangle(lpBits, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	drawer.setColor(54, 56, 27);
	drawer.Rectangle(lpBits, rectBoundary.left - 1, rectBoundary.top - 1, rectBoundary.right + 1, rectBoundary.bottom + 1);

	drawer.setColor(142, 179, 103);
	drawer.Rectangle(lpBits, rectBoundary.left, rectBoundary.top, rectBoundary.right, rectBoundary.bottom);

	drawer.setColor(154, 0, 0);
	drawer.Ellipse(lpBits, food.x * SNAKE_CELL_SIZE + BORDER,
		food.y * SNAKE_CELL_SIZE + BORDER,
		(food.x + 1)*SNAKE_CELL_SIZE + BORDER,
		(food.y + 1)*SNAKE_CELL_SIZE + BORDER);

	drawer.setColor(54, 56, 27);
	for (sn_pos = snake.begin(); sn_pos != snake.end(); sn_pos++)
	{
		BLOCK p = *sn_pos;
		drawer.Ellipse(lpBits,
			p.x * SNAKE_CELL_SIZE + BORDER,
			p.y * SNAKE_CELL_SIZE + BORDER,
			(p.x + 1)*SNAKE_CELL_SIZE + BORDER,
			(p.y + 1)*SNAKE_CELL_SIZE + BORDER);
	}

	SetDIBitsToDevice(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0, WINDOW_HEIGHT, lpBits, &bif, DIB_RGB_COLORS);
}
