/*#include "Food.h"
#include "winmain.h"

POSITION food;

Food::Food(void)
{
	//random_number = firs_value + rand() % last_value;
	x = 9 + rand() % 873;
	y = 9 + rand() % 646;
}

int Food::GetX()
{
	return x;
}

int Food::GetY()
{
	return y;
}

void Food::Draw(HDC hdc)
{
	SetMapMode(hdc, MM_TEXT);
	//Rectangle(hdc, 5, 5, 30, 30);
	//Rectangle(hdc, 0, 0, 900, 700);

	//Rectangle(hdc, 0, 0, 882, 9);
	//Rectangle(hdc, 0, 0, 882, 655);


	//Rectangle(hdc, 0, 18, 18, 0);
	//Rectangle(hdc, 21, 39, 39, 21);
	//Rectangle(hdc, 780, 600, 890, 690);
	Rectangle(hdc, x - 9, y - 9, x + 9, y + 9);
	//SetPolyFillMode(hdc, WINDING);
}

Food::~Food(void)
{
}*/