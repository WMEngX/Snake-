#pragma once

#ifndef _UI_H_
#define _UI_H_

struct UI {

	int marginTop;
	int marginLeft;//ҳ�߾ࣨ��ȣ�

	int windowWidth;
	int windowHeight;//���ڴ�С

	int gameWidth;
	int gameHeight;//��Ϸ�ڿ��ַ��ĸ���������ĸ�����

	char *snakeBlock;//�ߵķ���
	char *wallBlock;//ǽ�ķ���
	char *foodBlock;//ʳ��ķ���
	int blockWidth;//ÿ������ĳ���
};
struct UI * UIInit(int Width, int Height);//UI��ʼ��

void UIShowWelcome(const struct UI *pUI);//��ʾ��Ϸ��ӭ����

void UIShowGameWindow(const struct UI *pUI, int Score, int ScorePerFood);// ��ʾ��Ϸ���壬����ǽ���ұߵ���Ϣ���������ߺ�ʳ�����ʾ


void UIShowFoodAtXY(const struct UI *pUI, int x, int y);// ��x��y����ʾʳ�x��y�����ַ�����


void UIShowSnakeBlockAtXY(const struct UI *pUI, int x, int y);// ��x��y����ʾ�ߵ�һ����㣬x��y�����ַ�����


void UICleanBlockAtXY(const struct UI *pUI, int x, int y);// ���x��y������ʾ�飬x��y�����ַ�����


void UIShowScore(const struct UI *pUI, int score, int scorePerFood);// ��ʾ������Ϣ


void UIShowMessage(const struct UI *pUI, const char *message);// ����Ϸ���������ʾ��Ϸ�˳���Ϣ


void UIDeinitialize(struct UI *pUI);// ���� UI ��Դ

static void _SetPos(int x, int y);// �ƶ���굽x��y����ע�⣬���������������Ļ�ģ���������Ϸ�����

static void _DisplayWall(const struct UI *pUI);// ��ʾǽ


static void ShowDesc(const struct UI *pUI);// ��ʾ�Ҳ���Ϣ


static void CoordinatePosAtXY(const struct UI *pUI, int x, int y);// ����Ϸ�̵�x��y����ת��Ϊ���������Ļ��x��y��Ҳ���ǰ��ַ�����ת�������ַ����



static void ResetCursorPosition(const struct UI *pUI);// ���ù�굽��Ļ�·�����Ҫ��Ϊ����ʾ������


#endif 

