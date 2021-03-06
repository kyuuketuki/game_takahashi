//=============================================================================
//
// C [player.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "player.h"
#include "manager.h"
#include "bullet.h"
#include "sound.h"
#include "logo.h"
#include "polygon.h"
#include "animation.h"
#include "gamepad.h"

// }Nθ`
#define MOVE_NUMBER (7)

// ΓIoΟιΎ
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture[5] = {};

//O[oιΎ
D3DXVECTOR3 g_pos;					//Getp
int g_nCntPlayer;					//eΜ­Λ¬x
int g_nBulletLevel = 0;				//eΜ­»Level
int g_nTimePlayer = 0;				//³GΤL―

int g_nCntPlayerBullet = 0;			//eΜ­ΛΤup
int g_nCntPlayerBullet2 = 0;		//eΜ­ΛΤup
int g_nCntPlayerBullet3 = 0;		//eΜ­ΛΤup

float g_fAnglePlayer;				//eΜ­Λpx
float g_fAnglePlayerBullet = 0.0f;	//eΜ­Λpx

bool g_bAnglePlayer = false;		//eΜ­Λpx
bool g_bBumpedPlayer = false;		//³GσΤ

//=============================================================================
// RXgN^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene2D(nPriority)
{
	//ϊ»
	g_nCntPlayerBullet = 0;
	g_nCntPlayerBullet2 = 0;
	g_nCntPlayerBullet3 = 0;
	g_nTimePlayer = 0;
	g_nBulletLevel = 0;

	g_fAnglePlayerBullet = 0.0f;

	m_nBullet = false;
	m_nBullet2 = false;
	g_bAnglePlayer = false;
	g_bBumpedPlayer = false;
	m_nBulletLevelUP = false;
}

//=============================================================================
// fXgN^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ϊ»
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, int nLife, float fSizeX, float fSizeY)
{
	CScene2D::Init(pos, fSizeX, fSizeY);

	//ΞpόΜpx
	g_fAnglePlayer = atan2f(fSizeX, fSizeY);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 10, 10, PLAYER_COLLISION_PINTER);

	//»έΜ^CvπζΎ
	m_nType = CManager::GetPlayerType();

	//^CvΙζΑΔΕεHPπΟ¦ι
	if (m_nType == 0)
	{
		CManager::SetMaxPlayerLife(10);
		m_nSpeed = 12;
	}

	if (m_nType == 1)
	{
		CManager::SetMaxPlayerLife(10);
		m_nSpeed = 10;
	}

	if (m_nType == 2)
	{
		CManager::SetMaxPlayerLife(10);
		m_nSpeed = 10;
	}

	if (m_nType == 3)
	{
		CManager::SetMaxPlayerLife(7);
		m_nSpeed = 15;
	}

	if (m_nType == 4)
	{
		CManager::SetMaxPlayerLife(14);
		m_nSpeed = 7;
	}

	// IuWFNgΜνήέθ
	SetObjType(CScene::OBJTYPE_PLAYER);

	return S_OK;
}

