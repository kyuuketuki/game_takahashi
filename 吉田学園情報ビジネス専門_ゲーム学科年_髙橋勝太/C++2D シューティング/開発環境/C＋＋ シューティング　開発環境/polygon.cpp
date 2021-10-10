//=============================================================================
//
// メイン処理 [polygon.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "polygon.h"
#include "bullet.h"
#include "player.h"
#include "manager.h"
#include "animation.h"

int CPolygon::m_nDamage = NULL;
bool CPolygon::m_bUsePolygon = false;

bool g_bPoygonBullet = false;
bool g_bUse = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CPolygon::CPolygon()
{
	//初期化
	m_CirclePattern = 0;
	m_nMaxSize = 0;
	m_nMaxSize = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPolygon::~CPolygon()
{
	//初期化
	m_bUse = false;
	g_bPoygonBullet = false;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fSizeX, float fSizeY, float fmove, float fRot, float fRotMove, int nMaxSize, int MinSize, int nType, int nTypeNumber)
{
	// CScene2Dの初期化処理
	CScene2D::Init(pos, fSizeX, fSizeY);

	//回転設定
	SetRevolution(fRot);

	//メンバ変数に代入
	m_move = move;
	m_fmove = fmove;
	m_col = col;
	m_nLife = nLife;
	m_nType = nType;
	m_nTypeNumber = nTypeNumber;
	m_fSizeX = fSizeX;
	m_fSizeY = fSizeY;
	m_nMaxSize = nMaxSize;
	m_nMinSize = MinSize;
	m_fRotMove = fRotMove;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPolygon::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPolygon::Update(void)
{
	// 現在の位置の取得
	D3DXVECTOR3 pos = GetPosition();

	int nDamage = 0;

	if (m_nType == OBJTYPE_BULET_ENEMY)
	{
		//位置更新
		pos += m_move;
		nDamage = 0;
	}

	//プレイヤの位置に更新
	if (m_nType == OBJTYPE_BULET_PLAYER)
	{
		pos = CPlayer::GetPlayer();
		nDamage = 5;
	}

	//移動させる
	SetPosition(pos);

	// 現在の回転の取得
	D3DXVECTOR3 rot = GetRevolution();

	//回転更新
	rot.z += m_fRotMove;

	//回転設定
	SetRevolution(rot.z);

	//更新
	CScene2D::Update();

	//図形の拡大
	if (m_CirclePattern == 0)
	{
		//拡大縮小
		m_fSizeX += m_fmove;
		m_fSizeY += m_fmove;

		//拡大させる最大値
		if (m_fSizeX >= m_nMaxSize)
		{
			m_CirclePattern = 1;
		}

	}

	//図形の縮小
	if (m_CirclePattern == 1)
	{
		//拡大縮小
		m_fSizeX -= m_fmove;
		m_fSizeY -= m_fmove;

		//縮小させる最小値
		if (m_fSizeX <= m_nMinSize)
		{
			m_CirclePattern = 0;
		}
	}

	//ライフが0以下になったとき
	if (m_nLife <= 0)
	{
		Uninit();
	}

	//範囲外の場合
	if (pos.y <= 0 - 500.0f)
	{
		Uninit();
	}
	else if (pos.y >= SCREEN_HEIGHT + 500.0f)
	{
		Uninit();
	}

	if (g_bPoygonBullet == true)
	{
		if (m_nType == OBJTYPE_BULET_PLAYER)
		{
			g_bPoygonBullet = false;
			Uninit();
		}
	}

	// 位置
	D3DXVECTOR3 posBullet[4];

	// 対角線の設定
	float fLength = sqrtf(m_fSizeX * m_fSizeX + m_fSizeY * m_fSizeY);
	float fAngle = atan2f(m_fSizeX, m_fSizeY);

	//頂点の座標
	posBullet[0].x = (pos.x - sinf(fAngle + rot.z) * fLength);
	posBullet[0].y = (pos.y + cosf(fAngle + rot.z) * fLength);
	posBullet[0].z = (pos.z = 0.0f);

	posBullet[1].x = (pos.x - sinf(fAngle - rot.z) * fLength);
	posBullet[1].y = (pos.y - cosf(fAngle - rot.z) * fLength);
	posBullet[1].z = (pos.z = 0.0f);

	posBullet[2].x = (pos.x + sinf(fAngle - rot.z) * fLength);
	posBullet[2].y = (pos.y + cosf(fAngle - rot.z) * fLength);
	posBullet[2].z = (pos.z = 0.0f);

	posBullet[3].x = (pos.x + sinf(fAngle + rot.z) * fLength);
	posBullet[3].y = (pos.y - cosf(fAngle + rot.z) * fLength);
	posBullet[3].z = (pos.z = 0.0f);
	
	if (m_nType == OBJTYPE_BULET_ENEMY)
	{

		if (m_nTypeNumber == 1)
		{
			CBullet::Create(posBullet[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_col, 1, nDamage, BULLET_SIZE, BULLET_SIZE, m_nType);
		}

		if (m_nTypeNumber == 4)
		{

			CBullet::Create(posBullet[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_col, 1, nDamage, BULLET_SIZE, BULLET_SIZE, m_nType);
			CBullet::Create(posBullet[1], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_col, 1, nDamage, BULLET_SIZE, BULLET_SIZE, m_nType);
			CBullet::Create(posBullet[2], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_col, 1, nDamage, BULLET_SIZE, BULLET_SIZE, m_nType);
			CBullet::Create(posBullet[3], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_col, 1, nDamage, BULLET_SIZE, BULLET_SIZE, m_nType);
		}
	}

	if (m_nType == OBJTYPE_BULET_PLAYER)
	{
		if (m_nTypeNumber == 1)
		{
			CBullet::Create(posBullet[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_col, 1, nDamage, BULLET_SIZE, BULLET_SIZE, m_nType);
			CBullet::Create(posBullet[1], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_col, 1, nDamage, BULLET_SIZE, BULLET_SIZE, m_nType);
			CBullet::Create(posBullet[2], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_col, 1, nDamage, BULLET_SIZE, BULLET_SIZE, m_nType);
			CBullet::Create(posBullet[3], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_col, 1, nDamage, BULLET_SIZE, BULLET_SIZE, m_nType);

			if (g_bUse == true)
			{
				//弾の発射
				CBullet::Create(posBullet[0], D3DXVECTOR3(0.0f, -10.0f, 0.0f), m_col, 150, m_nDamage, BULLET_SIZE, BULLET_SIZE, m_nType);
				CBullet::Create(posBullet[1], D3DXVECTOR3(0.0f, -10.0f, 0.0f), m_col, 150, m_nDamage, BULLET_SIZE, BULLET_SIZE, m_nType);
				CBullet::Create(posBullet[2], D3DXVECTOR3(0.0f, -10.0f, 0.0f), m_col, 150, m_nDamage, BULLET_SIZE, BULLET_SIZE, m_nType);
				CBullet::Create(posBullet[3], D3DXVECTOR3(0.0f, -10.0f, 0.0f), m_col, 150, m_nDamage, BULLET_SIZE, BULLET_SIZE, m_nType);

				g_bUse = false;
			}
		}

		if (m_nTypeNumber == 2)
		{
			CBullet::Create(posBullet[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_col, 1, 1, BULLET_SIZE, BULLET_SIZE, m_nType);
			CBullet::Create(posBullet[1], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_col, 1, 1, BULLET_SIZE, BULLET_SIZE, m_nType);
			CBullet::Create(posBullet[2], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_col, 1, 1, BULLET_SIZE, BULLET_SIZE, m_nType);
			CBullet::Create(posBullet[3], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_col, 1, 1, BULLET_SIZE, BULLET_SIZE, m_nType);
		}
	}

	if (m_nType == OBJTYPE_BULET_ENEMY)
	{
		//弾のライフを減らす
		m_nLife--;
	}

	if (m_nType == OBJTYPE_BULET_PLAYER)
	{
		if (m_nTypeNumber == 2)
		{
			//弾のライフを減らす
			m_nLife--;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPolygon::Draw(void)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CPolygon * CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fSizeX, float fSizeY, float fmove, float fRot, float fRotMove, int nMaxSize, int MinSize, int nType, int nTypeNumber)
{
	//弾を生成
	CPolygon *pPolgon = NULL;
	pPolgon = new CPolygon;

	pPolgon->Init(pos, move, col, nLife, fSizeX, fSizeY, fmove, fRot, fRotMove, nMaxSize, MinSize, nType, nTypeNumber);

	return pPolgon;
}

//=============================================================================
// プレイヤーの発射用
//=============================================================================
void CPolygon::PlayerBullet(int nDamage)
{
	g_bUse = true;
	m_nDamage = nDamage;
}

//=============================================================================
// 途中破棄
//=============================================================================
void CPolygon::UninitBullet(void)
{
	//弾を生成
	CPolygon *pPolgon = NULL;
	pPolgon = new CPolygon;

	g_bPoygonBullet = true;
}