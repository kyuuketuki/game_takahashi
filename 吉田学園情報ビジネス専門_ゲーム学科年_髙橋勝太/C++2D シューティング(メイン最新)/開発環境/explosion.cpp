//=============================================================================
//
// メイン処理 [explosion.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "explosion.h"
#include "manager.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// インストラクタ
//=============================================================================
CExplosion::CExplosion()
{
	m_nCounterAnime = 0;
	m_nPatternAnime = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CExplosion::~CExplosion()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	CScene2D::Init(pos, fSizeX, fSizeY);

	//アニメーションの初期化
	CScene2D::SetTex(0, 0, 0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CExplosion::Update(void)
{
	//アニメーションの更新条件
	if ((m_nCounterAnime % 5) == 0)
	{
		//アニメーションパターンの更新
		m_nPatternAnime = (m_nPatternAnime + 1);

		//アニメーションの更新
		CScene2D::SetTex(0.143, 1, m_nPatternAnime);
	}

	//カウンターを進める
	m_nCounterAnime++;

	//更新
	CScene2D::Update();

	//アニメーションを終了リセット
	if (m_nPatternAnime == 8)
	{
		m_nPatternAnime == 0;
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 生成させる
//=============================================================================
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	//爆破を生成
	CExplosion *pExplosion = NULL;
	pExplosion = new CExplosion;

	// NULLチェック
	if (pExplosion != NULL)
	{
		pExplosion->Init(pos, fSizeX, fSizeY);
	}

	//テクスチャを入れる
	pExplosion->BindTexture(m_pTexture);

	return pExplosion;
}

//=============================================================================
// テクスチャの生成
//=============================================================================
HRESULT CExplosion::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/explosion01.png", &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CExplosion::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}