#pragma once

#ifndef _SNAKE_H_
#define _SNAKE_H_
//坐标
struct Position {

	int x;
	int y;
};
//数据的结构体
struct Node {

	struct Position position;
	struct Node* pNext;
};
//方向
enum Direction {

	UP,
	DOWN,
	LEFT,
	RIGHT
};
//蛇的数据
struct Snake {

	enum Direction direction;
	struct Node* pBody;
};
//游戏的数据
struct Game {

	int Width;	
	int Height;
	int Score;
	int ScorePerFood;
	struct Snake snake;
	struct Position Foodposition;
};
#endif