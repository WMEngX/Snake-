#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include "Game.h"
#include "UI.h"

enum ExitStatus
{
	QUIT,
	KILLED_BY_WALL,
	KILLED_BY_SELF
};

static void SetPos(int x, int y)// �ƶ���굽x��y����ע�⣬���������������Ļ�ģ���������Ϸ�����
{
	COORD point = { x, y };
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(HOutput, point);
}

static void CoordinatePosAtXY(const struct UI *pUI, int x, int y)
{
	SetPos(pUI->marginLeft + (1 + x) * pUI->blockWidth,
		pUI->marginTop + 1 + y);
}

static void ResetCursorPosition(const struct UI *pUI)
{
	SetPos(0, pUI->windowHeight - 1);
}

static void InitializeSnake(struct Snake *pSnake);// ��ʼ���߽ṹ��

static bool IsOverlapSnake(int x, int y, const struct Snake *pSnake);// �ж�ʳ�������Ƿ�������ص�

static void GenerateFood(struct Game *pGame);// ����һ��ʳ��

static struct Position GetNextPosition(const struct Snake *pSnake);// ��ȡ�߼������������

static bool IsWillEatFood(struct Point NextPoint, struct Point FoodPoint);// �ж����Ƿ񽫳Ե�ʳ��

static void GrowSnakeAndDisplay(struct Snake *pSnake, struct Point FoodPoint, const struct UI *pUI);// �����߲��ҽ�����ʾ

static void AddHead(struct Snake *pSnake, struct Point NextPoint, const struct UI *pUI);// ������ͷ

static void RemoveTail(struct Snake *pSnake, const struct UI *pUI);// ɾ����β

static void MoveSnakeAndDisplay(struct Snake *pSnake, struct Point NextPoint, const struct UI *pUI);// �ƶ��߲��ҽ�����ʾ

static bool IsKilledByWall(const struct Node *pHead, int width, int height);// ���Ƿ�ײǽ��

static bool IsKilledBySelf(const struct Node *pHead, const struct Snake *pSnake);// ���Ƿ�ײ�Լ���

static bool IsSnakeAlive(const struct Game *pGame, enum ExitStatus *exitStatus);// ���Ƿ���

static void HandleDirective(struct Game *pGame);// ������ָ��

static void DisplaySnake(const struct UI *pUI, const struct Snake *pSnake);// ��ʾ��������

static void _Pause();// ��ͣ


void CleanBodyColor(const struct UI *pUI, struct Game *pGame)//�����������ɫ
{
	UICleanBlockAtXY(pUI, pGame->Foodposition.x, pGame->Foodposition.y);
	CoordinatePosAtXY(pUI, pGame->Foodposition.x, pGame->Foodposition.y);
	printf(pUI->snakeBlock);
	ResetCursorPosition(pUI);
}


static void InitializeSnake(struct Snake *pSnake)//��ʼ���ߵĽṹ��
{
	const int length = 3;
	const int x = 5;
	const int y = 5;
	int i;
	struct Node *pNode;

	pSnake->direction = RIGHT;
	pSnake->pBody = NULL;

	for (i = 0; i < length; i++)
	{
		pNode = (struct Node *)malloc(sizeof(struct Node));
		pNode->position.x = x + i;
		pNode->position.y = y;
		pNode->pNext = pSnake->pBody;
		pSnake->pBody = pNode;
	}
}

static bool IsOverlapSnake(int x, int y, const struct Snake *pSnake)// �ж�ʳ�������Ƿ�������ص�
{
	struct Node *pNode;

	for (pNode = pSnake->pBody; pNode != NULL; pNode = pNode->pNext)
	{
		if (pNode->position.x == x && pNode->position.y == y)
		{
			return true;
		}
	}

	return false;
}

static void GenerateFood(struct Game *pGame)// ����һ��ʳ��
{
	int x, y;

	do
	{
		x = rand() % (pGame->Width - 2);
		y = rand() % (pGame->Height - 2);
	} while (IsOverlapSnake(x, y, &pGame->snake));

	pGame->Foodposition.x = x;
	pGame->Foodposition.y = y;
}

