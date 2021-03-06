//=============================================================================
//
// メイン処理 [animasion.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "animation.h"
#include "manager.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CAnimasion::m_pTexture[MAX_ANIME] = {};
int CAnimasion::m_nUninitType = NULL;
int g_nUninitType;

//==============================================================================
// コンストラクタ
//==============================================================================
CAnimasion::CAnimasion(int nPriority, int nType) : CScene2D(nPriority, nType)
{
	m_nAnime = 0;
	m_nPatternAnime = 0;
}

//==============================================================================
// デストラクタ
//==============================================================================
CAnimasion::~CAnimasion()
{

}

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT CAnimasion::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType)
{
	CScene2D::Init(pos, fSizeX, fSizeY);

	m_pos = pos;
	m_nType = nType;

	//アニメーションの初期化
	CScene2D::SetTex(1, 0, 0);

	m_nAnime = nAnime;

	if (nType == 0)
	{
		m_fAnimeX = 1.0f;			//テクスチャ分割
		m_fAnimeY = 0.05f;			//テクスチャ分割
		m_nX = 1;
		m_nY = 20;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 1)
	{
		m_fAnimeX = 0.333f;			//テクスチャ分割
		m_fAnimeY = 0.333f;			//テクスチャ分割
		m_nX = 3;
		m_nY = 3;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 2)
	{
		m_fAnimeX = 1.0f;			//テクスチャ分割
		m_fAnimeY = 0.1f;			//テクスチャ分割
		m_nX = 1;
		m_nY = 10;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 3)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.166f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 6;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 4)
	{
		m_fAnimeX = 0.5f;			//テクスチャ分割
		m_fAnimeY = 0.2f;			//テクスチャ分割
		m_nX = 2;
		m_nY = 5;
		m_fCriss = 1;				//ループあり

									//色変更
		CScene2D::SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}

	if (nType == 5)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.5f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 1;				//ループあり
	}

	if (nType == 6)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.1666f;		//テクスチャ分割
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 1;				//ループあり
	}

	if (nType == 7)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.3333f;		//テクスチャ分割
		m_nX = 5;
		m_nY = 3;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 8)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.3333f;		//テクスチャ分割
		m_nX = 5;
		m_nY = 3;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 9)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.5f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 1;				//ループあり
	}

	if (nType == 10)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.25f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 4;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 11)
	{
		m_fAnimeX = 0.20f;			//テクスチャ分割
		m_fAnimeY = 0.3333f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 3;
		m_fCriss = 1;				//ループなし
	}

	if (nType == 12)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.5f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 13)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.1666f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 6;
		m_fCriss = 1;				//ループなし
	}

	if (nType == 14)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.25f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 4;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 15)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.5f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 1;				//ループあり
	}

	if (nType == 16)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.5f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 1;				//ループあり
	}

	if (nType == 17)
	{
		m_fAnimeX = 0.5f;			//テクスチャ分割
		m_fAnimeY = 0.1f;			//テクスチャ分割
		m_nX = 2;
		m_nY = 10;
		m_fCriss = 1;				//ループあり
	}

	if (m_nType == 6 || m_nType == 9 || m_nType == 11 || m_nType == 5 || m_nType == 13)
	{
		//色変更
		CScene2D::SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CAnimasion::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
// 更新処理
//==============================================================================
void CAnimasion::Update(void)
{
	//プレイヤー用アニメーション
	if (m_nType == 6 || m_nType == 9 || m_nType == 11 || m_nType == 5 || m_nType == 13)
	{
		// 現在の位置の取得
		D3DXVECTOR3 pos = CPlayer::GetPlayer();
		D3DXVECTOR3 objective = D3DXVECTOR3(pos.x + m_pos.x, pos.y + m_pos.y, pos.z);

		//移動させる
		SetPosition(objective);
	}

	//途中変更Uninit
	if (m_nType == g_nUninitType)
	{
		m_fCriss = 0;
		m_nAnime = 1;
	}

	//アイテム取得時のエフェクトアニメーション
	if (m_nType == 7 || m_nType == 8)
	{
		// 現在の位置の取得
		D3DXVECTOR3 pos = CPlayer::GetPlayer();

		//移動させる
		SetPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));
	}

	//アニメーションの更新条件
	if ((m_nCounterAnime % m_nAnime) == 0)
	{
		//アニメーションパターンの更新
		m_nPatternAnime = (m_nPatternAnime + 1);

		//アニメーションの更新
		CScene2D::SetAnime(m_fAnimeX, m_fAnimeY, m_nX, m_nY, m_nPatternAnime);
	}

	//カウンターを進める
	m_nCounterAnime++;

	//更新
	CScene2D::Update();

	//アニメーションを終了リセット
	if (m_nPatternAnime == m_nX * m_nY)
	{
		//カウンターのリセット
		m_nPatternAnime = 0;

		//ループさせないとき
		if (m_fCriss == 0)
		{
			//終了される
			Uninit();
		}
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void CAnimasion::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, 0);

	CScene2D::Draw();

	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

