//-----------------------------------------------------------------
//
// プレイヤーの処理 (model.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//インクルードファイル
//------------------------
#include "car.h"
#include"camera.h"
#include "shadow.h"
#include "input.h"
#include "bullet.h"
#include "effect.h"
#include "object.h"
#include "meshfield.h"
#include "gamepad.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define MAX_CAR			(1)
#define CAR_X			(50)									// 中心から端までまでの長さ(x)
#define CAR_Y			(50)									// 中心から端までまでの長さ(y)
#define CAR_MOVE		(5.0f)									//移動速度

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPD3DXMESH g_pMeshCar[MAX_CAR] = {};	//頂点情報
LPD3DXBUFFER g_pBuffMetCar[MAX_CAR] = {};
LPDIRECT3DTEXTURE9 g_pTextureCar[5] = {};			//テクスチャ
DWORD  g_nNumMatCar = 0;							//マテリアルの数
CAR g_Car[MAX_CAR];
D3DXMATRIX g_mtxWorldCar;							//ワールドマトリックス
float g_carrot;
float g_SpeedCar = 0;
int g_CarnType = 0;

//-----------------------------------------------------------------------------
// ポリゴンの初期化処理
//-----------------------------------------------------------------------------
HRESULT InitCar(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_CAR; nCnt++)
	{
		//最大最小の値を入れる
		g_Car[nCnt].MinCar = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_Car[nCnt].MaxCar = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);

		//model読み込み
		D3DXLoadMeshFromX("data/model/point.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetCar[0], NULL, &g_nNumMatCar, &g_pMeshCar[0]);
		//D3DXLoadMeshFromX("data/model/car004.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetCar[1], NULL, &g_nNumMatCar, &g_pMeshCar[1]);


		int nNumVtx;			//頂点数
		DWORD sizeFVF;			//頂点フォーマットのサイズ
		BYTE *pVtxBuff;			//頂点バッファへのポインタ 

		D3DXMATERIAL *pMat;		//マテリアルへのポインタ

		//頂点数を取得
		nNumVtx = g_pMeshCar[nCnt]->GetNumVertices();
		g_Car[nCnt].nNumVtx = nNumVtx;

		//マテリアルデータへのポインタ取得
		pMat = (D3DXMATERIAL*)g_pBuffMetCar[nCnt]->GetBufferPointer();

		//xファイルにテクスチャがある場合
		for (int nCntMat = 0; nCntMat < (int)g_nNumMatCar; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャ読み込み
				//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/50.png", &g_pTextureCar[0]);
			}
		}

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshCar[nCnt]->GetFVF());

		//頂点バッファをロック
		g_pMeshCar[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//xファイルの最大最小の値を入れる
			if (g_Car[nCnt].MinCar.x > vtx.x)
			{
				g_Car[nCnt].MinCar.x = vtx.x;
			}
			if (g_Car[nCnt].MaxCar.x < vtx.x)
			{
				g_Car[nCnt].MaxCar.x = vtx.x;
			}
			if (g_Car[nCnt].MinCar.y > vtx.y)
			{
				g_Car[nCnt].MinCar.y = vtx.y;
			}
			if (g_Car[nCnt].MaxCar.y < vtx.y)
			{
				g_Car[nCnt].MaxCar.y = vtx.y;
			}
			if (g_Car[nCnt].MinCar.z > vtx.z)
			{
				g_Car[nCnt].MinCar.z = vtx.z;
			}
			if (g_Car[nCnt].MaxCar.z < vtx.z)
			{
				g_Car[nCnt].MaxCar.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	//頂点フォーマットのサイズ分を進める
		}
		//頂点バッファをアンロック
		g_pMeshCar[nCnt]->UnlockVertexBuffer();

		//位置
		g_Car[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//位置
		//g_Car[1].pos = D3DXVECTOR3(0.0f, 0.0f, -400.0f);

		//向き
		g_Car[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	return S_OK;
}

//-----------------------------------------------------------------------------
// ポリゴンの終了処理
//-----------------------------------------------------------------------------
void UninitCar(void)
{
	for (int nCnt = 0; nCnt < g_Car[nCnt].nNumVtx; nCnt++)
	{
		//メッシュの開放
		if (g_pMeshCar != NULL)
		{
			g_pMeshCar[nCnt]->Release();
			g_pMeshCar[nCnt] = NULL;
		}

		//マテリアルの開放
		if (g_pBuffMetCar != NULL)
		{
			g_pBuffMetCar[nCnt]->Release();
			g_pBuffMetCar[nCnt] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// ポリゴンの更新処理
//-----------------------------------------------------------------------------
void UpdateCar(void)
{
	CAMERA  *pCamera;
	pCamera = GetCamera();

	EFFECT *pEffect;
	pEffect = GetEffect();

	CAR  *pCar;
	pCar = GetCar();

	for (int nCnt = 0; nCnt < MAX_CAR; nCnt++)
	{
		//通常移動
		// モデルの移動
		if (GetKeyboardPress(DIK_W) == true)
		{
			if (GetKeyboardPress(DIK_A) == true)
			{// 左上方向
				g_Car[nCnt].move.x -= cosf(pCamera->rot.y + D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].move.z += sinf(pCamera->rot.y + D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].rotDest.y = pCamera->rot.y + (D3DX_PI * 3 / 4);
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{// 右上方向
				g_Car[nCnt].move.x += cosf(pCamera->rot.y - D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].move.z -= sinf(pCamera->rot.y - D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].rotDest.y = pCamera->rot.y - (D3DX_PI * 3 / 4);
			}
			else
			{// 上方向
				g_Car[nCnt].move.x += sinf(pCamera->rot.y) * CAR_MOVE;
				g_Car[nCnt].move.z += cosf(pCamera->rot.y) * CAR_MOVE;
				g_Car[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			if (GetKeyboardPress(DIK_D) == true)
			{// 右上方向
				g_Car[nCnt].move.x += cosf(pCamera->rot.y + D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].move.z -= sinf(pCamera->rot.y + D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI / -4;
			}
			else if (GetKeyboardPress(DIK_A) == true)
			{// 左上方向
				g_Car[nCnt].move.x -= cosf(pCamera->rot.y - D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].move.z += sinf(pCamera->rot.y - D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI / 4;
			}
			else
			{// 下方向
				g_Car[nCnt].move.x += sinf(pCamera->rot.y - D3DX_PI) * CAR_MOVE;
				g_Car[nCnt].move.z += cosf(pCamera->rot.y - D3DX_PI) * CAR_MOVE;
				g_Car[nCnt].rotDest.y = pCamera->rot.y;
			}
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{// 左方向.
			g_Car[nCnt].move.x -= cosf(pCamera->rot.y) * CAR_MOVE;
			g_Car[nCnt].move.z += sinf(pCamera->rot.y) * CAR_MOVE;
			g_Car[nCnt].rotDest.y = pCamera->rot.y + (D3DX_PI / 2);
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// 右方向
			g_Car[nCnt].move.x += cosf(pCamera->rot.y) * CAR_MOVE;
			g_Car[nCnt].move.z -= sinf(pCamera->rot.y) * CAR_MOVE;
			g_Car[nCnt].rotDest.y = pCamera->rot.y + (D3DX_PI / -2);
		}

		if (GetKeyboardPress(DIK_6) == true)
		{// 上方向
			g_Car[nCnt].move.y += 10.0;
		}

		if (GetKeyboardPress(DIK_7) == true)
		{// 下方向
			g_Car[nCnt].move.y -= 10.0;
		}

		//位置リセット
		if (GetKeyboardPress(DIK_0) == true)
		{
			g_Car[nCnt].pos.y = 0.0;
		}

		if (g_Car[nCnt].pos.y <= 0.0f)
		{// 下方向
			g_Car[nCnt].pos.y = 0.0f;
		}

		//移動量の減衰
		g_Car[nCnt].move.x -= (0 + g_Car[nCnt].move.x) * 0.5f;
		g_Car[nCnt].move.y -= (0 + g_Car[nCnt].move.y) * 0.5f;
		g_Car[nCnt].move.z -= (0 + g_Car[nCnt].move.z) * 0.5f;

		//位置更新
		g_Car[nCnt].pos.x += g_Car[nCnt].move.x;
		g_Car[nCnt].pos.y += g_Car[nCnt].move.y;
		g_Car[nCnt].pos.z += g_Car[nCnt].move.z;

		// 目的の回転角の上限
		if (g_Car[nCnt].rotDest.y - g_Car[nCnt].rot.y < -D3DX_PI)
		{
			g_Car[nCnt].rotDest.y += D3DX_PI * 2.0f;
		}
		else if (g_Car[nCnt].rotDest.y - g_Car[nCnt].rot.y > D3DX_PI)
		{
			g_Car[nCnt].rotDest.y -= D3DX_PI * 2.0f;
		}

		// 向きの更新
		g_Car[nCnt].rot.y += (g_Car[nCnt].rotDest.y - g_Car[nCnt].rot.y) * 0.1f;

		// 現在の回転角の上限
		if (g_Car[nCnt].rot.y < -D3DX_PI)
		{
			g_Car[nCnt].rot.y += D3DX_PI * 2.0f;
		}
		else if (g_Car[nCnt].rot.y > D3DX_PI)
		{
			g_Car[nCnt].rot.y -= D3DX_PI * 2.0f;
		}

		//影の位置更新
		SetPositionShadow(0, D3DXVECTOR3(g_Car[nCnt].pos.x, 0.0f, g_Car[nCnt].pos.z));
	}
}

//-----------------------------------------------------------------------------
// ポリゴンの描画処理
//-----------------------------------------------------------------------------
void DrawCar(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存
	D3DXMATERIAL *pMat;				//マテリアルへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_CAR; nCnt++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldCar);

		//向きの反転
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Car[nCnt].rot.y, g_Car[nCnt].rot.x, g_Car[nCnt].rot.z);
		D3DXMatrixMultiply(&g_mtxWorldCar, &g_mtxWorldCar, &mtxRot);

		//位置の反転
		D3DXMatrixTranslation(&mtxTrans, g_Car[nCnt].pos.x, g_Car[nCnt].pos.y, g_Car[nCnt].pos.z);
		D3DXMatrixMultiply(&g_mtxWorldCar, &g_mtxWorldCar, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldCar);

		//現在のマテリアルの取得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタ取得
		pMat = (D3DXMATERIAL*)g_pBuffMetCar[nCnt]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_nNumMatCar; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			//pDevice->SetTexture(0, g_pTextureCar[nCntMat]);

			//モデルパーツの描画
			g_pMeshCar[nCnt]->DrawSubset(nCntMat);
		}
	}

	//保存したマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//---------------------------------------------
//データの受け渡し
//---------------------------------------------
CAR *GetCar(void)
{
	return &g_Car[0];
}