//=============================================================================
// IΉ
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// XV
//=============================================================================
void CPlayer::Update(void)
{
	//L[{[hζΎ
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//Q[pbhΜ|C^ιΎ
	CGamepad *pGamepad;
	pGamepad = CManager::GetGamepad();

	//TEhπζΎ
	CSound *pSound;
	pSound = CManager::GetSound();

	//vC[Κu
	D3DXVECTOR3 pos;

	int nSpeed = 0;

	//³GσΤ
	if (g_bBumpedPlayer == true)
	{
		//vC[ΜFπΤ­·ι
		CScene2D::SetCollar(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_nTimePlayer++;
	}

	//³GσΤ©η
	if (g_nTimePlayer == 60)
	{
		CScene2D::SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_bBumpedPlayer = false;
		g_nTimePlayer = 0;
	}

	//»έΜΚuξρ
	pos = GetPosition();

	//Ϊ?
	//Aπ΅½Ζ«
	if (pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_LEFT) == true || pGamepad->IsButtonPush(CInput::LEFT))
	{
		//Wπ΅½Ζ«
		if (pInputKeyboard->GetPress(DIK_W) == true || pInputKeyboard->GetPress(DIK_UP) == true || pGamepad->IsButtonPush(CInput::UP))
		{
			pos.x += cosf(D3DX_PI) * ((m_nSpeed) / 1.5f);
			pos.y += cosf(D3DX_PI) * ((m_nSpeed) / 1.5f);
		}

		//AΖSπ΅½Ζ«
		else if (pInputKeyboard->GetPress(DIK_S) == true || pInputKeyboard->GetPress(DIK_RIGHT) == true || pGamepad->IsButtonPush(CInput::DOWN))
		{
			pos.x += cosf(D3DX_PI) * ((m_nSpeed) / 1.5f);
			pos.y -= cosf(D3DX_PI) * ((m_nSpeed) / 1.5f);
		}

		//Aπ΅½Ζ«
		else
		{
			pos.x -= (m_nSpeed);
			pos.y += 0;
		}
	}

	//Dπ΅½Ζ«
	else if (pInputKeyboard->GetPress(DIK_D) == true || pInputKeyboard->GetPress(DIK_RIGHT) == true || pGamepad->IsButtonPush(CInput::RIGHT))
	{
		//DΖWπ΅½Ζ«
		if (pInputKeyboard->GetPress(DIK_W) == true || pInputKeyboard->GetPress(DIK_UP) == true || pGamepad->IsButtonPush(CInput::UP))
		{
			pos.x -= cosf(D3DX_PI) * ((m_nSpeed) / 1.5f);
			pos.y += cosf(D3DX_PI) * ((m_nSpeed) / 1.5f);
		}

		//DΖSπ΅½Ζ«
		else if (pInputKeyboard->GetPress(DIK_S) == true || pInputKeyboard->GetPress(DIK_DOWN) == true || pGamepad->IsButtonPush(CInput::DOWN))
		{
			pos.x -= cosf(D3DX_PI) * ((m_nSpeed) / 1.5f);
			pos.y -= cosf(D3DX_PI) * ((m_nSpeed) / 1.5f);
		}

		//Dπ΅½Ζ«
		else
		{
			pos.x -= -(m_nSpeed);
			pos.y -= 0;
		}
	}

	//Wπ΅½Ζ«
	else if (pInputKeyboard->GetPress(DIK_W) == true || pInputKeyboard->GetPress(DIK_UP) == true || pGamepad->IsButtonPush(CInput::CInput::UP))
	{
		pos.y -= (m_nSpeed);
	}

	//Sπ΅½Ζ«
	else if (pInputKeyboard->GetPress(DIK_S) == true || pInputKeyboard->GetPress(DIK_DOWN) == true || pGamepad->IsButtonPush(CInput::DOWN))
	{
		pos.y += (m_nSpeed);
	}

	//Aπ΅½Ζ«ΜΑ¬Κ
	if (pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_LEFT) == true || pGamepad->IsButtonPush(CInput::LEFT))
	{
		m_move.x -= sinf(g_fAnglePlayer) * 1;
	}

	//Dπ΅½Ζ«ΜΑ¬Κ
	if (pInputKeyboard->GetPress(DIK_D) == true || pInputKeyboard->GetPress(DIK_RIGHT) == true || pGamepad->IsButtonPush(CInput::RIGHT))
	{
		m_move.x += sinf(g_fAnglePlayer) * 1;
	}

	//Wπ΅½Ζ«ΜΑ¬Κ
	if (pInputKeyboard->GetPress(DIK_W) == true || pInputKeyboard->GetPress(DIK_UP) == true || pGamepad->IsButtonPush(CInput::UP))
	{
		m_move.y -= cosf(g_fAnglePlayer) * 1;
	}

	//Sπ΅½Ζ«ΜΑ¬Κ
	if (pInputKeyboard->GetPress(DIK_S) == true || pInputKeyboard->GetPress(DIK_DOWN) == true || pGamepad->IsButtonPush(CInput::DOWN))
	{
		m_move.y += cosf(g_fAnglePlayer) * 1;
	}

	//vC[Μ^Cvͺ0Μ
	if (m_nType == 0)
	{
		//eΜ­Λ(Press)
		if (pInputKeyboard->GetPress(DIK_SPACE) == true || pGamepad->IsButtonPush(CInput::A) == true)
		{
			if (g_nCntPlayer == 0)
			{
				//TEhSE
				pSound->Play(CSound::SOUND_LABEL_SE_SHOT);

				//obgx0ΜΙ
				if (g_nBulletLevel == 0)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 50.0f, 1.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), 150, 25, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
				}

				//obgx0ΜΙ
				if (g_nBulletLevel == 1)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x + 30.0f, pos.y - 40.0f, 1.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), 150, 25, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 30.0f, pos.y - 40.0f, 1.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), 150, 25, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
				}

				//obgx2ΜΙ
				if (g_nBulletLevel >= 2)
				{
					CPolygon::PlayerBullet(20);
				}
			}

			//obg­Λ
			g_nCntPlayer++;

			//obg­ΛΤu
			if (g_nCntPlayer >= 10)
			{
				g_nCntPlayer = 0;
			}
		}

		//obgx2Εo»³Ήι
		if (g_nBulletLevel >= 2)
		{
			//ΘOΜσΤπϊ»
			if (g_nCntPlayerBullet == 0)
			{
				//CPolygon::UninitBullet();		//|SNXπΑ·
				//CAnimasion::UninitType(6);		//^Cv6ΜAj[VπΑ·
				g_nCntPlayerBullet = 1;			//ϊ»π?ΉσΤΙ·ι
			}

			//ϊ»σΤ©ηΜt[Θ~
			if (m_nBulletLevelUP == true)
			{
				if (m_nBullet == false)
				{
					//x2σΤΙo»·ι|S
					CPolygon::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), 300, 50, 50, 0.0f, 0.0f, 0.05f, 50, 50, OBJTYPE_BULET_PLAYER, 1);
					m_nBullet = true;
				}
			}

			//xAbvσΤΙ·ι
			m_nBulletLevelUP = true;

			if (m_nBullet2 == true)
			{
				//xAbvItσΤΙ·ι
				m_nBulletLevelUP = false;
			}
		}
	}

	//vC[Μ^Cvͺ1Μ
	if (m_nType == 1)
	{
		//eΜ­Λ(Press)
		if (pInputKeyboard->GetPress(DIK_SPACE) == true || pGamepad->IsButtonPush(CInput::A) == true)
		{
			if (g_nCntPlayer == 0)
			{
				//TEhSE
				pSound->Play(CSound::SOUND_LABEL_SE_SHOT);

				//obgx0
				if (g_nBulletLevel == 0)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x + 30.0f, pos.y - 50.0f, 1.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 30.0f, pos.y - 50.0f, 1.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
				}

				//obgx1
				if (g_nBulletLevel == 1)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 40.0f, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x + 30.0f, pos.y - 50.0f, 1.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 30.0f, pos.y - 50.0f, 1.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
				}

				//obgx2
				if (g_nBulletLevel == 2)
				{
					//eΜ­Λ
					CPolygon::PlayerBullet(20);
				}

				if (g_nBulletLevel >= 3)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 40.0f, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x + 100.0f, pos.y + 100.0f, 1.0f), D3DXVECTOR3(-1.0f, -15.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 100.0f, pos.y + 100.0f, 1.0f), D3DXVECTOR3(1.0f, -15.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x + 300.0f, pos.y, 1.0f), D3DXVECTOR3(-4.0f, -15.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 300.0f, pos.y, 1.0f), D3DXVECTOR3(4.0f, -15.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
				}
			}

			//obg­Λ
			g_nCntPlayer++;

			//obg­ΛΤu
			if (g_nCntPlayer >= 10)
			{
				g_nCntPlayer = 0;
			}
		}

		//obgx2Εo»³Ήι
		if (g_nBulletLevel == 2)
		{
			if (g_nCntPlayerBullet == 0)
			{
				//CPolygon::UninitBullet();		//|SNXπΑ·
				g_nCntPlayerBullet = 1;			//ϊ»π?ΉσΤΙ·ι
			}

			//ϊ»σΤ©ηΜt[Θ~
			if (m_nBulletLevelUP == true)
			{
				if (m_nBullet == false)
				{
					//x2σΤΙo»·ι|S
					CPolygon::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 300, 50, 50, 1.0f, 0.0f, 0.05f, 100, 50, OBJTYPE_BULET_PLAYER, 1);
					m_nBullet = true;
				}
			}

			//xAbvσΤΙ·ι
			m_nBulletLevelUP = true;

			if (m_nBullet2 == true)
			{
				//xAbvItσΤΙ·ι
				m_nBulletLevelUP = false;
			}
		}

		//obgx4Εo»³Ήι
		if (g_nBulletLevel >= 3)
		{
			if (g_nCntPlayerBullet2 == 0)
			{
				//CPolygon::UninitBullet();		//|SNXπΑ·
				g_nCntPlayerBullet2 = 1;		//ϊ»π?ΉσΤΙ·ι
			}

			//ϊ»σΤ©ηΜt[Θ~
			if (m_nBulletLevelUP == true)
			{
				if (m_nBullet2 == false)
				{
					//x2σΤΙo»·ιAj[V
					CAnimasion::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f), 100, 100, 10, 9);
					CAnimasion::Create(D3DXVECTOR3(-100.0f, 100.0f, 0.0f), 100, 100, 10, 9);
					CAnimasion::Create(D3DXVECTOR3(300.0f, 0.0f, 0.0f), 100, 100, 10, 9);
					CAnimasion::Create(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), 100, 100, 10, 9);
					m_nBullet2 = true;
				}
			}

			//xAbvσΤΙ·ι
			m_nBulletLevelUP = true;

			if (m_nBullet2 == true)
			{
				//xAbvItσΤΙ·ι
				m_nBulletLevelUP = false;
			}
		}
	}

	//vC[Μ^Cvͺ2Μ
	if (m_nType == 2)
	{
		//eΜ­Λ(Press)
		if (pInputKeyboard->GetPress(DIK_SPACE) == true || pGamepad->IsButtonPush(CInput::A) == true)
		{
			if (g_nCntPlayer == 0)
			{
				//TEhSE
				pSound->Play(CSound::SOUND_LABEL_SE_SHOT);

				//obgx0
				if (g_nBulletLevel == 0)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x + 30.0f, pos.y - 30.0f, 1.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 30.0f, pos.y - 30.0f, 1.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
				}

				//obgx2
				if (g_nBulletLevel >= 1 && g_nBulletLevel <= 2)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 50.0f, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x + 30.0f, pos.y - 30.0f, 1.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 30.0f, pos.y - 30.0f, 1.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
				}

				//obgx2
				if (g_nBulletLevel >= 3 && g_nBulletLevel <= 5)
				{
					CPolygon::PlayerBullet(20);
				}

				//obgx3
				if (g_nBulletLevel >= 6)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 50.0f, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 150, 20, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 50.0f, 1.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 150, 20, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);

					CBullet::Create(D3DXVECTOR3(pos.x + 100.0f, pos.y, 1.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 100.0f, pos.y, 1.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);

					CBullet::Create(D3DXVECTOR3(pos.x + 100.0f, pos.y, 1.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 100.0f, pos.y, 1.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);

					CBullet::Create(D3DXVECTOR3(pos.x + 100.0f, pos.y, 1.0f), D3DXVECTOR3(10.0f, -10.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 100.0f, pos.y, 1.0f), D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
				}
			}

			//obg­Λ
			g_nCntPlayer++;

			//obg­ΛΤu
			if (g_nCntPlayer >= 10)
			{
				g_nCntPlayer = 0;
			}
		}

		//obgx3Εo»³Ήι
		if (g_nBulletLevel >= 3 && g_nBulletLevel <= 5)
		{
			if (g_nCntPlayerBullet == 0)
			{
				//CPolygon::UninitBullet();		//|SNXπΑ·
				g_nCntPlayerBullet = 1;			//ϊ»π?ΉσΤΙ·ι
			}

			//ϊ»σΤ©ηΜt[Θ~
			if (m_nBulletLevelUP == true)
			{
				if (m_nBullet == false)
				{
					//x2σΤΙo»·ι|S
					CPolygon::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 300, 50, 50, 1.0f, 0.0f, 0.05f, 100, 50, OBJTYPE_BULET_PLAYER, 1);
					m_nBullet = true;
				}
			}

			//xAbvσΤΙ·ι
			m_nBulletLevelUP = true;

			if (m_nBullet2 == true)
			{
				//xAbvItσΤΙ·ι
				m_nBulletLevelUP = false;
			}
		}

		//obgx3Εo»³Ήι
		if (g_nBulletLevel >= 6)
		{
			if (g_nCntPlayerBullet2 == 0)
			{
				//CPolygon::UninitBullet();		//|SNXπΑ·
				g_nCntPlayerBullet = 1;			//ϊ»π?ΉσΤΙ·ι
			}

			//ϊ»σΤ©ηΜt[Θ~
			if (m_nBulletLevelUP == true)
			{
				if (m_nBullet2 == false)
				{
					//x2σΤΙo»·ιAj[V
					CAnimasion::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), 100, 100, 10, 6);
					CAnimasion::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), 100, 100, 10, 6);
					m_nBullet2 = true;
				}
			}

			//xAbvσΤΙ·ι
			m_nBulletLevelUP = true;

			if (m_nBullet2 == true)
			{
				//xAbvItσΤΙ·ι
				m_nBulletLevelUP = false;
			}
		}
	}

	//vC[Μ^Cvͺ3Μ
	if (m_nType == 3)
	{
		//eΜ­Λ(Press)
		if (pInputKeyboard->GetPress(DIK_SPACE) == true || pGamepad->IsButtonPush(CInput::A) == true)
		{
			if (g_nCntPlayer == 0)
			{
				//TEhSE
				pSound->Play(CSound::SOUND_LABEL_SE_SHOT);

				//obgx0
				if (g_nBulletLevel == 0)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x + 40.0f, pos.y, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 40.0f, pos.y, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
				}

				//obgx1
				if (g_nBulletLevel >= 1 && g_nBulletLevel <= 2)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 50.0f, 1.0f), D3DXVECTOR3(0.0f, -20.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 150, 20, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x + 40.0f, pos.y, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 40.0f, pos.y, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
				}

				//obgx1
				if (g_nBulletLevel >= 3 && g_nBulletLevel <= 5)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 50.0f, 1.0f), D3DXVECTOR3(0.0f, -20.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 150, 20, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::InitAngleBullet(D3DXVECTOR3(pos.x + 100.0f, pos.y, 1.0f), -10.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 500, 15, BULLET_SIZE, BULLET_SIZE, g_fAnglePlayerBullet, OBJTYPE_BULET_PLAYER);
					CBullet::InitAngleBullet(D3DXVECTOR3(pos.x - 100.0f, pos.y, 1.0f), -10.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 500, 15, BULLET_SIZE, BULLET_SIZE, g_fAnglePlayerBullet, OBJTYPE_BULET_PLAYER);
				}

				//obgx1
				if (g_nBulletLevel >= 6)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 50.0f, 1.0f), D3DXVECTOR3(0.0f, -20.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::InitAngleBullet(D3DXVECTOR3(pos.x + 100.0f, pos.y, 1.0f), -10.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 500, 13, BULLET_SIZE, BULLET_SIZE, g_fAnglePlayerBullet + 50, OBJTYPE_BULET_PLAYER);
					CBullet::InitAngleBullet(D3DXVECTOR3(pos.x - 100.0f, pos.y, 1.0f), -10.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 500, 13, BULLET_SIZE, BULLET_SIZE, g_fAnglePlayerBullet + 50, OBJTYPE_BULET_PLAYER);
					CBullet::InitAngleBullet(D3DXVECTOR3(pos.x + 100.0f, pos.y, 1.0f), -10.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 500, 13, BULLET_SIZE, BULLET_SIZE, g_fAnglePlayerBullet, OBJTYPE_BULET_PLAYER);
					CBullet::InitAngleBullet(D3DXVECTOR3(pos.x - 100.0f, pos.y, 1.0f), -10.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 500, 13, BULLET_SIZE, BULLET_SIZE, g_fAnglePlayerBullet, OBJTYPE_BULET_PLAYER);
				}
			}

			//obg­Λ
			g_nCntPlayer++;

			//obg­ΛΤu
			if (g_nCntPlayer >= 8)
			{
				g_nCntPlayer = 0;
			}

			//obgxͺ3ΘγΙΘΑ½η
			if (g_nBulletLevel >= 3)
			{
				//pxπΟ¦ι
				if (g_bAnglePlayer == false)
				{
					g_fAnglePlayerBullet += 5.0f;
				}

				if (g_bAnglePlayer == true)
				{
					g_fAnglePlayerBullet -= 5.0f;
				}

				//pxΜ§ΐ
				if (g_fAnglePlayerBullet >= 50)
				{
					g_bAnglePlayer = true;
				}

				if (g_fAnglePlayerBullet <= -50)
				{
					g_bAnglePlayer = false;
				}
			}
		}

		//obgx3Εo»³Ήι
		if (g_nBulletLevel >= 3)
		{
			if (g_nCntPlayerBullet2 == 0)
			{
				//CPolygon::UninitBullet();		//|SNXπΑ·
				g_nCntPlayerBullet = 1;			//ϊ»π?ΉσΤΙ·ι
			}

			//ϊ»σΤ©ηΜt[Θ~
			if (m_nBulletLevelUP == true)
			{
				if (m_nBullet2 == false)
				{
					//x2σΤΙo»·ιAj[V
					CAnimasion::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), 100, 100, 10, 11);
					CAnimasion::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), 100, 100, 10, 11);
					m_nBullet2 = true;
				}
			}

			//xAbvσΤΙ·ι
			m_nBulletLevelUP = true;

			if (m_nBullet2 == true)
			{
				//xAbvItσΤΙ·ι
				m_nBulletLevelUP = false;
			}
		}
	}

	//vC[Μ^Cvͺ4Μ
	if (m_nType == 4)
	{
		//eΜ­Λ(Press)
		if (pInputKeyboard->GetPress(DIK_SPACE) == true || pGamepad->IsButtonPush(CInput::A) == true)
		{
			if (g_nCntPlayer == 0)
			{
				//TEhSE
				pSound->Play(CSound::SOUND_LABEL_SE_SHOT);

				//obgx0
				if (g_nBulletLevel == 0)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 50.0f, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 50.0f, pos.y - 10.0f, 1.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x + 50.0f, pos.y - 10.0f, 1.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
				}

				//obgx1
				if (g_nBulletLevel == 1)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 100.0f, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x + 100.0f, pos.y, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 100.0f, pos.y, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
				}

				//obgx1
				if (g_nBulletLevel >= 2 && g_nBulletLevel <= 4)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 100.0f, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);

					CBullet::Create(D3DXVECTOR3(pos.x + 100.0f, pos.y - 70.0f, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 100.0f, pos.y - 70.0f, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x + 150.0f, pos.y, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 150.0f, pos.y, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
				}

				//obgx1
				if (g_nBulletLevel >= 5)
				{
					//eΜ­Λ
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 100.0f, 1.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 150, 15, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);

					CBullet::Create(D3DXVECTOR3(pos.x + 150.0f, pos.y, 1.0f), D3DXVECTOR3(10.0f, -15.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 150.0f, pos.y, 1.0f), D3DXVECTOR3(-10.0f, -15.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x + 100.0f, pos.y + 70.0f, 1.0f), D3DXVECTOR3(5.0f, -15.0f, 0.0f), D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 100.0f, pos.y + 70.0f, 1.0f), D3DXVECTOR3(-5.0f, -15.0f, 0.0f), D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x + 100.0f, pos.y - 70.0f, 1.0f), D3DXVECTOR3(1.0f, -20.0f, 0.0f), D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
					CBullet::Create(D3DXVECTOR3(pos.x - 100.0f, pos.y - 70.0f, 1.0f), D3DXVECTOR3(-1.0f, -20.0f, 0.0f), D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f), 150, 10, BULLET_SIZE, BULLET_SIZE, OBJTYPE_BULET_PLAYER);
				}
			}

			//obg­Λ
			g_nCntPlayer++;

			//obg­ΛΤu
			if (g_nCntPlayer >= 10)
			{
				g_nCntPlayer = 0;
			}
		}

		//obgx1Εo»³Ήι
		if (g_nBulletLevel == 1)
		{
			if (g_nCntPlayerBullet == 0)
			{
				//CAnimasion::UninitType(13);		//Aj[VNXΜ^Cv13πΑ·
				//CAnimasion::UninitType(5);		//Aj[VNXΜ^Cv5πΑ·
				g_nCntPlayerBullet = 1;
			}

			//ϊ»σΤ©ηΜt[Θ~
			if (m_nBulletLevelUP == true)
			{
				if (m_nBullet == false)
				{
					CAnimasion::UninitTypeClear();
					//x1σΤΙo»·ιAj[V
					CAnimasion::Create(D3DXVECTOR3(0.0f, -100.0f, 0.0f), 100, 100, 10, 13);
					CAnimasion::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), 100, 100, 10, 5);
					CAnimasion::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), 100, 100, 10, 5);

					m_nBullet = true;
				}
			}

			//xAbvσΤΙ·ι
			m_nBulletLevelUP = true;

			if (m_nBullet == true)
			{
				//xAbvItσΤΙ·ι
				m_nBulletLevelUP = false;
			}
		}

		//obgx2Εo»³Ήι
		if (g_nBulletLevel >= 2 && g_nBulletLevel <= 4)
		{
			if (g_nCntPlayerBullet2 == 0)
			{
				//CAnimasion::UninitType(13);		//Aj[VNXΜ^Cv13πΑ·
				//CAnimasion::UninitType(5);		//Aj[VNXΜ^Cv5πΑ·
				g_nCntPlayerBullet2 = 1;
			}

			//ϊ»σΤ©ηΜt[Θ~
			if (m_nBulletLevelUP == true)
			{
				if (m_nBullet2 == false)
				{
					CAnimasion::UninitTypeClear();
					//x2ΘγΜσΤΙo»·ιAj[V
					//CAnimasion::Create(D3DXVECTOR3(0.0f, -100.0f, 0.0f), 100, 100, 10, 13);
					CAnimasion::Create(D3DXVECTOR3(150.0f, 0.0f, 0.0f), 100, 100, 10, 5);
					CAnimasion::Create(D3DXVECTOR3(-150.0f, 0.0f, 0.0f), 100, 100, 10, 5);
					CAnimasion::Create(D3DXVECTOR3(100.0f, -70.0f, 0.0f), 100, 100, 10, 5);
					CAnimasion::Create(D3DXVECTOR3(-100.0f, -70.0f, 0.0f), 100, 100, 10, 5);

					m_nBullet2 = true;
				}
			}

			//xAbvσΤΙ·ι
			m_nBulletLevelUP = true;

			if (m_nBullet2 == true)
			{
				//xAbvItσΤΙ·ι
				m_nBulletLevelUP = false;
			}
		}

		//obgx5Εo»³Ήι
		if (g_nBulletLevel >= 5)
		{
			if (g_nCntPlayerBullet3 == 0)
			{
				//CAnimasion::UninitType(13);		//Aj[VNXΜ^Cv13πΑ·
				//CAnimasion::UninitType(5);		//Aj[VNXΜ^Cv5πΑ·
				g_nCntPlayerBullet3 = 1;
			}

			//ϊ»σΤ©ηΜt[Θ~
			if (m_nBulletLevelUP == true)
			{
				if (m_nBullet3 == false)
				{
					CAnimasion::UninitTypeClear();
					//x5ΘγΜσΤΙo»·ιAj[V
					//CAnimasion::Create(D3DXVECTOR3(0.0f, -100.0f, 0.0f), 100, 100, 10, 13);
					//CAnimasion::Create(D3DXVECTOR3(150.0f, 0.0f, 0.0f), 100, 100, 10, 5);
					//CAnimasion::Create(D3DXVECTOR3(-150.0f, 0.0f, 0.0f), 100, 100, 10, 5);
					CAnimasion::Create(D3DXVECTOR3(100.0f, 70.0f, 0.0f), 100, 100, 10, 5);
					CAnimasion::Create(D3DXVECTOR3(-100.0f, 70.0f, 0.0f), 100, 100, 10, 5);
					//CAnimasion::Create(D3DXVECTOR3(100.0f, -70.0f, 0.0f), 100, 100, 10, 5);
					//CAnimasion::Create(D3DXVECTOR3(-100.0f, -70.0f, 0.0f), 100, 100, 10, 5);

					m_nBullet3 = true;
				}
			}

			//xAbvσΤΙ·ι
			m_nBulletLevelUP = true;

			if (m_nBullet3 == true)
			{
				//xAbvItσΤΙ·ι
				m_nBulletLevelUP = false;
			}
		}
	}

	//Ϊ?§ΐ
	if (pos.x >= SCREEN_WIDTH)
	{
		pos.x = SCREEN_WIDTH;
	}
	if (pos.x <= 0)
	{
		pos.x = 0;
	}

	if (pos.y >= SCREEN_HEIGHT)
	{
		pos.y = SCREEN_HEIGHT;
	}
	if (pos.y <= 0)
	{
		pos.y = 0;
	}

	pos += m_move;

	//ΚuξρπoΟΙόκι
	g_pos = pos;
	m_pos = pos;

	//Ϊ?ΚΜΈ
	m_move.x += (0 - m_move.x) * 0.3f;
	m_move.y += (0 - m_move.y) * 0.3f;

	//Ϊ?³Ήι
	SetPosition(pos);

	//XV
	CScene2D::Update();
}

