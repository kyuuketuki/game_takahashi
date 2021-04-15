#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------
//
// game (game.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//インクルードファイル
//------------------------
#include<stdio.h>
#include "main.h"
#include "camera.h"
#include "light.h"
#include"model.h"
#include "xinput.h"
#include "input.h"
#include "wall.h"
#include "stdio.h"
#include "object.h"
#include "billboard.h"
#include "effect.h"
#include "ui.h"
#include "meshfield.h"
#include "bullet.h"
#include "pause.h"
#include "bg.h"
#include "score.h"
#include "gamepad.h"
#include "timer.h"
#include "fade.h"
#include "meshorbit.h"

//==============================================================================
// マクロ定義
//==============================================================================
#define TEXT_LENGTH			(128)		// テキスト読み込みの最大数
#define DATA_LENGTH			(64)		// データ読み込みの最大数

//==============================================================================
// グローバル変数
//==============================================================================
bool g_bPause;						//ポーズ状態判定
int g_PlayerChange = 0;				//動かしているプレイヤー
int g_nDataTime = 0;				//初期状態
float g_nDataTime2 = 0;				//初期状態
int g_nDataItem = 0;				//初期状態
int g_nDataItem2 = 0;				//初期状態
FAILDATE FailDate[MAX_OBJECT];
int g_nObjectDate = 0;
int g_nItemDate = 0;
int g_FPSCnt = 0;
char g_GameStage;

//--------------
//初期化処理
//--------------
HRESULT InitGame()
{
	g_bPause = false;

	//LoadGame();

	InitPause();

	InitBG();

	InitScore();

	InitMeshfield();

	InitMeshOrbit();

	InitWall();

	InitBillboard();

	InitBullet();

	InitPlayer();

	InitObject();

	InitCamera();

	Initlight();

	InitEffect();

	InitUi();

	InitTimer();

	//スコアの表示
	for (int nCount = 0; nCount < 8; nCount++)
	{
		SetScore(D3DXVECTOR3(1600 + 70.0f * (nCount + 1), 50.0f, 0.0f), 0);
	}

	//タイムの表示
	//分
	for (int nCount = 0; nCount < 2; nCount++)
	{
		SetTimer(D3DXVECTOR3(800 + 50.0f * (nCount + 1), 50.0f, 0.0f), 0);
	}
	//秒
	for (int nCount = 0; nCount < 2; nCount++)
	{
		SetTimer(D3DXVECTOR3(950 + 50.0f * (nCount + 1), 50.0f, 0.0f), 0);
	}

	//フィールドの設定
	SetField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);	//平面

	return E_NOTIMPL;
}

//----------------
//終了処理
//----------------
void UninitGame(void)
{
	UninitBG();

	UninitScore();

	UninitMeshfield();

	UninitMeshOrbit();

	UninitWall();

	UninitBillboard();

	UninitBullet();

	UninitPlayer();

	UninitObject();

	UninitCamera();

	Uninitlight();

	UninitEffect();

	UninitUi();

	UninitTimer();

	// ポーズメニューの終了処理
	UninitPause();
}

//--------------------
//更新処理
//--------------------
void UpdatetGame(void)
{
	//ポーズボタンを押したとき
	if (GetKeyboardTrigger(DIK_P) == true || IsButtonDown(P))
	{
		g_bPause = g_bPause ? false : true;

	}

	if (g_bPause == true)
	{
		UpdatePause();
	}

	else
	{
		UpdateMeshfield();

		UpdateMeshOrbit();

		UpdateScore();

		UpdateBullet();

		UpdateWall();

		UpdateBillboard();

		UpdatePlayer();

		UpdateObject();

		UpdateCamera();

		Updatelight();

		UpdateEffect();

		UpdateUi();

		UpdateBG();

		UpdateTimer();

		AddTimer(1);
	}
}

//--------------------
//描画処理
//--------------------
void DrawGame(void)
{
	DrawMeshfield();

	DrawMeshOrbit();

	DrawObject();

	DrawWall();

	DrawBillboard();

	DrawBullet();
	
	DrawUi();

	DrawScore();

	DrawPlayer();

	DrawEffect();

	DrawTimer();

	

	// ポーズの描画処理
	if (g_bPause == true)
	{
		DrawPause();
	}
}

//---------------------------------------------
//データの受け渡し
//---------------------------------------------
int GetGame(void)
{
	return g_PlayerChange;
}

//---------------------------------------------
//データの受け渡し
//---------------------------------------------
int GetItem(void)
{
	return g_nDataTime;
}

//---------------------------------------------
//データの受け渡し
//---------------------------------------------
char GetGameTXT(void)
{
	return g_GameStage;
}

//---------------------------------------------
//データの受け渡し
//---------------------------------------------
bool PauseGame(void)
{
	return g_bPause;
}