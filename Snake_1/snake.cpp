#include "Snake.h"
#include <ctime>

#define INIT_LEN 5

DIRECTION snake_direction;
deque <BLOCK> snake;
BLOCK food;

int score = 0;

bool CollisionBlocks(BLOCK one, BLOCK two)
{
	if (one.x == two.x && one.y == two.y)
		return true;
	return false;
}

bool InitSnake()
{
	SetDirection(SNAKE_STOP);

	BLOCK p;
	snake.clear();
	p.x = 2; 
	p.y = 2; 

	for (int i = 0; i < INIT_LEN; i++)
	{
		snake.push_front(p);
		p.x += 1;
	}

	return true;
}


void SetDirection(DIRECTION dir)
{
	switch (snake_direction)
	{
	case SNAKE_STOP:
		if (dir == SNAKE_LEFT)
			return;
		break;
	case SNAKE_UP:
		if (dir == SNAKE_DOWN)
			return;
		break;
	case SNAKE_DOWN:
		if (dir == SNAKE_UP)
			return;
		break;
	case SNAKE_LEFT:
		if (dir == SNAKE_RIGHT)
			return;
		break;
	case SNAKE_RIGHT:
		if (dir == SNAKE_LEFT)
			return;
		break;
	}
	snake_direction = dir;
}

int SnakeMove()
{
	BLOCK headBlock;
	headBlock = snake.front();

	switch (snake_direction)
	{
	case SNAKE_STOP:
		break;
	case SNAKE_UP:
		headBlock.y -= 1;
		break;
	case SNAKE_DOWN:
		headBlock.y += 1;
		break;
	case SNAKE_LEFT:
		headBlock.x -= 1;
		break;
	case SNAKE_RIGHT:
		headBlock.x += 1;
		break;
	}
	if (snake_direction != SNAKE_STOP) {

		snake.push_front(headBlock);

		if (CollisionBlocks(headBlock, food))
		{
			score++;
			SpawnFood();
			return 1;
		}

		snake.pop_back();
		deque <BLOCK>::iterator posbody;

		for (posbody = snake.begin(), posbody++; posbody != snake.end(); posbody++)
		{
			if (CollisionBlocks(headBlock, *posbody))
			{
				return -1;
			}

		}
		return IsWallHitted(headBlock);
		return 0;
	}
}

int IsWallHitted(BLOCK positionHead)
{
	if (positionHead.x < 0 || positionHead.x > CELLS_X ||
		positionHead.y < 0 || positionHead.y > CELLS_Y)
	{
		return -1;
	}

	return 0;
}


bool SpawnFood()
{
	srand(time(0));
	food.x = 1 + rand() % CELLS_X;
	food.y = 1 + rand() % CELLS_Y;

	deque <BLOCK>::iterator posbody;
	for (posbody = snake.begin(); posbody != snake.end(); posbody++)
	{
		if (CollisionBlocks(*posbody, food))
		{
			food.x = rand() % CELLS_X;
			food.y = rand() % CELLS_Y;
			posbody = snake.begin();
		}
	}
	
	return true;
}