//=============================================================================
// `ζ
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// vC[πΆ¬
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, int nLife, float fSizeX, float fSizeY)
{
	// [JΟιΎ
	CPlayer *pPlayer = NULL;
	pPlayer = new CPlayer;

	// ϊ»
	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, nLife, fSizeX, fSizeY);
	}

	// eNX`θΔ
	pPlayer->BindTexture(m_pTexture[CManager::GetPlayerType()]);

	return pPlayer;
}

//=============================================================================
// eNX`Μ[h
//=============================================================================
HRESULT CPlayer::Load(void)
{
	// foCXΜζΎ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// eNX`ΜΗέέ
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_01.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_02.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_03.png", &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_04.png", &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_05.png", &m_pTexture[4]);

	return S_OK;
}

//=============================================================================
// eNX`ΜA[h
//=============================================================================
void CPlayer::Unload(void)
{
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// obgx
//=============================================================================
void CPlayer::BulletLevel(void)
{
	g_nBulletLevel++;
}

void CPlayer::SetBulletLevel(int nData)
{
	g_nBulletLevel = nData;
}

//=============================================================================
// Get&SetΦ
//=============================================================================
bool CPlayer::GetBumped(void)
{
	return g_bBumpedPlayer;
}
void CPlayer::SetBumped(bool bBumped)
{
	g_bBumpedPlayer = bBumped;
}

//=============================================================================
// GetΦ
//=============================================================================
D3DXVECTOR3 CPlayer::GetPlayer(void)
{
	return g_pos;
}
