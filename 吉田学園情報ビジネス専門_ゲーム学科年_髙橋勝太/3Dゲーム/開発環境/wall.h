//-----------------------------------------------------------------
//
// プレイヤーの処理 (player.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//---------------------------------------------------------------------------- -
// マクロ定義
//-----------------------------------------------------------------------------
#define MAX_WALL (3)				//壁の上限
#define SHADOW_SIZE (10)			//壁のサイズ

//-----------------------------------------------------------------------------
//構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	bool bUse;
}WALL;


//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define MOVE_NUMBER (6)
#define MOVE_NUMBER2 (50)

//===============
//プロトタイプ宣言
//===============
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos);
#endif

