//==============================================================================
//
// メッシュフィールドの描画〔meshorbit.cpp〕
// AUTHOR : TAKAHASHI SHOTA
//
//==============================================================================
#include "meshorbit.h"
#include "model.h"
#include "input.h"
#include "score.h"

//==============================================================================
// マクロ定義
//==============================================================================
#define ORBIT_WIDTHNUM	(10)								// 列数(幅)
#define ORBIT_DEPTHNUM	(1)									// 行数(奥行)
#define ORBIT_WIDTH		(0.0f)							// 幅の大きさ
#define ORBIT_DEPTH		(0.0f)							// 奥行の大きさ

//==============================================================================
// グローバル変数
//==============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshOrbit = NULL;	// バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshOrbit = NULL;	// インデックスバッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshOrbit = NULL;		// テクスチャへのポインタ
D3DXVECTOR3 g_posMeshOrbit;							// 位置
D3DXVECTOR3 g_rotMeshOrbit;							// 向き
D3DXMATRIX g_mtxWorldMeshOrbit;						// ワールドマトリックス
MeshOrbit g_orbit[ORBIT_MAX];						//フィールドの情報
int g_nAllPointOrbit;								// 総頂点数
int g_nPolygonOrbit;								// ポリゴン数
int g_nIdxPointOrbit;								// インデックスバッファの必要な確保数
float g_fWidthOrbit = ORBIT_WIDTH;					// 横幅の端
float g_fDepthOrbit = ORBIT_DEPTH;					// 奥行の端
int g_nWidthOrbit = ORBIT_WIDTHNUM + 1;				// 横幅の頂点数
int g_nDepthOrbit = ORBIT_DEPTHNUM + 1;				// 奥行の頂点数
													
//==============================================================================
// 初期化処理
//==============================================================================
HRESULT InitMeshOrbit(void)
{
	// ローカル変数宣言
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	WORD *pIdx;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/10.png", &g_pTextureMeshOrbit);

	// 変数の初期化
	g_nAllPointOrbit = ORBIT_DEPTHNUM * 2 * (ORBIT_WIDTHNUM + 2) - 2;						// 総頂点数
	g_nPolygonOrbit = ORBIT_WIDTHNUM * ORBIT_DEPTHNUM * 2 + (4 * (ORBIT_DEPTHNUM - 1));		// 総ポリゴン数
	g_nIdxPointOrbit = g_nWidthOrbit * g_nDepthOrbit;										// インデックスバッファでの頂点数

	for (int nCnt = 0; nCnt < ORBIT_MAX; nCnt++)
	{
		g_orbit[nCnt].nAllPoint = 0;
		g_orbit[nCnt].nPolygon = 0;
		g_orbit[nCnt].nIdxPoint = 0;
		g_orbit[nCnt].bUse = false;
	}

	float fWidthMax = g_fWidthOrbit * (float)ORBIT_WIDTHNUM;
	float fDepthMax = g_fDepthOrbit * (float)ORBIT_DEPTHNUM;

	PLAYER *pModel;
	pModel = GetModel();

	//g_orbit[0].pMtxParent = pModel->mtxWorld;
	//g_orbit[0].pMtxParent = pModel->aModel[1].mtxWorld;

	//g_orbit[0].aOffice[0] = D3DXVECTOR3(pModel->aModel[5].mtxWorld._41, pModel->aModel[5].mtxWorld._42, pModel->aModel[5].mtxWorld._43);
	//g_orbit[0].aOffice[1] = D3DXVECTOR3(pModel->aModel[1].mtxWorld._41, pModel->aModel[1].mtxWorld._42, pModel->aModel[1].mtxWorld._43);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * g_nIdxPointOrbit,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshOrbit,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshOrbit->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < g_nDepthOrbit; nCnt++)
	{// 奥行軸
		for (int nCntA = 0; nCntA < g_nWidthOrbit; nCntA++)
		{
			// 横軸
			// ポリゴンの各頂点座標
			pVtx[0].pos = D3DXVECTOR3(-fWidthMax / 2.0f + (float)nCntA * g_fWidthOrbit, g_posMeshOrbit.y, fDepthMax / 2.0f - (float)nCnt * g_fDepthOrbit);

			// 法線ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 各頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.2f);

			// テクスチャ頂点情報の設定
			pVtx[0].tex = D3DXVECTOR2(1.0f * nCntA, 1.0f * nCnt);
			//pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx++;
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffMeshOrbit->Unlock();

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nAllPointOrbit,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&g_pIdxBuffMeshOrbit,NULL);

	// インデックスバッファをロックし、番号データへのポインタを取得
	g_pIdxBuffMeshOrbit->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntA = 0; nCntA < ORBIT_DEPTHNUM; nCntA++)
	{
		for (int nCnt = 0; nCnt < g_nWidthOrbit + 1; nCnt++, pIdx += 2)
		{
			if (nCnt != 0 && nCnt == g_nWidthOrbit && nCntA != ORBIT_DEPTHNUM - 1)
			{// 右端から折り返す時
				pIdx[0] = pIdx[-1];
				pIdx[1] = pIdx[-2] + 1;
			}
			else if (nCntA == ORBIT_DEPTHNUM - 1 && nCnt == g_nWidthOrbit)
			{// 終了時に無視する
				break;
			}
			else
			{// 通常配置
				pIdx[0] = g_nWidthOrbit + (g_nWidthOrbit * nCntA) + nCnt;
				pIdx[1] = pIdx[0] - g_nWidthOrbit;
			}
		}
	}

	// インデックスバッファをアンロックする
	g_pIdxBuffMeshOrbit->Unlock();

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void UninitMeshOrbit(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffMeshOrbit != NULL)
	{
		g_pVtxBuffMeshOrbit->Release();
		g_pVtxBuffMeshOrbit = NULL;
	}

	// テクスチャの開放
	if (g_pTextureMeshOrbit != NULL)
	{
		g_pTextureMeshOrbit->Release();
		g_pTextureMeshOrbit = NULL;
	}

	// インデックスバッファの開放
	if (g_pIdxBuffMeshOrbit != NULL)
	{
		g_pIdxBuffMeshOrbit->Release();
		g_pIdxBuffMeshOrbit = NULL;
	}
}

