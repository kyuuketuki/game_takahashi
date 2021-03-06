#pragma once
//-----------------------------------------------------------------
//
// ゲーム内容の処理 (game.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

typedef struct
{
	float X;
	float Y;
	float Z;
	float Rot;
	int Type;
}FAILDATE;

//----------------------
//プロトタイプ宣言
//----------------------
HRESULT InitGame();
void UninitGame(void);
void UpdatetGame(void);
void DrawGame(void);
int GetGame(void);
int GetItem(void);
bool PauseGame(void);
int FailObject(void);

#endif