//==============================================================================
// 生成処理
//==============================================================================
CAnimasion * CAnimasion::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType)
{
	//弾を生成
	CAnimasion *pAnimasion = NULL;
	pAnimasion = new CAnimasion;

	// NULLチェック
	if (pAnimasion != NULL)
	{
		pAnimasion->Init(pos, fSizeX, fSizeY, nAnime, nType);
	}

	//テクスチャを入れる
	pAnimasion->BindTexture(m_pTexture[nType]);

	return pAnimasion;
}

//==============================================================================
// テクスチャの読み込み
//==============================================================================
HRESULT CAnimasion::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hoshihikari.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pipo-btleffect133_.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pipo-btleffect145.png", &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pipo-btleffect120e.png", &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/frameeffects006m.png", &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pipo-mapeffect015_480.png", &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect_01.png", &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect_04.png", &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect_05.png", &m_pTexture[8]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pipo-mapeffect014_480.png", &m_pTexture[9]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg_01.png", &m_pTexture[10]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect_03.png", &m_pTexture[11]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pipo-mapeffect014_480.png", &m_pTexture[12]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pipo-nazoobj01a.png", &m_pTexture[13]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg_01.png", &m_pTexture[14]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pipo-mapeffect014_480.png", &m_pTexture[15]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pipo-mapeffect015_480.png", &m_pTexture[16]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg02.jpg", &m_pTexture[17]);

	return S_OK;
}

//==============================================================================
// テクスチャの破棄
//==============================================================================
void CAnimasion::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_ANIME; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//==============================================================================
// 破棄するタイプ
//==============================================================================
void CAnimasion::UninitType(int nUninitType)
{
	g_nUninitType = nUninitType;
}

//==============================================================================
// 廃棄したグローバルを初期化
//==============================================================================
void CAnimasion::UninitTypeClear(void)
{
	g_nUninitType = 0;
}

//=============================================================================
//
// メイン処理 [animasionbg.cpp]
// Author : takahashi shota
//
//=============================================================================

//==============================================================================
// コンストラクタ
//==============================================================================
CAnimasionBg::CAnimasionBg(int nPriority, int nType) : CAnimasion(nPriority, nType)
{
	m_nAnime = 0;
	m_nPatternAnime = 0;
}

