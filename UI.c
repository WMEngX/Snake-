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
	pUI->wallBlock = "��";
	pUI->foodBlock = "��";
	pUI->snakeBlock = "��";
	pUI->blockWidth = strlen(pUI->wallBlock);

	/*char WindowInit[50];
	sprintf(WindowInit, "mode con cols=%d lines=%d", pUI->windowWidth, pUI->windowHeight);
	system(WindowInit);*/
	return pUI;

}

void UIShowWelcome(const struct UI *pUI)//��ʾ��Ϸ��ӭ����
{
	int i;
	const char *Messages[3] = {
		"̰����С��Ϸ",
		"�á�.��.��.�������ߵ��ƶ��� F1Ϊ���٣�F2Ϊ���١�",
		"���ٽ��ܵõ����ߵķ�����"
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
void UIShowGameWindow(const struct UI *pUI, int score, int scorePerFood)// ��ʾǽ����Ϣ
{
	ShowWall(pUI);
	UIShowScore(pUI, score, scorePerFood);
	ShowDesc(pUI);

	ResetCursorPosition(pUI);
}
void UIShowFoodAtXY(const struct UI *pUI, int x, int y)// ��x��y����ʾʳ�x��yΪ�ַ�����
{
	CoordinatePosAtXY(pUI, x, y);
	printf(pUI->foodBlock);
	ResetCursorPosition(pUI);
}
void UIShowSnakeBlockAtXY(const struct UI *pUI, int x, int y)// ��x��y����ʾ�ߵ�һ����㣬x��yΪ�ַ�����
{
	CoordinatePosAtXY(pUI, x, y);
	printf(pUI->snakeBlock);
	ResetCursorPosition(pUI);
}
void UICleanBlockAtXY(const struct UI *pUI, int x, int y)// ���x��y������ʾ�飬x��yΪ�ַ�����
{
	CoordinatePosAtXY(pUI, x, y);
	int i;

	for (i = 0; i < pUI->blockWidth; i++) {
		printf(" ");
	}

	ResetCursorPosition(pUI);
}
void UIShowScore(const struct UI *pUI, int score, int scorePerFood)// ��ʾ������Ϣ
{
	int blockWidth = strlen(pUI->wallBlock);
	int left = pUI->marginLeft + (pUI->gameWidth + 2) * blockWidth + 2;
	SetPos(left, pUI->marginTop + 8);
	printf("�÷�: %3d��ÿ��ʳ��÷�: %3d", score, scorePerFood);

	ResetCursorPosition(pUI);
}
void UIShowMessage(const struct UI *pUI, const char *Message)// ����Ϸ���������ʾ��Ϸ�˳���Ϣ
{
	// ������� + (1(��߽������+��Ϸ����ĸ���/2) * ÿ���ַ��Ŀ��
	// - �ַ����Ŀ�� / 2
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
	//��
	for (i = 0; i <= pUI->gameWidth+1; i++)
	{
		_SetPos(pUI->marginLeft + 2 * i, pUI->marginTop);
		printf("%s", pUI->wallBlock);
		_SetPos(30, 40);
	};

   //��
	for (i = 0; i <= pUI->gameWidth+1; i++)
	{
	    _SetPos(pUI->marginLeft + 2 * i, pUI->marginTop + 1 + pUI->gameHeight);
		printf("%s", pUI->wallBlock);
		_SetPos(30, 40);

	};
	//��
	for (i = 0; i < pUI->gameHeight; i++)
	{
		_SetPos(pUI->marginLeft, pUI->marginTop + 1+ i );
		printf("%s", pUI->wallBlock);
		_SetPos(30, 40);

	};
	//��
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
		"���ܴ�ǽ������ҧ���Լ���",
		"�� �� �� �� �� �ֱ�����ߵ��ƶ���",
		"F1 Ϊ���٣�F2 Ϊ���١�",
		"ESC �˳���Ϸ�� SPACE ��ͣ��Ϸ��",
		"��Ȩ @�����2012"
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

static void CoordinatePosAtXY(const struct UI *pUI, int x, int y)// �ƶ���굽x��y����ע�⣬���������������Ļ�ģ���������Ϸ�����
{
	SetPos(pUI->marginLeft + (1 + x) * pUI->blockWidth,
		pUI->marginTop + 1 + y);
}


static void ResetCursorPosition(const struct UI *pUI)
{
	SetPos(0, pUI->windowHeight - 1);
}