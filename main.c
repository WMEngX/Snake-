#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"UI.h"
#include"Game.h"

int main()
{
	srand((unsigned int)time(NULL));// ���ݵ�ǰʱ��������������
	struct Game *pGame = CreateGame();
	StartGame(pGame);
	DestroyGame(pGame);
	system("pause");
	return 0;
}