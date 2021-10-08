//=============================================================================
//
// ���C������ [game.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "player.h"
#include "score.h"
#include "enemy.h"
#include "polygon.h"
#include "life.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "item.h"
#include "fade.h"
#include "logo.h"

//�}�N����`
#define WAVE_1		(100)		
#define WAVE_2		(21)	
#define WAVE_3		(00)	

//����
int nTimeGame = 0;
int nTimeCounter = 0;

//�G��|������
int g_nDaed = 0;
bool g_bDead = false;

bool g_bDaed[2] = {};

//��ʑJ�ڗp
bool g_bMigrate = false;		

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CGame::CGame()
{
	//������
	nTimeGame = 0;
	nTimeCounter = 0;

	g_bMigrate = false;		//��ʑJ�ڗp
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CGame::~CGame()
{

}

//==============================================================================
// ����������
//==============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���hBGM
	pSound->Play(CSound::SOUND_LABEL_BGM003);

	// �t�H���g�I�u�W�F�N�g�̐���
	D3DXCreateFont(pDevice, 36, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pTimeFontGame);

	//���݂̃X�e�[�W��Manaager�ɋL��������
	CManager::SetGameStage(1);

	//�N���A����������
	CManager::SetEnemyDead(0);

	//����U�����I�t�ɂ���
	CEnemy::NextAttack(0);

	//�v���C���[�̐���
	CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), MAX_LIFE, PLAYER_SIZE, PLAYER_SIZE);

	//�w�i��\��
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//HP�o�[
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		CLife::Create(D3DXVECTOR3(40.0f + (80.0f * nCnt), 100.0f, 0.0f), 30.0f, 30.0f);
	}

	//�X�R�A
	CScore::Create(D3DXVECTOR3(1800.0f, 50.0f, 0.0f), 100.0f, 100.0f);

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CGame::Uninit(void)
{
	//�T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�ݒu
	pSound->Stop(CSound::SOUND_LABEL_BGM003);

	// �I�u�W�F�N�g�j��
	Release();
}

//==============================================================================
// �X�V����
//==============================================================================
void CGame::Update(void)
{
	//�L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�J�E���g
	nTimeCounter++;

	//�J�E���^�[��60�ȏ�ɂȂ�����
	if (nTimeCounter >= 60)
	{
		nTimeGame++;

		//�J�E���^�[��߂�
		nTimeCounter = 0;
	}

	//�G�̏o�����U���Ɋւ���
	Attack2();

	//���{�X��1�̓|�����ꍇ
	if (CManager::GetEnemyDead() == 11)		//�����𖞂����Ă���ꍇ
	{
		//��ʑJ�ڏ���
		if (g_bMigrate == false)
		{
			g_bMigrate = true;
			nTimeGame = 100;
			nTimeCounter = 0;
		}
	}

	//�G��|���Ă���2�b�o�ߌ�ɉ�ʑJ��
	if (g_bMigrate == true)
	{
		if (nTimeGame == 103 && nTimeCounter == 0)
		{
			//��ʑJ��
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME2, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));	// �V�[���J��
		}
	}

	//�G��|���؂����ꍇ�Ƀ^�C���X�L�b�v
	if (g_bDead == false)
	{
		if (CManager::GetEnemyDead() == 2)		//�����𖞂����Ă���ꍇ
		{
			if (nTimeGame < 20)
			{
				g_nDaed = CManager::GetEnemyDead();
				g_bDead = true;
				nTimeGame = 20;		//�^�C���X�L�b�v
			}
		}

		if (CManager::GetEnemyDead() == 10)		//�����𖞂����Ă���ꍇ
		{
			if (nTimeGame < 42)
			{
				g_nDaed = CManager::GetEnemyDead();
				g_bDead = true;
				nTimeGame = 42;		//�^�C���X�L�b�v
			}
		}
	}

	//�l���ω������ꍇ�ɏ���������
	if (g_nDaed != CManager::GetEnemyDead())
	{
		g_bDead = false;
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void CGame::Draw(void)
{
#ifdef _DEBUG
	// ���[�J���ϐ��錾
	RECT rect = { -1500,30,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//��ʂɕ\��������
	sprintf(&aStr[0], "GAME��ʂ̌o�ߎ��� : %d\n", CManager::GetEnemyDead());

	// �e�L�X�g�̕`��
	m_pTimeFontGame->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 255, 255, 255));
#endif
}

