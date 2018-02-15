#pragma once
#include <vector>
#include <string>
#include <deque>
#include <iterator> 
#include <Windows.h>
#include "constants.h"

using std::deque;

enum DIRECTION
{ 
	SNAKE_STOP = 0,
	SNAKE_LEFT, 
	SNAKE_RIGHT,
	SNAKE_UP,
	SNAKE_DOWN
};

typedef struct _POSITION
{
	unsigned short x;
	unsigned short y;
} BLOCK;

bool CollisionBlocks(BLOCK one, BLOCK two);
int IsWallHitted(BLOCK a); 
void SetDirection(DIRECTION dir);
bool SpawnFood();
bool InitSnake();
int SnakeMove();