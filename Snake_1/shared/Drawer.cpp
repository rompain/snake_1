#include "Drawer.h"
#include <cmath>    


Drawer::Drawer(int width){
	this->window_width = width;
	this->color.red = 0;
	this->color.green = 0;
	this->color.blue = 0;
}

int Drawer::getPos(int x, int y){
	return (x + y * this->window_width) * 4;
}

void Drawer::setWidth(int w){
	this->window_width = w;
}


void Drawer::setColor(int r, int g, int b){
	this->color.red = r;
	this->color.green = g;
	this->color.blue = b;
}

void Drawer::setPixel(LPBYTE p, int x, int y){
	p[this->getPos(x, y)] = this->color.blue;
	p[this->getPos(x, y)+1] = this->color.green;
	p[this->getPos(x, y)+2] = this->color.red;
}

COLOR Drawer::getPixel(LPBYTE p, int x, int y){
	COLOR color;
	color.blue= p[this->getPos(x, y)];
	color.green= p[this->getPos(x, y)+1];
	color.red= p[this->getPos(x, y)+2];
	return color;
}

void Drawer::Ellipse(LPBYTE p, int x, int y, int endx, int endy){
	
	int centerx = x + (int)abs(x - endx) / 2;
	int centery = y + (int)abs(y - endy) / 2;
	
	long a2, b2, dds, ddt, dxt, t, s, e, ca, cd, indx;
	int a, b;
	a = abs(endx - centerx); b = abs(endy - centery);
	a2 = (long)a * (long)a;
	b2 = (long)b * (long)b;
	dds = 4 * a2;
	ddt = 4 * b2;
	dxt = (float)a2 / sqrt(a2 + b2) + 2;
	t = 0;
	s = -4 * a2*b;
	e = (-s / 2) - 2 * b2 - a2;
	ca = -6 * b2;
	cd = ca - 4 * a2;
	x = centerx;
	y = centery + b;
	setPixel(p, x, y);
	setPixel(p, x, 2 * centery - y);
	setPixel(p, 2 * centerx - x, 2 * centery - y);
	setPixel(p, 2 * centerx - x, y);
	for (indx = 1; indx <= dxt; indx++){
		x++;
		if (e >= 0) e += t + ca;
		else {
			y--;
			e += t - s + cd;
			s += dds;
		}
		t -= ddt;
		setPixel(p, x, y);
		setPixel(p, x, 2 * centery - y);
		setPixel(p, 2 * centerx - x, 2 * centery - y);
		setPixel(p, 2 * centerx - x, y);
	}
	dxt = abs(y - centery);
	e -= t / 2 + s / 2 + b2 + a2;
	ca = -6 * a2;
	cd = ca - 4 * b2;
	for (indx = 1; indx <= dxt; indx++){
		y--;
		if (e <= 0) e += -s + ca;
		else {
			x++;
			e += - s + t + cd;
			t -= ddt;
		}
		s += dds;
		setPixel(p, x, y);
		setPixel(p, x, 2 * centery - y);
		setPixel(p, 2 * centerx - x, 2 * centery - y);
		setPixel(p, 2 * centerx - x, y);
	}
	this->fill(p, centerx, centery);
}

void Drawer::Rectangle(LPBYTE p, int x, int y, int endx, int endy){	
	for(int x_ = x; x_ < endx; x_++){
		for(int y_ = y; y_ < endy; y_++){
			this->setPixel(p,x_,y_);
		}
	}
}

COLORREF toCR(COLOR c){
	return RGB(c.red, c.green, c.blue);
}

void Drawer::fill(LPBYTE p, int x, int y){
	COLORREF clr = toCR(getPixel(p, x, y));

	if (clr != toCR(this->color)){
		setPixel(p, x, y);
		fill(p, x + 1, y);
		fill(p, x - 1, y);
		fill(p, x, y + 1);
		fill(p, x, y - 1);
	}
}
