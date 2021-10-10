//=============================================================================
//
// ���C������ [pause.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "pause.h"
#include "logo.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "animation.h"
#include "fade.h"

int nTimeGamePause = 0;
int nTimeCounterPause = 0;
int g_nPointerPauseX = 0;
bool g_bButtonDownPause = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPause::CPause(int nPriority, int nType) : CScene(nPriority, nType)
{
	//������
	g_nPointerPauseX = 0;
	g_bButtonDownPause = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPause::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�w�i
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 31);

	//�t���[��
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), 210, 60, 9);

	//���S
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), 200, 50, 28);

	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 200, 50, 29);

	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), 200, 50, 30);//�w�i��\��

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPause::Uninit(void)
{
	// �I�u�W�F�N�g�j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPause::Update(void)
{
	//�L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	//��ʑJ�ڂ��n�܂��ĂȂ��ꍇ
	if (g_bButtonDownPause == false)
	{
		//S�������������ꍇ
		if (pInputKeyboard->GetTrigger(DIK_S) == true || CGamepad::IsButtonDown(DOWN))
		{
			if (g_nPointerPauseX == 0)
			{
				g_nPointerPauseX = 1;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 9);
			}

			else if (g_nPointerPauseX == 1)
			{
				g_nPointerPauseX = 2;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), 9);
			}

			else if (g_nPointerPauseX == 2)
			{
				g_nPointerPauseX = 0;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 9);
			}

			//�T�E���hSE
			pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
		}

		//W�������������ꍇ
		if (pInputKeyboard->GetTrigger(DIK_W) == true || CGamepad::IsButtonDown(UP))
		{
			if (g_nPointerPauseX == 0)
			{
				g_nPointerPauseX = 2;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), 9);
			}

			else if (g_nPointerPauseX == 1)
			{
				g_nPointerPauseX = 0;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), 9);
			}

			else if (g_nPointerPauseX == 2)
			{
				g_nPointerPauseX = 1;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 9);
			}

			//�T�E���hSE
			pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
		}

		//��ʑJ��
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || CGamepad::IsButtonDown(A) || CGamepad::IsButtonDown(B) == true)
		{
			if (g_nPointerPauseX == 0)
			{
				//Stage1�ŃQ�[���I�[�o�[�ɂȂ����ꍇ
				if (CManager::GetGameStage() == 1)
				{
					//Stage1�ɑJ�ڂ���
					CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));	// �V�[���J��
				}

				//Stage1�ŃQ�[���I�[�o�[�ɂȂ����ꍇ
				if (CManager::GetGameStage() == 2)
				{
					//Stage2�ɑJ�ڂ���
					CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME2, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.0f));	// �V�[���J��
				}
			}

			if (g_nPointerPauseX == 1)
			{
				//���[�h�ݒ�
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_SELECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �V�[���J��
			}

			if (g_nPointerPauseX == 2)
			{
				//���[�h�ݒ�
				//CManager::SetMode(CManager::MODE_TITLE);
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �V�[���J��
			}

			//��ʑJ�ڂ��n�܂���
			g_bButtonDownPause = true;

			//�T�E���hSE
			pSound->Play(CSound::SOUND_LABEL_SE_DECISION);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPause::Draw(void)
{

}

//=============================================================================
// ��������
//=============================================================================
CPause * CPause::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �|�C���^�ϐ��̐���
	CPause *pPause;
	pPause = new CPause;

	// NULL�`�F�b�N
	if (pPause != NULL)
	{
		pPause->Init(pos, fSizeX, fSizeY);
	}

	return pPause;
}
