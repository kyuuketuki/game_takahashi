//=============================================================================
//
// ÉÅÉCÉìèàóù [polygon.cpp]
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
// 
//=============================================================================
CPolygon::CPolygon()
{
	m_CirclePattern = 0;
	m_nMaxSize = 0;
	m_nMaxSize = 0;
}

//=============================================================================
// 
//=============================================================================
CPolygon::~CPolygon()
{
	m_bUse = false;
	g_bPoygonBullet = false;
}

//=============================================================================
// 
//=============================================================================
HRESULT CPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fSizeX, float fSizeY, float fmove, float fRot, float fRotMove, int nMaxSize, int MinSize, int nType, int nTypeNumber)
{
	// CScene2DÇÃèâä˙âªèàóù
	CScene2D::Init(pos, fSizeX, fSizeY);

	//âÒì]ê›íË
	SetRevolution(fRot);

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
// 
//=============================================================================
void CPolygon::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 
//=============================================================================
void CPolygon::Update(void)
{
	// åªç›ÇÃà íuÇÃéÊìæ
	D3DXVECTOR3 pos = GetPosition();

	int nDamage = 0;

	if (m_nType == OBJTYPE_BULET_ENEMY)
	{
		//à íuçXêV
		pos += m_move;
		nDamage = 0;
	}

	//ÉvÉåÉCÉÑÇÃà íuÇ…çXêV
	if (m_nType == OBJTYPE_BULET_PLAYER)
	{
		pos = CPlayer::GetPlayer();
		nDamage = 5;
	}

	//à⁄ìÆÇ≥ÇπÇÈ
	SetPosition(pos);

	// åªç›ÇÃâÒì]ÇÃéÊìæ
	D3DXVECTOR3 rot = GetRevolution();

	//âÒì]çXêV
	rot.z += m_fRotMove;

	//âÒì]ê›íË
	SetRevolution(rot.z);

	//çXêV
	CScene2D::Update();

	//ê}å`ÇÃägëÂ
	if (m_CirclePattern == 0)
	{
		//ägëÂèkè¨
		m_fSizeX += m_fmove;
		m_fSizeY += m_fmove;

		//ägëÂÇ≥ÇπÇÈç≈ëÂíl
		if (m_fSizeX >= m_nMaxSize)
		{
			m_CirclePattern = 1;
		}

	}

	//ê}å`ÇÃèkè¨
	if (m_CirclePattern == 1)
	{
		//ägëÂèkè¨
		m_fSizeX -= m_fmove;
		m_fSizeY -= m_fmove;

		//èkè¨Ç≥ÇπÇÈç≈è¨íl
		if (m_fSizeX <= m_nMinSize)
		{
			m_CirclePattern = 0;
		}
	}

	//ÉâÉCÉtÇ™0à»â∫Ç…Ç»Ç¡ÇΩÇ∆Ç´
	if (m_nLife <= 0)
	{
		Uninit();
	}

	//îÕàÕäOÇÃèÍçá
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

	// à íu
	D3DXVECTOR3 posBullet[4];

	// ëŒäpê¸ÇÃê›íË
	float fLength = sqrtf(m_fSizeX * m_fSizeX + m_fSizeY * m_fSizeY);
	float fAngle = atan2f(m_fSizeX, m_fSizeY);

	//í∏ì_ÇÃç¿ïW
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
				//íeÇÃî≠éÀ
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
		//íeÇÃÉâÉCÉtÇå∏ÇÁÇ∑
		m_nLife--;
	}

	if (m_nType == OBJTYPE_BULET_PLAYER)
	{
		if (m_nTypeNumber == 2)
		{
			//íeÇÃÉâÉCÉtÇå∏ÇÁÇ∑
			m_nLife--;
		}
	}
}

//=============================================================================
// 
//=============================================================================
void CPolygon::Draw(void)
{
	//CScene2D::Draw();
}

//=============================================================================
// 
//=============================================================================
CPolygon * CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fSizeX, float fSizeY, float fmove, float fRot, float fRotMove, int nMaxSize, int MinSize, int nType, int nTypeNumber)
{
	//íeÇê∂ê¨
	CPolygon *pPolgon = NULL;
	pPolgon = new CPolygon;

	pPolgon->Init(pos, move, col, nLife, fSizeX, fSizeY, fmove, fRot, fRotMove, nMaxSize, MinSize, nType, nTypeNumber);

	return pPolgon;
}

//=============================================================================
// 
//=============================================================================
void CPolygon::PlayerBullet(int nDamage)
{
	g_bUse = true;
	m_nDamage = nDamage;
}

//=============================================================================
// 
//=============================================================================
void CPolygon::UninitBullet(void)
{
	//íeÇê∂ê¨
	CPolygon *pPolgon = NULL;
	pPolgon = new CPolygon;

	g_bPoygonBullet = true;
}