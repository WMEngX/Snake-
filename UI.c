#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<Windows.h>
#include "UI.h"
#include"Snake.h"


struct UI * UIInit(int width, int height)
{
	int left = 2;
    int top = 2;
	int blockWidth = 2;
	int descWidth = 50;

	struct UI *pUI = (struct UI *)malloc(sizeof (struct UI));
	pUI->marginTop = top;
	pUI->marginLeft = left;
	pUI->windowWidth =  left + (width + 2) * blockWidth + descWidth;
	pUI->windowHeight = top + height + 2 + 3;
	pUI->gameWidth = width;
	pUI->gameHeight = height;
	pUI->wallBlock = "█";
	pUI->foodBlock = "█";
	pUI->snakeBlock = "█";
	pUI->blockWidth = strlen(pUI->wallBlock);

	/*char WindowInit[50];
	sprintf(WindowInit, "mode con cols=%d lines=%d", pUI->windowWidth, pUI->windowHeight);
	system(WindowInit);*/
	return pUI;

}

void UIShowWelcome(const struct UI *pUI)//显示游戏欢迎界面
{
	int i;
	const char *Messages[3] = {
		"贪吃蛇小游戏",
		"用↑.↓.←.→控制蛇的移动， F1为加速，F2为减速。",
		"加速将能得到更高的分数。"
	};

	i = 0;
	SetPos(pUI->windowWidth / 2 - strlen(Messages[i]) / 2, pUI->windowHeight / 2);
	printf("%s\n", Messages[i]);
	SetPos(pUI->windowWidth / 2 - strlen(Messages[i]) / 2, pUI->windowHeight / 2 + 2);
	system("pause");
	system("cls");

	i = 1;
	SetPos(pUI->windowWidth / 2 - strlen(Messages[i]) / 2, pUI->windowHeight / 2);
	printf("%s\n", Messages[i]);

	i = 2;
	SetPos(pUI->windowWidth / 2 - strlen(Messages[i]) / 2, pUI->windowHeight / 2 + 2);
	printf("%s\n", Messages[i]);
	SetPos(pUI->windowWidth / 2 - strlen(Messages[i]) / 2, pUI->windowHeight / 2 + 4);
	system("pause");
	system("cls");
}
void UIShowGameWindow(const struct UI *pUI, int score, int scorePerFood)// 显示墙，信息
{
	ShowWall(pUI);
	UIShowScore(pUI, score, scorePerFood);
	ShowDesc(pUI);

	ResetCursorPosition(pUI);
}
void UIShowFoodAtXY(const struct UI *pUI, int x, int y)// 在x，y处显示食物，x，y为字符个数
{
	CoordinatePosAtXY(pUI, x, y);
	printf(pUI->foodBlock);
	ResetCursorPosition(pUI);
}
void UIShowSnakeBlockAtXY(const struct UI *pUI, int x, int y)// 在x，y处显示蛇的一个结点，x，y为字符个数
{
	CoordinatePosAtXY(pUI, x, y);
	printf(pUI->snakeBlock);
	ResetCursorPosition(pUI);
}
void UICleanBlockAtXY(const struct UI *pUI, int x, int y)// 清空x，y处的显示块，x，y为字符个数
{
	CoordinatePosAtXY(pUI, x, y);
	int i;

	for (i = 0; i < pUI->blockWidth; i++) {
		printf(" ");
	}

	ResetCursorPosition(pUI);
}
void UIShowScore(const struct UI *pUI, int score, int scorePerFood)// 显示分数信息
{
	int blockWidth = strlen(pUI->wallBlock);
	int left = pUI->marginLeft + (pUI->gameWidth + 2) * blockWidth + 2;
	SetPos(left, pUI->marginTop + 8);
	printf("得分: %3d，每个食物得分: %3d", score, scorePerFood);

	ResetCursorPosition(pUI);
}
void UIShowMessage(const struct UI *pUI, const char *Message)// 在游戏区域居中显示游戏退出消息
{
	// 左填充宽度 + (1(左边界个数）+游戏区域的个数/2) * 每个字符的宽度
	// - 字符串的宽度 / 2
	SetPos(
		pUI->marginLeft + (
		(1 + pUI->gameWidth / 2) * pUI->blockWidth)
		- strlen(Message) / 2,
		pUI->marginTop + 1 + pUI->gameHeight / 2);
	printf("%s\n", Message);

	ResetCursorPosition(pUI);
}
static void _DisplayWall(const struct UI *pUI)
{
	int i;
	//上
	for (i = 0; i <= pUI->gameWidth+1; i++)
	{
		_SetPos(pUI->marginLeft + 2 * i, pUI->marginTop);
		printf("%s", pUI->wallBlock);
		_SetPos(30, 40);
	};

   //下
	for (i = 0; i <= pUI->gameWidth+1; i++)
	{
	    _SetPos(pUI->marginLeft + 2 * i, pUI->marginTop + 1 + pUI->gameHeight);
		printf("%s", pUI->wallBlock);
		_SetPos(30, 40);

	};
	//左
	for (i = 0; i < pUI->gameHeight; i++)
	{
		_SetPos(pUI->marginLeft, pUI->marginTop + 1+ i );
		printf("%s", pUI->wallBlock);
		_SetPos(30, 40);

	};
	//右
	for (i = 0; i < pUI->gameHeight; i++)
	{
		_SetPos((pUI->marginLeft + 2 + (pUI->gameWidth) * 2), pUI->marginTop +1 + i);
		printf("%s", pUI->wallBlock);
		_SetPos(30, 40);

	};
}
static void ShowDesc(const struct UI *pUI)
{
	int left = pUI->marginLeft + (pUI->gameWidth + 2) * pUI->blockWidth + 2;
	const char *Messages[] = {
		"不能穿墙，不能咬到自己。",
		"用 ↑ ↓ ← → 分别控制蛇的移动。",
		"F1 为加速，F2 为减速。",
		"ESC 退出游戏。 SPACE 暂停游戏。",
		"版权 @金翅鸟2012"
	};
	int i;

	for (i = 0; i < sizeof(Messages) / sizeof(char *); i++) {
		SetPos(left, pUI->marginTop + 10 + i);
		printf("%s\n", Messages[i]);
	}
}
static void _SetPos(int x, int y)
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };
	SetConsoleCursorPosition(hOutput,position);
	
}

void UIDeinitialize(struct UI * pUI)
{
	free(pUI);
}

static void CoordinatePosAtXY(const struct UI *pUI, int x, int y)// 移动光标到x，y处，注意，这里是相对整个屏幕的，而不是游戏区域的
{
	SetPos(pUI->marginLeft + (1 + x) * pUI->blockWidth,
		pUI->marginTop + 1 + y);
}


static void ResetCursorPosition(const struct UI *pUI)
{
	SetPos(0, pUI->windowHeight - 1);
}