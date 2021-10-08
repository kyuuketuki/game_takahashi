//=============================================================================
//
// メイン処理 [logo.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "logo.h"
#include "manager.h"
#include "scene2D.h"
#include "scene.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CLogo::m_apTextureLogo[MAX_LOGO] = {};
CPlayer *CLogo::m_pPlayer = NULL;

//グローバル宣言
int g_nTypeLogo = -1;
int g_nTypeMoveLogo = -1;
int g_nTypeCollarLogo = -1;
D3DXVECTOR3 g_posLogo;
D3DXCOLOR g_col;

//=============================================================================
// コンストラクタ
//=============================================================================
CLogo::CLogo(int nPriority, int nType) : CScene2D(nPriority, nType)
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CLogo::~CLogo()
{
	g_nTypeLogo = -1;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLogo::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	CScene2D::Init(pos, fSizeX, fSizeY);

	m_nType = nType;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLogo::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLogo::Update(void)
{	
	//タイトル移動
	if (m_nType == 0)
	{
		// 現在の位置の取得
		D3DXVECTOR3 pos = GetPosition();

		//移動させる
		SetPosition(pos);

		//更新
		CScene2D::Update();
	}

	//プレイヤー当たり判定の移動
	if (m_nType == 5)
	{
		//色を変える
		CScene2D::SetCollar(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

		//プレイヤーの位置を取得
		D3DXVECTOR3 posPlayer = m_pPlayer->GetPlayer();

		//移動させる
		SetPosition(posPlayer);

		//更新
		CScene2D::Update();
	}

	if (m_nType == 9)
	{
		//色を変える
		CScene2D::SetCollar(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}

	if (m_nType == g_nTypeCollarLogo)
	{
		//色を変える
		CScene2D::SetCollar(g_col);
	}

	//途中移動
	if (m_nType == g_nTypeMoveLogo)
	{
		//初期化
		g_nTypeMoveLogo = -1;

		//移動させる
		SetPosition(g_posLogo);

		//更新
		CScene2D::Update();
	}
	
	
	if (g_nTypeLogo == m_nType)
	{
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CLogo::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CLogo * CLogo::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	// ローカル変数宣言
	CLogo *pLogo = NULL;
	pLogo = new CLogo;

	// 初期化
	if (pLogo != NULL)
	{
		pLogo->Init(pos, fSizeX, fSizeY , nType);
	}

	// テクスチャ割り当て
	pLogo->BindTexture(m_apTextureLogo[nType]);

	return pLogo;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CLogo::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title01.png", &m_apTextureLogo[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg100.png", &m_apTextureLogo[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &m_apTextureLogo[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg102.png", &m_apTextureLogo[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_enter.png", &m_apTextureLogo[4]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet000.png", &m_apTextureLogo[5]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/logo_game.jpg", &m_apTextureLogo[6]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/logo_操作説明.jpg", &m_apTextureLogo[7]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/logo_終了.jpg", &m_apTextureLogo[8]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/frame001a.png", &m_apTextureLogo[9]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_01.png", &m_apTextureLogo[10]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_02.png", &m_apTextureLogo[11]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_03.png", &m_apTextureLogo[12]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_04.png", &m_apTextureLogo[13]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_05.png", &m_apTextureLogo[14]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/status1.jpg", &m_apTextureLogo[15]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/status2.jpg", &m_apTextureLogo[16]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/status3.jpg", &m_apTextureLogo[17]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/status4.jpg", &m_apTextureLogo[18]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/status5.jpg", &m_apTextureLogo[19]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_04_status.png", &m_apTextureLogo[20]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_02_status.png", &m_apTextureLogo[21]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_04_status.png", &m_apTextureLogo[22]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_04_status.png", &m_apTextureLogo[23]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_05_status.png", &m_apTextureLogo[24]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/keyboard.jpg", &m_apTextureLogo[25]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gamepad.jpg", &m_apTextureLogo[26]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gameover.png", &m_apTextureLogo[27]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gameover1.jpg", &m_apTextureLogo[28]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gameover2.jpg", &m_apTextureLogo[29]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gameover3.jpg", &m_apTextureLogo[30]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause.png", &m_apTextureLogo[31]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gemeclear.png", &m_apTextureLogo[32]);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CLogo::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_LOGO; nCnt++)
	{
		if (m_apTextureLogo != NULL)
		{
			m_apTextureLogo[nCnt]->Release();
			m_apTextureLogo[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 
//=============================================================================
void CLogo::TypeUninit(int nType)
{
	g_nTypeLogo = nType;
}

//=============================================================================
// 
//=============================================================================
void CLogo::TypeMove(D3DXVECTOR3 pos, int nTypeMove)
{
	g_posLogo = pos;
	g_nTypeMoveLogo = nTypeMove;
}

//=============================================================================
// 指定したタイプの色を変える
//=============================================================================
void CLogo::TypeChangeCollar(D3DXCOLOR col, int nTypeCollar)
{
	g_nTypeCollarLogo = nTypeCollar;
	g_col = col;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CLogoPause::CLogoPause(int nPriority, int nType) : CLogo(nPriority, nType)
{

}

//=============================================================================
// 
//=============================================================================
CLogoPause::~CLogoPause()
{

}

//=============================================================================
// 
//=============================================================================
HRESULT CLogoPause::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	CScene2D::Init(pos, fSizeX, fSizeY);

	CLogoPause::m_nType = nType;

	return S_OK;
}

//=============================================================================
// 
//=============================================================================
void CLogoPause::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 
//=============================================================================
void CLogoPause::Update(void)
{
	//タイトル移動
	if (m_nType == 0)
	{
		// 現在の位置の取得
		D3DXVECTOR3 pos = GetPosition();

		//移動させる
		SetPosition(pos);

		//更新
		CScene2D::Update();
	}

	//プレイヤー当たり判定の移動
	if (m_nType == 5)
	{
		//色を変える
		CScene2D::SetCollar(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

		//プレイヤーの位置を取得
		D3DXVECTOR3 posPlayer = m_pPlayer->GetPlayer();

		//移動させる
		SetPosition(posPlayer);

		//更新
		CScene2D::Update();
	}

	if (m_nType == 9)
	{
		//色を変える
		CScene2D::SetCollar(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}

	if (m_nType == g_nTypeCollarLogo)
	{
		//色を変える
		CScene2D::SetCollar(g_col);
	}

	//途中移動
	if (m_nType == g_nTypeMoveLogo)
	{
		//初期化
		g_nTypeMoveLogo = -1;

		//移動させる
		SetPosition(g_posLogo);

		//更新
		CScene2D::Update();
	}


	if (g_nTypeLogo == m_nType)
	{
		Uninit();
	}
}

//=============================================================================
// 
//=============================================================================
void CLogoPause::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 
//=============================================================================
CLogoPause * CLogoPause::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	// ローカル変数宣言
	CLogoPause *pLogoPause = NULL;
	pLogoPause = new CLogoPause;

	// 初期化
	if (pLogoPause != NULL)
	{
		pLogoPause->Init(pos, fSizeX, fSizeY, nType);
	}

	// テクスチャ割り当て
	pLogoPause->BindTexture(m_apTextureLogo[nType]);

	return pLogoPause;
}

//=============================================================================
// 
//=============================================================================
void CLogoPause::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_LOGO; nCnt++)
	{
		if (m_apTextureLogo != NULL)
		{
			m_apTextureLogo[nCnt]->Release();
			m_apTextureLogo[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 
//=============================================================================
void CLogoPause::TypeUninit(int nType)
{
	g_nTypeLogo = nType;
}

//=============================================================================
// 
//=============================================================================
void CLogoPause::TypeMove(D3DXVECTOR3 pos, int nTypeMove)
{
	g_posLogo = pos;
	g_nTypeMoveLogo = nTypeMove;
}

//=============================================================================
// 
//=============================================================================
void CLogoPause::TypeChangeCollar(D3DXCOLOR col, int nTypeCollar)
{
	g_nTypeCollarLogo = nTypeCollar;
	g_col = col;
}
