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
#include "shadow.h"
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
#include "car.h"
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

	InitShadow();

	InitPlayer();

	InitCar();

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

	UninitShadow();

	UninitPlayer();

	UninitCar();

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
	if (GetKeyboardTrigger(DIK_P) == true)
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

		UpdateShadow();


		//プレイヤーの切り替え
		if (g_PlayerChange == 1)
		{
			UpdatePlayer();
		}

		//プレイヤーの切り替え
		if (g_PlayerChange == 0)
		{
			UpdateCar();
		}

		UpdateObject();

		UpdateCamera();

		Updatelight();

		UpdateEffect();

		UpdateUi();

		UpdateBG();

		UpdateTimer();

		AddTimer(1);

		if (GetKeyboardTrigger(DIK_1) == true)
		{
			//車をを動かす
			if (g_PlayerChange == 1)
			{
				g_PlayerChange = 0;
			}

			//プレイヤーを動かす
			else if (g_PlayerChange == 0)
			{
				g_PlayerChange = 1;
			}
		}

		PLAYER *player;
		player = GetModel();

		//オブジェクトの向きを変える
		if (GetKeyboardTrigger(DIK_RIGHT) == true)
		{
			g_nDataTime2 += D3DX_PI / 2;
		}

		if (GetKeyboardTrigger(DIK_LEFT) == true)
		{
			g_nDataTime2 += -D3DX_PI / 2;
		}

		CAR  *pCar;
		pCar = GetCar();

		//プレイヤーの位置にオブジェクトを生成
		if (GetKeyboardTrigger(DIK_G) == true)
		{
			//ツールの位置に
			SetObject(D3DXVECTOR3(pCar->pos.x, pCar->pos.y, pCar->pos.z), D3DXVECTOR3(0.0f, g_nDataTime2, 0.0f), g_nDataTime);

			//txtファイルに書き込む
			FailObject();

			//Gボタン押した回数をカウント
			g_nObjectDate += 1;
		}

		//最新のオブジェクトを消去
		if (g_nObjectDate >= 1)
		{
			if (GetKeyboardTrigger(DIK_H) == true)
			{
				//Hボタン押した回数をカウント
				//情報を受け渡す
				g_nObjectDate -= 1;

				//txtファイルに書き込む
				FailObject();
			}
		}

		//オブジェクトのタイプを変える
		if (GetKeyboardTrigger(DIK_UP) == true)
		{
			g_nDataTime += 1;
		}

		if (GetKeyboardTrigger(DIK_DOWN) == true)
		{
			g_nDataTime -= 1;
		}

		//オブジェクトタイプの上限時の場合0に戻す
		if (g_nDataTime > GetobjectType() - 1.0f)
		{
			g_nDataTime = 0.0f;
		}

		//オブジェクトタイプの上限時の場合MAXに戻す
		if (g_nDataTime == -1.0f)
		{
			g_nDataTime = GetobjectType() - 1.0f;
		}

		//アイテムのタイプを変える
		if (GetKeyboardTrigger(DIK_UP) == true)
		{
			g_nDataItem += 1;
		}

		if (GetKeyboardTrigger(DIK_DOWN) == true)
		{
			g_nDataItem -= 1;
		}
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

	DrawShadow();

	DrawBullet();

	DrawPlayer();

	DrawCar();

	DrawEffect();

	DrawTimer();

	DrawUi();

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

//---------------------------------------------
//書き出し
//---------------------------------------------
int FailObject()
{
	PLAYER *player;
	player = GetModel();

	CAR  *pCar;
	pCar = GetCar();

	FILE *fp;

	fp = fopen("data/TEXT/ObjectSet.txt", "w");

	//オブジェクトの位置を記憶(CAR)
	FailDate[g_nObjectDate].X = pCar->pos.x;
	FailDate[g_nObjectDate].Y = pCar->pos.y;
	FailDate[g_nObjectDate].Z = pCar->pos.z;
	FailDate[g_nObjectDate].Rot = g_nDataTime2;
	FailDate[g_nObjectDate].Type = g_nDataTime;

	for (int nCnt = 0; nCnt < g_nObjectDate + 1; nCnt++)
	{
		//書き込む内容
		fprintf(fp, "OBJECTSET\n");
		fprintf(fp, "	POSX = %.1f\n", FailDate[nCnt].X);
		fprintf(fp, "	POSY = %.1f\n", FailDate[nCnt].Y);
		fprintf(fp, "	POSZ = %.1f\n", FailDate[nCnt].Z);
		fprintf(fp, "	ROTX = 0");
		fprintf(fp, "	ROTY = %.1f\n", FailDate[nCnt].Rot);
		fprintf(fp, "	ROTZ = 0");
		fprintf(fp, "	TYPE = %d\n", FailDate[nCnt].Type);
		fprintf(fp, "END_SETOBJECT\n\n");
	}

	//「txt」のファイルを閉じる
	fclose(fp);

	return 0;
}