static struct Position GetNextPosition(const struct Snake *pSnake)// ��ȡ�߼������������
{
	int nextX, nextY;

	nextX = pSnake->pBody->position.x;
	nextY = pSnake->pBody->position.y;

	switch (pSnake->direction)
	{
	case UP:
		nextY -= 1;
		break;
	case DOWN:
		nextY += 1;
		break;
	case LEFT:
		nextX -= 1;
		break;
	case RIGHT:
		nextX += 1;
		break;
	}

	struct Position position =
	{
		.x = nextX,
		.y = nextY
	};

	return position;
}

static bool IsWillEatFood(struct Position NextPoint, struct Position FoodPoint)// �ж����Ƿ񽫳Ե�ʳ��
{
	return NextPoint.x == FoodPoint.x && NextPoint.y == FoodPoint.y;
}

static void GrowSnakeAndDisplay(struct Snake *pSnake, struct Position FoodPoint, const struct UI *pUI)// �����߲��ҽ�����ʾ
{
	struct Node *pHead = (struct Node *)malloc(sizeof(struct Node));
	pHead->position.x = FoodPoint.x;
	pHead->position.y = FoodPoint.y;

	pHead->pNext = pSnake->pBody;
	pSnake->pBody = pHead;

	UIShowSnakeBlockAtXY(pUI, FoodPoint.x, FoodPoint.y);
}

static void AddHead(struct Snake *pSnake, struct Position NextPoint, const struct UI *pUI)// ������ͷ
{
	struct Node *pNode = (struct Node *)malloc(sizeof(struct Node));

	pNode->position.x = NextPoint.x;
	pNode->position.y = NextPoint.y;
	pNode->pNext = pSnake->pBody;

	pSnake->pBody = pNode;

	UIShowSnakeBlockAtXY(pUI, NextPoint.x, NextPoint.y);
}

static void RemoveTail(struct Snake *pSnake, const struct UI *pUI)// ɾ����β
{
	struct Node *pNode = pSnake->pBody;

	while (pNode->pNext->pNext != NULL)
	{
		pNode = pNode->pNext;
	}

	UICleanBlockAtXY(pUI, pNode->pNext->position.x, pNode->pNext->position.y);

	free(pNode->pNext);
	pNode->pNext = NULL;
}

static void MoveSnakeAndDisplay(struct Snake *pSnake, struct Position NextPoint, const struct UI *pUI)// �ƶ��߲��ҽ�����ʾ
{
	RemoveTail(pSnake, pUI);
	AddHead(pSnake, NextPoint, pUI);
}

static bool IsKilledByWall(const struct Node *pHead, int width, int height)// ���Ƿ�ײǽ��
{
	if (pHead->position.x < 0 || pHead->position.x >= width - 1)
	{
		return true;
	}

	if (pHead->position.y < 0 || pHead->position.y >= height - 1)
	{
		return true;
	}

	return false;
}

static bool IsKilledBySelf(const struct Node *pHead, const struct Snake *pSnake)// ���Ƿ�ײ�Լ���
{
	struct Node *pNode;


	for (pNode = pSnake->pBody->pNext; pNode != NULL; pNode = pNode->pNext)
	{
		if (pHead->position.x == pNode->position.x && pHead->position.y == pNode->position.y)
		{
			return true;
		}
	}

	return false;
}

static bool IsSnakeAlive(const struct Game *pGame, enum ExitStatus *exitStatus)// ���Ƿ���
{
	struct Node *pHead = pGame->snake.pBody;

	if (IsKilledByWall(pHead, pGame->Width, pGame->Height))
	{
		*exitStatus = KILLED_BY_WALL;
		return false;
	}

	if (IsKilledBySelf(pHead, &pGame->snake))
	{
		*exitStatus = KILLED_BY_SELF;
		return false;
	}

	return true;
}