//==============================================================================
// デストラクタ
//==============================================================================
CAnimasionBg::~CAnimasionBg()
{

}

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT CAnimasionBg::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType)
{
	CScene2D::Init(pos, fSizeX, fSizeY);

	m_pos = pos;
	m_nType = nType;

	//アニメーションの初期化
	CScene2D::SetTex(1, 0, 0);

	//アニメーションスピード
	m_nAnime = nAnime;

	if (nType == 0)
	{
		m_fAnimeX = 1.0f;			//テクスチャ分割
		m_fAnimeY = 0.05f;			//テクスチャ分割
		m_nX = 1;
		m_nY = 20;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 1)
	{
		m_fAnimeX = 0.333f;			//テクスチャ分割
		m_fAnimeY = 0.333f;			//テクスチャ分割
		m_nX = 3;
		m_nY = 3;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 2)
	{
		m_fAnimeX = 1.0f;			//テクスチャ分割
		m_fAnimeY = 0.1f;			//テクスチャ分割
		m_nX = 1;
		m_nY = 10;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 3)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.166f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 6;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 4)
	{
		m_fAnimeX = 0.5f;			//テクスチャ分割
		m_fAnimeY = 0.2f;			//テクスチャ分割
		m_nX = 2;
		m_nY = 5;
		m_fCriss = 1;				//ループあり

									//色変更
		CScene2D::SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}

	if (nType == 5)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.5f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 1;				//ループあり
	}

	if (nType == 6)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.1666f;		//テクスチャ分割
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 1;				//ループあり
	}

	if (nType == 7)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.3333f;		//テクスチャ分割
		m_nX = 5;
		m_nY = 3;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 8)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.3333f;		//テクスチャ分割
		m_nX = 5;
		m_nY = 3;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 9)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.5f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 1;				//ループあり
	}

	if (nType == 10)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.25f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 4;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 11)
	{
		m_fAnimeX = 0.20f;			//テクスチャ分割
		m_fAnimeY = 0.3333f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 3;
		m_fCriss = 1;				//ループなし
	}

	if (nType == 12)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.5f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 13)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.1666f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 6;
		m_fCriss = 1;				//ループなし
	}

	if (nType == 14)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.25f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 4;
		m_fCriss = 0;				//ループなし
	}

	if (nType == 15)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.5f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 1;				//ループあり
	}

	if (nType == 16)
	{
		m_fAnimeX = 0.2f;			//テクスチャ分割
		m_fAnimeY = 0.5f;			//テクスチャ分割
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 1;				//ループあり
	}

	if (nType == 17)
	{
		m_fAnimeX = 0.5f;			//テクスチャ分割
		m_fAnimeY = 0.1f;			//テクスチャ分割
		m_nX = 2;
		m_nY = 10;
		m_fCriss = 1;				//ループあり
		m_fColorFa = 0.0f;			//透明度0.0f
	}

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CAnimasionBg::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
// 更新処理
//==============================================================================
void CAnimasionBg::Update(void)
{
	if (m_fColorFa <= 1.0f)
	{
		m_fColorFa += 0.005f;
		CScene2D::SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorFa));
	}

	//アニメーションの更新条件
	if ((m_nCounterAnime % m_nAnime) == 0)
	{
		//アニメーションパターンの更新
		m_nPatternAnime = (m_nPatternAnime + 1);

		//アニメーションの更新
		CScene2D::SetAnime(m_fAnimeX, m_fAnimeY, m_nX, m_nY, m_nPatternAnime);
	}

	//カウンターを進める
	m_nCounterAnime++;

	//更新
	CScene2D::Update();

	//アニメーションを終了リセット
	if (m_nPatternAnime == m_nX * m_nY)
	{
		//カウンターのリセット
		m_nPatternAnime = 0;

		//ループさせないとき
		if (m_fCriss == 0)
		{
			//終了される
			Uninit();
		}
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void CAnimasionBg::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
// 生成処理
//==============================================================================
CAnimasionBg * CAnimasionBg::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType)
{
	//弾を生成
	CAnimasionBg *pAnimasionBg = NULL;
	pAnimasionBg = new CAnimasionBg;

	// NULLチェック
	if (pAnimasionBg != NULL)
	{
		pAnimasionBg->Init(pos, fSizeX, fSizeY, nAnime, nType);
	}

	//テクスチャを入れる
	pAnimasionBg->BindTexture(m_pTexture[nType]);

	return pAnimasionBg;
}

//==============================================================================
// 途中破棄処理
//==============================================================================
void CAnimasionBg::UninitTypeClear(void)
{
	for (int nCnt = 0; nCnt < MAX_ANIME; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