//==============================================================================
//�G�̈ړ��Ǘ�
//==============================================================================
void CGame::Attack(void)
{
	if (nTimeGame == 1 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(800.0f, -100.0f, 0.0f), 15.0f, D3DXVECTOR3(300.0f, 400.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 8, ENEMY_01, 1);
		CEnemy::Create(D3DXVECTOR3(800.0f, -200.0f, 0.0f), 15.0f, D3DXVECTOR3(300.0f, 300.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 8, ENEMY_01, 2);
		CEnemy::Create(D3DXVECTOR3(800.0f, -300.0f, 0.0f), 15.0f, D3DXVECTOR3(300.0f, 200.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 8, ENEMY_01, 3);
		CEnemy::Create(D3DXVECTOR3(800.0f, -400.0f, 0.0f), 15.0f, D3DXVECTOR3(300.0f, 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 8, ENEMY_01, 4);
	}

	if (nTimeGame == 4 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 10.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 8, ENEMY_01, 0);
		}
	}

	if (nTimeGame == 3 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(1000.0f, 800.0f, 0.0f), 15.0f, 1);
	}

	if (nTimeGame == 3 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(1000.0f, 700.0f, 0.0f), 15.0f, 2);
	}

	if (nTimeGame == 3 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 15.0f, 3);
	}

	if (nTimeGame == 3 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), 15.0f, 4);
	}

	if (nTimeGame == 5 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(1800.0f, 400.0f, 0.0f), 15.0f, 1);
	}

	if (nTimeGame == 5 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(1700.0f, 300.0f, 0.0f), 15.0f, 2);
	}

	if (nTimeGame == 5 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(1600.0f, 200.0f, 0.0f), 15.0f, 3);
	}

	if (nTimeGame == 5 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(1500.0f, 100.0f, 0.0f), 15.0f, 4);
	}

	if (nTimeGame == 5 && nTimeCounter == 4)
	{
		//CEnemy::MoveClear();
	}

	if (nTimeGame == 9 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(800.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(300.0f, 200.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 18, ENEMY_01, 1);
		CEnemy::Create(D3DXVECTOR3(800.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 400.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 18, ENEMY_01, 2);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 200.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 18, ENEMY_01, 3);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 400.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 18, ENEMY_01, 4);
	}

	if (nTimeGame == 10 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 10.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 14, ENEMY_01, 0);
		}
	}

	if (nTimeGame == 13 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(800.0f, 400.0f, 0.0f), 15.0f, 1);
	}

	if (nTimeGame == 13 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(800.0f, 300.0f, 0.0f), 15.0f, 2);
	}

	if (nTimeGame == 13 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 400.0f, 0.0f), 15.0f, 3);
	}

	if (nTimeGame == 13 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 300.0f, 0.0f), 15.0f, 4);
	}

	if (nTimeGame == 13 && nTimeCounter == 4)
	{
		//CEnemy::MoveClear();
	}

	if (nTimeGame == 15 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(800.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(300.0f, 300.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 19, ENEMY_01, 5);
		CEnemy::Create(D3DXVECTOR3(800.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(500.0f, 200.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 19, ENEMY_01, 6);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 300.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 20, ENEMY_01, 7);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 500.0f, 200.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 20, ENEMY_01, 8);
	}

	if (nTimeGame == 16 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 3.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 20, ENEMY_01, 0);
		}
	}

	if (nTimeGame == 20 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(800.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(300.0f, 300.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 26, ENEMY_01, 1);
		CEnemy::Create(D3DXVECTOR3(800.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(300.0f, 200.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 26, ENEMY_01, 2);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 300.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 26, ENEMY_01, 3);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 200.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 26, ENEMY_01, 4);
	}

	if (nTimeGame == 22 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(800.0f, 800.0f, 0.0f), 5.0f, 1);
	}

	if (nTimeGame == 22 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(800.0f, 900.0f, 0.0f), 5.0f, 2);
	}

	if (nTimeGame == 22 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 800.0f, 0.0f), 5.0f, 3);
	}

	if (nTimeGame == 22 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 900.0f, 0.0f), 5.0f, 4);
	}

	if (nTimeGame == 25 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(500.0f, 400.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 25 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(400.0f, 500.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 25 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, 400.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 25 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, 500.0f, 0.0f), 10.0f, 4);
		
		CEnemy::MoveClear();
	}

	if (nTimeGame == 27 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(800.0f, 400.0f, 0.0f), 200, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_02, 1);
		CEnemy::Create(D3DXVECTOR3(1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(800.0f, 200.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_03, 2);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 400.0f, 0.0f),200, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_02, 3);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 200.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_03, 4);
	}

	if (nTimeGame == 28 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 100.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 28 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(300.0f, 100.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 28 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(400.0f, 100.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 28 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(500.0f, 100.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 30 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, 300.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 30 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, 300.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 30 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 300.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 30 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 100.0f, 300.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 32 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(100.0f, 600.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 32 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(300.0f, 600.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 32 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(500.0f, 600.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 32 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(700.0f, 600.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 35 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(100.0f, 200.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 35 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(300.0f, 200.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 35 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(500.0f, 200.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 35 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(700.0f, 200.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 30 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 3.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 42, ENEMY_01, 0);
		}
	}

	if (nTimeGame == 35 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 3.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 42, ENEMY_01, 0);
		}
	}

	if (nTimeGame == 38 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 3.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 42, ENEMY_01, 0);
		}

		CEnemy::MoveClear();
	}

	if (nTimeGame == 42 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 200.0f, 0.0f), 200, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
		CEnemy::Create(D3DXVECTOR3(1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(300.0f, 400.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
		CEnemy::Create(D3DXVECTOR3(1000.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(1000.0f, 400.0f, 0.0f), 200, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
		CEnemy::Create(D3DXVECTOR3(1000.0f, -400.0f, 0.0f), 8.0f, D3DXVECTOR3(1100.0f, 200.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 200.0f, 0.0f), 200, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 400.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, 400.0f, 0.0f), 200, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -400.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 1100.0f, 200.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
	}

	if (nTimeGame == 50 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 3.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 57, ENEMY_01, 0);
		}
	}

	if (nTimeGame == 58 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 5.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 68, ENEMY_02, 0);
		}
	}

	if (nTimeGame == 62 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 3.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 68, ENEMY_01, 0);
		}
	}

	if (nTimeGame == 70 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 400.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 1);
		CEnemy::Create(D3DXVECTOR3(1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 300.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 2);
		CEnemy::Create(D3DXVECTOR3(1000.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 3);
		CEnemy::Create(D3DXVECTOR3(1000.0f, -400.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 100.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 4);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 1000.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 5);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 900.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 6);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 800.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 7);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -400.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 700.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 8);
	}

	//����U���ɕύX
	if (nTimeGame == 73 && nTimeCounter == 0)
	{
		CEnemy::NextAttack(2);
	}

	if (nTimeGame == 74 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 400.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 74 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 300.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 74 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 200.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 74 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 100.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 74 && nTimeCounter == 4)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 1000.0f, 0.0f), 10.0f, 5);
	}

	if (nTimeGame == 74 && nTimeCounter == 5)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 900.0f, 0.0f), 10.0f, 6);
	}

	if (nTimeGame == 74 && nTimeCounter == 6)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 800.0f, 0.0f), 10.0f, 7);
	}

	if (nTimeGame == 74 && nTimeCounter == 7)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 700.0f, 0.0f), 10.0f, 8);
	}

	//�ړ�
	if (nTimeGame == 78 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 700.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 78 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 800.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 78 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 900.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 78 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 1000.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 78 && nTimeCounter == 4)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 100.0f, 0.0f), 10.0f, 5);
	}

	if (nTimeGame == 78 && nTimeCounter == 5)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 200.0f, 0.0f), 10.0f, 6);
	}

	if (nTimeGame == 78 && nTimeCounter == 6)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 300.0f, 0.0f), 10.0f, 7);
	}

	if (nTimeGame == 78 && nTimeCounter == 7)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 400.0f, 0.0f), 10.0f, 8);
	}

	//����U���ɕύX
	if (nTimeGame == 81 && nTimeCounter == 50)
	{
		CEnemy::NextAttack(3);
	}

	//�ړ�
	if (nTimeGame == 82 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 1000.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 82 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, 1000.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 82 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 600.0f, 1000.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 82 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 1000.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 82 && nTimeCounter == 4)
	{
		CEnemy::NextMove(D3DXVECTOR3(800.0f, 100.0f, 0.0f), 10.0f, 5);
	}

	if (nTimeGame == 82 && nTimeCounter == 5)
	{
		CEnemy::NextMove(D3DXVECTOR3(600.0f, 100.0f, 0.0f), 10.0f, 6);
	}

	if (nTimeGame == 82 && nTimeCounter == 6)
	{
		CEnemy::NextMove(D3DXVECTOR3(400.0f, 100.0f, 0.0f), 10.0f, 7);
	}

	if (nTimeGame == 82 && nTimeCounter == 7)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 100.0f, 0.0f), 10.0f, 8);
	}

	//����U���ɕύX
	if (nTimeGame == 85 && nTimeCounter == 50)
	{
		CEnemy::NextAttack(4);
	}

	//�ړ�
	if (nTimeGame == 86 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 600.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 86 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 600.0f, 400.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 86 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, 200.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 86 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 100.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 86 && nTimeCounter == 4)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 200.0f, 0.0f), 10.0f, 5);
	}

	if (nTimeGame == 86 && nTimeCounter == 5)
	{
		CEnemy::NextMove(D3DXVECTOR3(400.0f, 400.0f, 0.0f), 10.0f, 6);
	}

	if (nTimeGame == 86 && nTimeCounter == 6)
	{
		CEnemy::NextMove(D3DXVECTOR3(600.0f, 600.0f, 0.0f), 10.0f, 7);
	}

	if (nTimeGame == 86 && nTimeCounter == 7)
	{
		CEnemy::NextMove(D3DXVECTOR3(800.0f, 800.0f, 0.0f), 10.0f, 8);
	}

	//����U���ɕύX
	if (nTimeGame == 90 && nTimeCounter == 0)
	{
		CEnemy::NextAttack(0);
	}

	//覐�
	if (nTimeGame >= 90 && nTimeGame <= 150)
	{
		int nRand = rand() % 50;
		int nRandX = rand() % SCREEN_WIDTH - 300.0f;

		if (nRand == 1)
		{
			//�G����
			CEnemy::Create(D3DXVECTOR3(nRandX + 150.0f, -50.0f, 0.0f), 2.0f, D3DXVECTOR3(nRandX + 150.0f, 2000.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 1, ENEMY_99, 0);
		}
	}

	if (nTimeGame == 94 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 500.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 - 500.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 1);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 - 600.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 2);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 3);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 + 600.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 4);
	}

	//�ړ�
	if (nTimeGame == 96 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, 600.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 96 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300.0f, 600.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 96 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, 600.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 96 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH / 2 + 300.0f, 600.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 98 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 500.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 - 800.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 - 900.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 + 800.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 + 900.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
	}

	if (nTimeGame == 102 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 500.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 - 800.0f, 800.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 - 900.0f, 1000.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 + 800.0f, 800.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 + 900.0f, 1000.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
	}

	//����U���ɕύX
	if (nTimeGame == 105 && nTimeCounter == 0)
	{
		CEnemy::NextAttack(4);
	}

	//����U���ɕύX
	if (nTimeGame == 122 && nTimeCounter == 0)
	{
		CEnemy::NextAttack(0);
	}

	if (nTimeGame == 123 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 - 500.0f, 300.0f, 0.0f), 3000, ENEMY_SIZE + 100, ENEMY_SIZE + 100, 120, ENEMY_05, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, 300.0f, 0.0f), 3000, ENEMY_SIZE + 100, ENEMY_SIZE + 100, 120, ENEMY_05, 0);
	}

	//����U���ɕύX
	if (nTimeGame == 125 && nTimeCounter == 0)
	{
		CEnemy::NextAttack(5);
	}

	//����U���ɕύX
	if (nTimeGame == 130 && nTimeCounter == 0)
	{
		CEnemy::NextAttack(6);
	}

	if (nTimeGame == 131 && nTimeCounter == 0)
	{
		//���[�h�ݒ�
		CManager::SetMode(CManager::MODE_GAME2);
	}
}

