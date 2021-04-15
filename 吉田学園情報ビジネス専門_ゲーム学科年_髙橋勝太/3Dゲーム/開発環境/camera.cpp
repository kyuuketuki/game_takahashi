//==============================================================================
//
// カメラの設定〔camera.cpp〕
// AUTHOR : shota takahashi
//
//==============================================================================
#include "camera.h"
#include "model.h"
#include "input.h"
#include "game.h"
#include "gamepad.h"

//==============================================================================
// マクロ定義
//==============================================================================
#define CAMERA_MOVE				(2.0f)							// カメラの移動量
#define CAMERA_TURN				(D3DX_PI / 100.0f)				// カメラの旋回速度
#define CAMERA_RANGE_CAR		(500.0f)						// 視点・注視点間の距離
#define CAMERA_RANGE_MODEL		(250.0f)						// 視点・注視点間の距離
#define CAMERA_HEIGHT			(500.0f)						// カメラ(視点)の高さ
#define CAMERA_SPDOWN			(0.5f)							// 減衰係数 

//==============================================================================
// グローバル変数
//==============================================================================
CAMERA g_camera[2];
float nHeight = 200;

//==============================================================================
// 初期化処理
//==============================================================================
void InitCamera(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//関数呼び出し
		CameraInfo(nCnt);
	}
}			

//==============================================================================
// 終了処理
//==============================================================================
void UninitCamera(void)
{

}

//==============================================================================
// 更新処理
//==============================================================================
void UpdateCamera(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// ローカル変数宣言
		PLAYER *player;
		player = GetModel();

		//アドレスを渡す
		CAMERA  *pCamera;
		pCamera = GetCamera();

		//プレイヤ視点
		// 目的の注視点
		g_camera[0].posRDest.x = player->pos.x - g_camera[0].fFront * sinf(player->rotDest.y);
		g_camera[0].posRDest.z = player->pos.z - g_camera[0].fFront * cosf(player->rotDest.y);
		g_camera[0].posRDest.y = player->pos.y + g_camera[0].fHeightR;

		// 目的の視点
		g_camera[0].posVDest.x = player->pos.x - sinf(g_camera[0].rot.y) * g_camera[0].fLength;
		g_camera[0].posVDest.z = player->pos.z - cosf(g_camera[0].rot.y) * g_camera[0].fLength;
		g_camera[0].posVDest.y = player->pos.y + cosf(g_camera[0].rot.x) * g_camera[0].fLength + g_camera[0].fHeightV;

		//モデル画面の時
		//if (GetGame() == 0)
		{
				//キーボード押したとき
				//Cを押した
				if (GetKeyboardPress(DIK_C) == true || IsButtonPush(C))
				{
					g_camera[0].rot.y += CAMERA_TURN;

					if (g_camera[0].rot.y > D3DX_PI)
					{
						g_camera[0].rot.y -= D3DX_PI * 2.0f;
					}

					g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * g_camera[0].fLength;
					g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * g_camera[0].fLength;
				}

				//Zを押した
				if (GetKeyboardPress(DIK_Z) == true || IsButtonPush(Z))
				{
					g_camera[0].rot.y -= CAMERA_TURN;

					if (g_camera[0].rot.y < -D3DX_PI)
					{
						g_camera[0].rot.y += D3DX_PI * 2.0f;
					}

					g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * g_camera[0].fLength;
					g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * g_camera[0].fLength;
				}

			//高さ調整
			if (GetKeyboardPress(DIK_8) == true)
			{
				nHeight += 10.0f;
			}
			if (GetKeyboardPress(DIK_9) == true)
			{
				nHeight -= 10.0f;
			}

			//カメラリセット
			if (GetKeyboardTrigger(DIK_0) == true)
			{
				g_camera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// カメラの角度
				nHeight = 0.0f;
			}
		}

		//更新
		g_camera[0].fHeightV = nHeight;							//視点の高さの更新
		g_camera[0].fLength = CAMERA_RANGE_MODEL;				//視点の距離の更新

		// 注視点の位置更新
		g_camera[nCnt].posR.x += (g_camera[nCnt].posRDest.x - g_camera[nCnt].posR.x) * CAMERA_SPDOWN;
		g_camera[nCnt].posR.z += (g_camera[nCnt].posRDest.z - g_camera[nCnt].posR.z) * CAMERA_SPDOWN;
		g_camera[nCnt].posR.y += (g_camera[nCnt].posRDest.y - g_camera[nCnt].posR.y) * CAMERA_SPDOWN;

		// 視点の位置更新
		g_camera[nCnt].posV.x += (g_camera[nCnt].posVDest.x - g_camera[nCnt].posV.x) * CAMERA_SPDOWN;
		g_camera[nCnt].posV.z += (g_camera[nCnt].posVDest.z - g_camera[nCnt].posV.z) * CAMERA_SPDOWN;
		g_camera[nCnt].posV.y += (g_camera[nCnt].posVDest.y - g_camera[nCnt].posV.y) * CAMERA_SPDOWN;
	}
}

//==============================================================================
// カメラの設定処理
//==============================================================================
void SetCamera(int nIdx)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	//ビューポートを取得
	pDevice->SetViewport(&g_camera[nIdx].viewport);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera[nIdx].mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(
		&g_camera[nIdx].mtxProjection,
		D3DXToRadian(45.0f),									// 画角の設定
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,					// 比率
		10.0f,													// 手前限界の描画距離
		4000.0f);												// 奥限界の描画距離

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nIdx].mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera[nIdx].mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(
		&g_camera[nIdx].mtxView,
		&g_camera[nIdx].posV,
		&g_camera[nIdx].posR,
		&g_camera[nIdx].vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nIdx].mtxView);
}

//==============================================================================
// カメラの情報
//==============================================================================
void CameraInfo(int nIdx)
{
	// ローカル変数宣言
	PLAYER *player;
	player = GetModel();

	player += nIdx;

	switch (nIdx)
	{
	case 0:
		// 構造体の初期化
		g_camera[nIdx].posV = D3DXVECTOR3(player->pos.x,
			player->pos.y + 100.0f,
			player->pos.z - 200.0f);							// カメラ視点の位置
		g_camera[nIdx].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 注視点位置
		g_camera[nIdx].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 上方向ベクトル
		g_camera[nIdx].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量
		g_camera[nIdx].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// カメラの角度
		g_camera[nIdx].fLength = 200;							// 視点・注視点間の距離
		g_camera[nIdx].fHeightV = -60.0f;						// 視点の高さ
		g_camera[nIdx].fHeightR = player->pos.y + 100.0f;		// 注視点の高さ
		g_camera[nIdx].fFront = 15.0f;							// モデルの前方の距離
		g_camera[nIdx].bAutoTurn = false;						// カメラの回り込みON・OFF
		g_camera[nIdx].viewport.X = (DWORD)0.0f;				// 描画する画面左上のＸ座標
		g_camera[nIdx].viewport.Y = (DWORD)0.0f;				// 描画する画面左上のＹ座標 
		g_camera[nIdx].viewport.Width = (DWORD)1960.0f;			// 描画する画面の幅
		g_camera[nIdx].viewport.Height = (DWORD)1080.0f;		// 描画する画面の高さ
		g_camera[nIdx].viewport.MinZ = 0.0f;
		g_camera[nIdx].viewport.MaxZ = 1.0f;

		break;
	default:
		break;
	}
}

//==============================================================================
// カメラの取得
//==============================================================================
CAMERA *GetCamera(void)
{
	return &g_camera[0];
}

//==============================================================================
// カメラの取得
//==============================================================================
CAMERA *GetCamera2(void)
{
	return &g_camera[1];
}