//==============================================================================
// 更新処理
//==============================================================================
void UpdateMeshOrbit(void)
{

}

//==============================================================================
// 描画処理
//==============================================================================
void DrawMeshOrbit(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;		// デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	MeshOrbit *pOrbit;
	pOrbit = &g_orbit[0];

	// デバイスの取得
	pDevice = GetDevice();

	//両面
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	for (int nCnt = 0; nCnt < ORBIT_MAX; nCnt++, pOrbit++)
	{
		if (pOrbit->bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldMeshOrbit);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_orbit[0].aOffice[0].x, g_orbit[0].aOffice[0].y, g_orbit[0].aOffice[0].z);
			D3DXMatrixMultiply(&pOrbit->aMtxWorldPoint[0], &pOrbit->aMtxWorldPoint[0], &mtxTrans);

			// 算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
			D3DXMatrixMultiply(&pOrbit->aMtxWorldPoint[0], &pOrbit->aMtxWorldPoint[0], &g_orbit[0].pMtxParent);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_orbit[0].aOffice[1].x, g_orbit[0].aOffice[1].y, g_orbit[0].aOffice[1].z);
			D3DXMatrixMultiply(&pOrbit->aMtxWorldPoint[1], &pOrbit->aMtxWorldPoint[1], &mtxTrans);

			// 算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
			D3DXMatrixMultiply(&pOrbit->aMtxWorldPoint[1], &pOrbit->aMtxWorldPoint[1], &g_orbit[0].pMtxParent);

			// ローカル変数宣言
			VERTEX_3D *pVtx;
			PLAYER *pModel;
			pModel = GetModel();

			//// 頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffMeshOrbit->Lock(0, 0, (void**)&pVtx, 0);

			//ずらす
			pVtx[20].pos = pVtx[18].pos;
			pVtx[18].pos = pVtx[16].pos;
			pVtx[16].pos = pVtx[14].pos;
			pVtx[14].pos = pVtx[12].pos;
			pVtx[12].pos = pVtx[10].pos;
			pVtx[10].pos = pVtx[8].pos;
			pVtx[8].pos = pVtx[6].pos;
			pVtx[6].pos = pVtx[4].pos;
			pVtx[4].pos = pVtx[2].pos;
			pVtx[2].pos = pVtx[0].pos;

			//代入
			pVtx[0].pos = D3DXVECTOR3(pModel->aModel[5].mtxWorld._41, pModel->aModel[5].mtxWorld._42, pModel->aModel[5].mtxWorld._43);
			//pVtx[0].pos = g_orbit[0].pos;

			//ずらす
			pVtx[21].pos = pVtx[19].pos;
			pVtx[19].pos = pVtx[17].pos;
			pVtx[17].pos = pVtx[15].pos;
			pVtx[15].pos = pVtx[13].pos;
			pVtx[13].pos = pVtx[11].pos;
			pVtx[11].pos = pVtx[9].pos;
			pVtx[9].pos = pVtx[7].pos;
			pVtx[7].pos = pVtx[5].pos;
			pVtx[5].pos = pVtx[3].pos;
			pVtx[3].pos = pVtx[1].pos;

			//代入
			pVtx[1].pos = D3DXVECTOR3(pModel->aModel[4].mtxWorld._41, pModel->aModel[4].mtxWorld._42, pModel->aModel[4].mtxWorld._43);
			///pVtx[1].pos = g_orbit[1].pos;

			// 頂点バッファをアンロックする
			g_pVtxBuffMeshOrbit->Unlock();

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshOrbit);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshOrbit, 0, sizeof(VERTEX_3D));

			// インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshOrbit);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMeshOrbit);

			// ポリゴンの描画
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,	// プリミティブの種類
				0,
				0,
				g_nIdxPointOrbit,			// 頂点数
				0,
				g_nPolygonOrbit);			// プリミティブ数
		}
	}
	//レンダーステートの設定
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

MeshOrbit * GetOrbit(void)
{
	return &g_orbit[0];
}

//==============================================================================
// フィールドの設定
//==============================================================================
void SetOrbit(D3DXVECTOR3 pos, D3DXVECTOR3 pos2)
{
	// ローカル変数宣言
	VERTEX_3D *pVtx;

	MeshOrbit *pOrbit;
	pOrbit = &g_orbit[0];

	// フィールドの設定
	for (int nCnt = 0; nCnt < ORBIT_MAX; nCnt++, pOrbit++)
	{
		if (pOrbit->bUse == false)
		{
			pOrbit->pos = pos;
			pOrbit->pos2 = pos2;

			//使用していいるか
			pOrbit->bUse = true;

			//break;
		}
	}
}