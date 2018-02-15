#ifndef DRAWING_H
#define DRAWING_H

#include <windows.h>

typedef struct {
	BYTE red;
	BYTE blue;
	BYTE green;
} COLOR;

class Drawer{
	int window_width;
	COLOR color;
public:
	Drawer(int);
	int getPos(int, int);
	void fill(LPBYTE p, int x, int y);
	void setWidth(int w);
	void setColor(int r, int g, int b);
	void setPixel(LPBYTE p, int x, int y);
	COLOR getPixel(LPBYTE p, int x, int y);
	void Ellipse(LPBYTE p, int x, int y, int endx, int endy);
	void Rectangle(LPBYTE p, int x, int y, int endx, int endy);
};

#endif
