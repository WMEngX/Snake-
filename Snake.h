#pragma once

#ifndef _SNAKE_H_
#define _SNAKE_H_
//����
struct Position {

	int x;
	int y;
};
//���ݵĽṹ��
struct Node {

	struct Position position;
	struct Node* pNext;
};
//����
enum Direction {

	UP,
	DOWN,
	LEFT,
	RIGHT
};
//�ߵ�����
struct Snake {

	enum Direction direction;
	struct Node* pBody;
};
//��Ϸ������
struct Game {

	int Width;	
	int Height;
	int Score;
	int ScorePerFood;
	struct Snake snake;
	struct Position Foodposition;
};
#endif