#pragma once

#ifndef _GAME_H_
#define _GAME_H_
#include "Snake.h"

// ��������ʼ����Ϸ
struct Game * CreateGame();
// ��ʼ��Ϸ
void StartGame(struct Game *pGame);
// ������Ϸ��Դ
void DestroyGame(struct Game *pGame);

#endif