static void HandleDirective(struct Game *pGame)// ������ָ��
{
	if (GetAsyncKeyState(VK_UP) && pGame->snake.direction != DOWN) {
		pGame->snake.direction = UP;
	}
	else if (GetAsyncKeyState(VK_DOWN) && pGame->snake.direction != UP) {
		pGame->snake.direction = DOWN;
	}
	else if (GetAsyncKeyState(VK_LEFT) && pGame->snake.direction != RIGHT) {
		pGame->snake.direction = LEFT;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && pGame->snake.direction != LEFT) {
		pGame->snake.direction = RIGHT;
	}
}

static void DisplaySnake(const struct UI *pUI, const struct Snake *pSnake)// ��ʾ��������
{
	struct Node *pNode;

	if (pSnake->pBody == NULL) {
		return;
	}

	for (pNode = pSnake->pBody; pNode != NULL; pNode = pNode->pNext)
	{
		UIShowSnakeBlockAtXY(pUI, pNode->position.x, pNode->position.y);
	}
}

struct Game * CreateGame()
{
	struct Game *pGame = (struct Game *)malloc(sizeof(struct Game));
	pGame->Width = 29;
	pGame->Height = 27;
	pGame->Score = 0;
	pGame->ScorePerFood = 10;


	InitializeSnake(&pGame->snake);
	GenerateFood(pGame);

	return pGame;
}

void StartGame(struct Game *pGame)
{

	struct UI *pUI = UIInit(pGame->Width, pGame->Height);
	enum ExitStatus exitStatus = QUIT;
	int time = 300;

	UIShowWelcome(pUI);
	UIShowGameWindow(pUI, pGame->Score, pGame->ScorePerFood);
	DisplaySnake(pUI, &pGame->snake);
	UIShowFoodAtXY(pUI, pGame->Foodposition.x, pGame->Foodposition.y);


	while (1)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}
		else if (GetAsyncKeyState(VK_SPACE))
		{
			_Pause();
		}
		HandleDirective(pGame);// ������ָ��
		struct Position NextPoint = GetNextPosition(&pGame->snake);

		if (IsWillEatFood(NextPoint, pGame->Foodposition)) {
			pGame->Score += pGame->ScorePerFood;
			UIShowScore(pUI, pGame->Score, pGame->ScorePerFood);
			GrowSnakeAndDisplay(&pGame->snake, pGame->Foodposition, pUI);
			CleanBodyColor(pUI, pGame);

			GenerateFood(pGame);

			UIShowFoodAtXY(pUI, pGame->Foodposition.x, pGame->Foodposition.y);
		}
		else {
			MoveSnakeAndDisplay(&pGame->snake, NextPoint, pUI);
		}

		if (!IsSnakeAlive(pGame, &exitStatus)) {
			break;
		}
		if (GetAsyncKeyState(VK_F1))
		{
			if (pGame->ScorePerFood < 60)
			{
				pGame->ScorePerFood = pGame->ScorePerFood + 10;
				time = time - 50;
				UIShowScore(pUI, pGame->Score, pGame->ScorePerFood);//��ʱ���µ����÷�
			}
		}
		if (GetAsyncKeyState(VK_F2))
		{
			if (pGame->ScorePerFood > 10)
			{
				pGame->ScorePerFood = pGame->ScorePerFood - 10;
				time = time + 50;
				UIShowScore(pUI, pGame->Score, pGame->ScorePerFood);//��ʱ���µ����÷�
			}
		}

		Sleep(time);
	}

	char *messages[3];
	messages[QUIT] = "��Ϸ����";
	messages[KILLED_BY_WALL] = "��Ϸ������ײ��ǽ��";
	messages[KILLED_BY_SELF] = "��Ϸ������ײ���Լ���";
	UIShowMessage(pUI, messages[exitStatus]);

	UIDestory(pUI);
}

void DestroyGame(struct Game *pGame)
{
	struct Node *pNode, *pNext;

	for (pNode = pGame->snake.pBody; pNode != NULL; pNode = pNext)
	{
		pNext = pNode->pNext;
		free(pNode);
	}
	free(pGame);
}


static void _Pause()
{
	while (1)
	{
		Sleep(300);
		if (GetAsyncKeyState(VK_SPACE))
		{
			break;
		}
	}
}
