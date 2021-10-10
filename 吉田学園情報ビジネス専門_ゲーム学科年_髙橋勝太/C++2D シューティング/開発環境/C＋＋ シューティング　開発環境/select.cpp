//=============================================================================
//
// ���C������ [select.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "bg.h"
#include "input.h"
#include "manager.h"
#include "scene2D.h"
#include "logo.h"
#include "animation.h"
#include "polygon.h"
#include "select.h"
#include "fade.h"

//�O���[�o��
int g_nPointerSelectY = 0;
int g_nOldPinterY = 0;
bool g_bUseKeyDown = false;
bool g_bButtonDownSelect = false;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CSelect::CSelect()
{
	//������
	g_nPointerSelectY = 0;
	g_nOldPinterY = 0;
	g_bUseKeyDown = false;
	g_bButtonDownSelect = false;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CSelect::~CSelect()
{

}

//==============================================================================
// ����������
//==============================================================================
HRESULT CSelect::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	//�w�i��\��
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 130, 130, 9);

	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 800.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 100, 100, 13);			//3
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 400.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 100, 100, 14);			//4
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 100, 100, 10);					//0
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 400.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 100, 100, 11);			//1
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 800.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 100, 100, 12);			//2

	//�X�e�[�^�X�\��
	CLogo::Create(D3DXVECTOR3(300.0f, 500.0f, 0.0f), 200, 100, 15);
	CLogo::Create(D3DXVECTOR3(1200.0f, 700.0f, 0.0f), 600, 300, 20);

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CSelect::Uninit(void)
{
	// �I�u�W�F�N�g�j��
	Release();
}

//==============================================================================
// �X�V����
//==============================================================================
void CSelect::Update(void)
{
	//�L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	//D�������������ꍇ
	if (pInputKeyboard->GetTrigger(DIK_D) == true || CGamepad::IsButtonDown(RIGHT))
	{
		g_bUseKeyDown = true;

		if (g_nPointerSelectY == 0)
		{
			g_nPointerSelectY = 1;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2 + 400.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 9);
		}

		else if (g_nPointerSelectY == 1)
		{
			g_nPointerSelectY = 2;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2 + 800.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 9);
		}

		else if (g_nPointerSelectY == 2)
		{
			g_nPointerSelectY = 3;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2 - 800.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 9);
		}

		else if (g_nPointerSelectY == 3)
		{
			g_nPointerSelectY = 4;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2 - 400.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 9);
		}

		else if (g_nPointerSelectY == 4)
		{
			g_nPointerSelectY = 0;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 9);
		}

		//�T�E���hSE
		pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
	}

	//A�������������ꍇ
	if (pInputKeyboard->GetTrigger(DIK_A) == true || CGamepad::IsButtonDown(LEFT))
	{
		g_bUseKeyDown = true;

		if (g_nPointerSelectY == 0)
		{
			g_nPointerSelectY = 4;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2 - 400.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 9);
		}

		else if (g_nPointerSelectY == 1)
		{
			g_nPointerSelectY = 0;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 9);
		}

		else if (g_nPointerSelectY == 2)
		{
			g_nPointerSelectY = 1;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2 + 400.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 9);
		}

		else if (g_nPointerSelectY == 3)
		{
			g_nPointerSelectY = 2;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2 + 800.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 9);
		}

		else if (g_nPointerSelectY == 4)
		{
			g_nPointerSelectY = 3;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2 - 800.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f), 9);
		}

		//�T�E���hSE
		pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
	}

	//�X�e�[�^�X�ݒ�
	if (g_bUseKeyDown == true)
	{
		//�\������Ă���X�e�[�^�X������
		if (g_nOldPinterY == 0)
		{
			CLogo::TypeUninit(15);
			CLogo::TypeUninit(20);
		}

		if (g_nOldPinterY == 1)
		{
			CLogo::TypeUninit(16);
			CLogo::TypeUninit(21);
		}

		if (g_nOldPinterY == 2)
		{
			CLogo::TypeUninit(17);
			CLogo::TypeUninit(22);
		}

		if (g_nOldPinterY == 3)
		{
			CLogo::TypeUninit(18);
			CLogo::TypeUninit(23);
		}

		if (g_nOldPinterY == 4)
		{
			CLogo::TypeUninit(19);
			CLogo::TypeUninit(24);
		}

		//�O�̃|�C���^�[���L��
		g_nOldPinterY = g_nPointerSelectY;
		
		//�X�e�[�^�X��\��
		if (g_nPointerSelectY == 0)
		{
			CLogo::Create(D3DXVECTOR3(300.0f, 500.0f, 0.0f), 200, 100, 15);
			CLogo::Create(D3DXVECTOR3(1200.0f, 700.0f, 0.0f), 600, 300, 20);
		}

		if (g_nPointerSelectY == 1)
		{
			CLogo::Create(D3DXVECTOR3(300.0f, 500.0f, 0.0f), 200, 100, 16);
			CLogo::Create(D3DXVECTOR3(1200.0f, 700.0f, 0.0f), 600, 300, 21);
		}

		if (g_nPointerSelectY == 2)
		{
			CLogo::Create(D3DXVECTOR3(300.0f, 500.0f, 0.0f), 200, 100, 17);
			CLogo::Create(D3DXVECTOR3(1200.0f, 700.0f, 0.0f), 600, 300, 22);
		}

		if (g_nPointerSelectY == 3)
		{
			CLogo::Create(D3DXVECTOR3(300.0f, 500.0f, 0.0f), 200, 100, 18);
			CLogo::Create(D3DXVECTOR3(1200.0f, 700.0f, 0.0f), 600, 300, 23);
		}

		if (g_nPointerSelectY == 4)
		{
			CLogo::Create(D3DXVECTOR3(300.0f, 500.0f, 0.0f), 200, 100, 19);
			CLogo::Create(D3DXVECTOR3(1200.0f, 700.0f, 0.0f), 600, 300, 24);
		}

		g_bUseKeyDown = false;
	}

	//�v���C���[�̃^�C�v
	CManager::SetPlayerType(g_nPointerSelectY);

	//���߂ĉ������Ƃ�
	if (g_bButtonDownSelect == false)
	{
		//��ʑJ��
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || CGamepad::IsButtonDown(A) || CGamepad::IsButtonDown(B) == true)
		{
			//���[�h�ݒ�
			//CManager::SetMode(CManager::MODE_GAME);
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �V�[���J��

			//�A�Ŗh�~
			g_bButtonDownSelect = true;

			//�T�E���hSE
			pSound->Play(CSound::SOUND_LABEL_SE_DECISION);
		}
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void CSelect::Draw(void)
{

}

//==============================================================================
// ��������
//==============================================================================
CSelect * CSelect::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �|�C���^�ϐ��̐���
	CSelect *pSelect;
	pSelect = new CSelect;

	// NULL�`�F�b�N
	if (pSelect != NULL)
	{
		pSelect->Init(pos, fSizeX, fSizeY);
	}

	return pSelect;
}