void CGame::Attack2(void)
{
	///�����_���ɃA�C�e���𐶐�
	int nRand = rand() % 1000;
	int nRandX = rand() % SCREEN_WIDTH;

	if (nRand == 1)
	{
		//�A�C�e������
		CItem::Create(D3DXVECTOR3(nRandX, 0.0f, 0.0f), 2.0f, 50, 50, 0);
	}

	else if (nRand == 2 || nRand == 3)
	{
		//�A�C�e������
		CItem::Create(D3DXVECTOR3(nRandX, 0.0f, 0.0f), 2.0f, 50, 50, 1);
	}

	//1
	{
		if (nTimeGame == 1 && nTimeCounter == 0)
		{
			CEnemy::Create(D3DXVECTOR3(800.0f, -100.0f, 0.0f), 5.0f, D3DXVECTOR3(700.0f, 200.0f, 0.0f), 800, ENEMY_SIZE, ENEMY_SIZE, 20, ENEMY_06, 0);
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, -100.0f, 0.0f), 5.0f, D3DXVECTOR3(SCREEN_WIDTH - 700.0f, 200.0f, 0.0f), 800, ENEMY_SIZE, ENEMY_SIZE, 20, ENEMY_07, 0);
		}

		//����U���ɕύX
		if (nTimeGame == 2 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(8);
		}
	}

	//2
	{
		if (nTimeGame == WAVE_2 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(0);		//����U���ɕύX
			CEnemy::Create(D3DXVECTOR3(1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 400.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 1);
			CEnemy::Create(D3DXVECTOR3(1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 300.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 2);
			CEnemy::Create(D3DXVECTOR3(1000.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 200.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 3);
			CEnemy::Create(D3DXVECTOR3(1000.0f, -400.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 100.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 4);
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 1000.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 5);
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 900.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 6);
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 800.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 7);
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -400.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 700.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 8);
		}

		//����U���ɕύX
		if (nTimeGame == WAVE_2 + 1 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(2);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 0)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 400.0f, 0.0f), 10.0f, 1);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 1)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 300.0f, 0.0f), 10.0f, 2);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 2)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 200.0f, 0.0f), 10.0f, 3);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 3)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 100.0f, 0.0f), 10.0f, 4);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 4)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 1000.0f, 0.0f), 10.0f, 5);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 5)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 900.0f, 0.0f), 10.0f, 6);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 6)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 800.0f, 0.0f), 10.0f, 7);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 7)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 700.0f, 0.0f), 10.0f, 8);
		}

		//�ړ�
		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 0)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 700.0f, 0.0f), 10.0f, 1);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 1)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 800.0f, 0.0f), 10.0f, 2);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 2)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 900.0f, 0.0f), 10.0f, 3);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 3)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 1000.0f, 0.0f), 10.0f, 4);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 4)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 100.0f, 0.0f), 10.0f, 5);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 5)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 200.0f, 0.0f), 10.0f, 6);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 6)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 300.0f, 0.0f), 10.0f, 7);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 7)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 400.0f, 0.0f), 10.0f, 8);
		}

		//����U���ɕύX
		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(3);
		}

		//�ړ�
		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 0)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 1000.0f, 0.0f), 10.0f, 1);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 1)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, 1000.0f, 0.0f), 10.0f, 2);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 2)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 600.0f, 1000.0f, 0.0f), 10.0f, 3);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 3)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 1000.0f, 0.0f), 10.0f, 4);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 4)
		{
			CEnemy::NextMove(D3DXVECTOR3(800.0f, 100.0f, 0.0f), 10.0f, 5);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 5)
		{
			CEnemy::NextMove(D3DXVECTOR3(600.0f, 100.0f, 0.0f), 10.0f, 6);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 6)
		{
			CEnemy::NextMove(D3DXVECTOR3(400.0f, 100.0f, 0.0f), 10.0f, 7);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 7)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 100.0f, 0.0f), 10.0f, 8);
		}

		//����U���ɕύX
		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(10);
		}

		//�ړ�
		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 0)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 600.0f, 0.0f), 10.0f, 1);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 1)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 600.0f, 400.0f, 0.0f), 10.0f, 2);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 2)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, 200.0f, 0.0f), 10.0f, 3);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 3)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 100.0f, 0.0f), 10.0f, 4);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 4)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 200.0f, 0.0f), 10.0f, 5);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 5)
		{
			CEnemy::NextMove(D3DXVECTOR3(400.0f, 400.0f, 0.0f), 10.0f, 6);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 6)
		{
			CEnemy::NextMove(D3DXVECTOR3(600.0f, 600.0f, 0.0f), 10.0f, 7);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 7)
		{
			CEnemy::NextMove(D3DXVECTOR3(800.0f, 100.0f, 0.0f), 10.0f, 8);
		}
	}

	//�A�C�e������
	if (nTimeGame == 42 && nTimeCounter == 0)
	{
		CItem::Heart2(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f), 2.0f, 50, 50, 1, 0);
	}

	//3
	{
		if (nTimeGame == 45 && nTimeCounter == 0)
		{
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -100.0f, 0.0f), 5.0f, D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f), 5000, ENEMY_SIZE + 50, ENEMY_SIZE + 50, 999, ENEMY_05, 1);
		}

		//����U���ɕύX
		if (nTimeGame == 46 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(9);
		}

		//����U���ɕύX
		if (nTimeGame == 53 && nTimeCounter == 0)
		{
			CEnemy::NextAttack2(11);
		}
	}
}

//==============================================================================
// Get�֐��^�C��
//==============================================================================
int CGame::GetTime(void)
{
	return nTimeGame;
}

//==============================================================================
// ��������
//==============================================================================
CGame * CGame::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �|�C���^�ϐ��̐���
	CGame *pGame;
	pGame = new CGame;

	// NULL�`�F�b�N
	if (pGame != NULL)
	{
		pGame->Init(pos, fSizeX, fSizeY);
	}

	return pGame;
}
