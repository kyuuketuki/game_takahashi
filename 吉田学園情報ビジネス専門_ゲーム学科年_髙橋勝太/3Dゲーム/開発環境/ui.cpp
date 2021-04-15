//-----------------------------------------------------------------
//
// タイトルの処理 (titile.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//インクルードファイル
//------------------------
#include "ui.h"
#include "input.h"
#include "fade.h"
#include "game.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MAX_UI			(2)									// 最大数
#define HEIGHT_Y		(500.0f * -1.0f)					// ロゴの初期中心Y座標
#define PLAYER_X		(450.0f)							// ロゴ幅
#define PLAYER_Y		(100.0f)							// ロゴの高さ
#define PLAYER_BAR_X	(450.0f)							// ロゴの高さ
#define PLAYER_BAR_Y	(100.0f)							// ロゴの高さ


//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUi = NULL;
LPDIRECT3DTEXTURE9 g_pTextureUi[MAX_UI] = {};
D3DXVECTOR3 g_posPlayer;						// タイトルロゴの中心座標
D3DXVECTOR3 g_posPlayerBar;						// タイトルロゴの中心座標
D3DXVECTOR3 g_posPlayer2;						// タイトルロゴの中心座標
D3DXVECTOR3 g_posPlayer2Bar;					// タイトルロゴの中心座標
int g_PlayerBar = 0;
int g_Player2Bar = 0;
int g_playerDate;
//-----------------------------------------------------------------
// タイトルの初期化処理
//-----------------------------------------------------------------
HRESULT InitUi(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	g_posPlayer = D3DXVECTOR3(960.0f, 50.0f, 0.0f);
	g_posPlayerBar = D3DXVECTOR3(1700.0f, 50.0f, 0.0f);

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/timer.jpg", &g_pTextureUi[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/item.jpg", &g_pTextureUi[0]);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_UI,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,						// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffUi,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntUi = 0; nCntUi < MAX_UI; nCntUi++)
	{
		// 頂点座標の設定
		SetVertexUi(nCntUi);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定			
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 情報の更新
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffUi->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// タイトルの終了処理
//-----------------------------------------------------------------
void UninitUi(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffUi != NULL)
	{
		g_pVtxBuffUi->Release();
		g_pVtxBuffUi = NULL;
	}

	// テクスチャの開放
	for (int nCntTexture = 0; nCntTexture < MAX_UI; nCntTexture++)
	{
		if (g_pTextureUi[nCntTexture] != NULL)
		{
			g_pTextureUi[nCntTexture]->Release();
			g_pTextureUi[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// タイトルの更新処理
//-----------------------------------------------------------------
void UpdateUi(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	for (int nCntUi = 0; nCntUi < MAX_UI; nCntUi++)
	{
		// 頂点座標の設定
		SetVertexUi(nCntUi);
	}

	if (GetKeyboardPress(DIK_I) == true)
	{
		g_PlayerBar += 5;
	}

	if (GetKeyboardPress(DIK_K) == true)
	{
		g_Player2Bar += 5;
	}
}

//-----------------------------------------------------------------
// タイトルの描画処理
//-----------------------------------------------------------------
void DrawUi(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffUi, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntTexture = 0; nCntTexture < MAX_UI; nCntTexture++)
	{
		pDevice->SetTexture(0, g_pTextureUi[nCntTexture]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
	}
}

//-----------------------------------------------------------------
// タイトル画面に貼るテクスチャの指定
//-----------------------------------------------------------------
void SetVertexUi(int nCntUi)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	//
	if (nCntUi == 0)
	{
		pVtx[0].pos = D3DXVECTOR3(g_posPlayerBar.x - (PLAYER_X / 2), g_posPlayerBar.y + (PLAYER_Y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posPlayerBar.x - (PLAYER_X / 2), g_posPlayerBar.y - (PLAYER_Y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posPlayerBar.x + (PLAYER_X / 2) - (g_PlayerBar), g_posPlayerBar.y + (PLAYER_Y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posPlayerBar.x + (PLAYER_X / 2) - (g_PlayerBar), g_posPlayerBar.y - (PLAYER_Y / 2), 0.0f);
	}

	if (nCntUi == 1)
	{
		pVtx[4].pos = D3DXVECTOR3(g_posPlayer.x - (PLAYER_BAR_X / 2), g_posPlayer.y + (PLAYER_BAR_Y / 2), 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_posPlayer.x - (PLAYER_BAR_X / 2), g_posPlayer.y - (PLAYER_BAR_Y / 2), 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_posPlayer.x + (PLAYER_BAR_X / 2) - (g_PlayerBar), g_posPlayer.y + (PLAYER_BAR_Y / 2), 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_posPlayer.x + (PLAYER_BAR_X / 2) - (g_PlayerBar), g_posPlayer.y - (PLAYER_BAR_Y / 2), 0.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffUi->Unlock();
}