//=============================================================================
//
// ���C������ [input.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "input.h"
#include "main.h"

//�ÓI�����o�ϐ�
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CInput::~CInput()
{

}

//=============================================================================
//�@����������
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr = S_FALSE;
	if (m_pInput == NULL)
	{
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}

	return hr;
}

//=============================================================================
//�@�I������
//=============================================================================
void CInput::Uninit(void)
{
	//�f�[�^�t�H�[�}�b�g�̊J��
	if (m_pDevice != NULL)
	{
		//�A�N�Z�X���̔j��
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
//�@�L�[�{�[�h���� �p����input
//=============================================================================

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	//m_aKeyState[256] = 0;
	//m_aKeyStateTrigger[256] = 0;
	//m_aKeyStateRelease[256] = 0;
	//m_aKeyStateRepeat[256] = 0;

	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyStateRelease));
	memset(&m_aKeyStateRepeat[0], 0, sizeof(m_aKeyStateRepeat));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=============================================================================
//�@����������
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h�̐ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�A�N�Z�X���̎擾
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
//�@�I������
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
//�@�X�V����
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[256];
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < 256; nKey++)
		{
			//�������Ƃ�
			m_aKeyStateTrigger[nKey] = (~m_aKeyState[nKey]) & aKeyState[nKey];

			//�������Ƃ�
			m_aKeyStateRelease[nKey] = m_aKeyState[nKey] & (~aKeyState[nKey]);

			//�����������Ƃ�
			m_aKeyState[nKey] = aKeyState[nKey];
		}
	}

	else
	{
		//�A�N�Z�X���̎擾
		m_pDevice->Acquire();
	}
}

//=============================================================================
//�@�v���X
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
//�@�g���K�[
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
//�@�����[�X
//=============================================================================
bool CInputKeyboard::GetReleace(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
