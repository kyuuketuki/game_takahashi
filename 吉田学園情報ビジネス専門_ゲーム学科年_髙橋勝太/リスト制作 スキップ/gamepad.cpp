//==============================================================================
//
// ���͏����i�Q�[���p�b�h�j�kgamepad.cpp�l
// AUTHOR : takahashi shouta
//
//==============================================================================
#include "input.h"
#include "gamepad.h"

// �}�N����`
#define MAX_CONTROLLER	(2)

typedef struct
{
	LPDIRECTINPUTDEVICE8 Device;
	ButtonState ButtonStates[KEYINFO::KEYINFO_MAX];
}Controller;

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
static LPDIRECTINPUT8 g_InputInterface;
Controller g_Control[MAX_CONTROLLER];
int g_nController = 0;

//==============================================================================
// 
//==============================================================================
CGamepad::CGamepad()
{
}

//==============================================================================
// 
//==============================================================================
CGamepad::~CGamepad()
{
}

//==============================================================================
// 
//==============================================================================
HRESULT CGamepad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	if (FAILED(m_pInput->EnumDevices(
		DI8DEVCLASS_GAMECTRL,
		EnumJoysticksCallback,
		NULL,
		DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}

	// �����[�h���Βl���[�h�Ƃ��Đݒ�
	DIPROPDWORD diprop;
	ZeroMemory(&diprop, sizeof(diprop));
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_ABS;	// ��Βl���[�h�̎w��(DPROPAXISMODE_REL�ɂ����瑊�Βl)

	// ���͏��̏�����
	for (int nControl = 0; nControl < MAX_CONTROLLER; nControl++)
	{
		if (!g_Control[nControl].Device)
		{
			return E_FAIL;
		}

		for (int nCnt = 0; nCnt < KEYINFO::KEYINFO_MAX; nCnt++)
		{
			g_Control[nControl].ButtonStates[nCnt] = ButtonState::ButtonStateNone;
		}

		// �f�[�^�t�H�[�}�b�g�̐ݒ�
		if (FAILED(g_Control[nControl].Device->SetDataFormat(
			&c_dfDIJoystick)))
		{
			return E_FAIL;
		}

		// �����[�h��ύX
		if (FAILED(g_Control[nControl].Device->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
		{
			return false;
		}

		// ���X�e�B�b�N�̏�����
		DIPROPRANGE diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.diph.dwObj = DIJOFS_X;
		diprg.lMin = -10000;
		diprg.lMax = 10000;

		// �E�X�e�B�b�N�̏�����
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize = sizeof(dipdw);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwHow = DIPH_BYOFFSET;
		dipdw.dwData = 0;

		if (FAILED(g_Control[nControl].Device->SetProperty(DIPROP_RANGE, &diprg.diph)))
		{
			return false;
		}

		diprg.diph.dwObj = DIJOFS_Y;
		if (FAILED(g_Control[nControl].Device->SetProperty(DIPROP_RANGE, &diprg.diph)))
		{
			return false;
		}

		// �������[�h�̐ݒ�
		if (FAILED(g_Control[nControl].Device->SetCooperativeLevel(
			hWnd,
			(DISCL_FOREGROUND | DISCL_EXCLUSIVE))))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//==============================================================================
// 
//==============================================================================
void CGamepad::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		if (g_Control[nCnt].Device != NULL)
		{
			// �A�N�Z�X���̔j��
			g_Control[nCnt].Device->Unacquire();

			g_Control[nCnt].Device->Release();
			g_Control[nCnt].Device = NULL;
		}
	}

	if (g_InputInterface != NULL)
	{
		g_InputInterface->Release();
		g_InputInterface = NULL;
	}
}

//==============================================================================
// 
//==============================================================================
void CGamepad::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		if (g_Control[nCnt].Device == nullptr)
		{
			return;
		}

		DIJOYSTATE pad_data;

		HRESULT hr = g_Control[nCnt].Device->GetDeviceState(sizeof(DIJOYSTATE), &pad_data);

		if (FAILED(hr))
		{
			if (FAILED(g_Control[nCnt].Device->Acquire()))
			{
				for (int nCntButton = 0; nCntButton < KEYINFO::KEYINFO_MAX; nCntButton++)
				{
					g_Control[nCnt].ButtonStates[nCntButton] = ButtonState::ButtonStateNone;
				}
				g_Control[nCnt].Device->Poll();
			}
			return;
		}

		ButtonSet(pad_data, nCnt);
	}
}

//==============================================================================
// 
//==============================================================================
void CGamepad::ButtonSet(DIJOYSTATE pad_data, int nCnt)
{
	// ���[�J���ϐ��錾
	bool is_push[MAX_CONTROLLER][KEYINFO::KEYINFO_MAX];
	int unresponsive_range = 200;
	float rightRange = 32767.0f;

	// ���X�e�B�b�N�͈̔�
	if (pad_data.lX < -unresponsive_range)
	{// ���ɌX����
		is_push[nCnt][KEYINFO::LEFT] = true;
	}
	else if (pad_data.lX > unresponsive_range)
	{// �E�ɌX����
		is_push[nCnt][KEYINFO::RIGHT] = true;
	}

	if (pad_data.lY < -unresponsive_range)
	{// ��ɌX����
		is_push[nCnt][KEYINFO::UP] = true;
	}
	else if (pad_data.lY > unresponsive_range)
	{// ���ɌX����
		is_push[nCnt][KEYINFO::DOWN] = true;
	}

	// �E�X�e�B�b�N�͈̔�
	if (pad_data.lZ < rightRange / 5.0f)
	{// ���ɌX����
		is_push[nCnt][KEYINFO::RIGHT] = true;
	}
	else if (pad_data.lZ > rightRange * 1.2f)
	{// �E�ɌX����
		is_push[nCnt][KEYINFO::LEFT] = true;
	}

	if (pad_data.lRz < rightRange / 5.0f)
	{// ��ɌX����
		is_push[nCnt][KEYINFO::UP] = true;
	}
	else if (pad_data.lRz > rightRange * 1.2f)
	{// ���ɌX����
		is_push[nCnt][KEYINFO::DOWN] = true;
	}

	// �\���L�[�̐ݒ�
	if (pad_data.rgdwPOV[0] != 0xFFFFFFFF)
	{
		// 8�����ł̐���
		switch (pad_data.rgdwPOV[0])
		{
			// ��
		case 0:
			is_push[nCnt][KEYINFO::UP] = true;
			break;
			// �E��
		case 4500:
			is_push[nCnt][KEYINFO::UP] = true;
			is_push[nCnt][KEYINFO::RIGHT] = true;
			break;
			// �E
		case 9000:
			is_push[nCnt][KEYINFO::RIGHT] = true;
			break;
			// �E��
		case 13500:
			is_push[nCnt][KEYINFO::DOWN] = true;
			is_push[nCnt][KEYINFO::RIGHT] = true;
			break;
			// ��
		case 18000:
			is_push[nCnt][KEYINFO::DOWN] = true;
			break;
			// ����
		case 22500:
			is_push[nCnt][KEYINFO::DOWN] = true;
			is_push[nCnt][KEYINFO::LEFT] = true;
			break;
			// ��
		case 27000:
			is_push[nCnt][KEYINFO::LEFT] = true;
			break;
			// ����
		case 31500:
			is_push[nCnt][KEYINFO::UP] = true;
			is_push[nCnt][KEYINFO::LEFT] = true;
			break;
		}
	}

	for (int nCntButton = 0; nCntButton < 32; nCntButton++)
	{
		if (!(pad_data.rgbButtons[nCntButton] & 0x80))
		{
			continue;
		}

		switch (nCntButton)
		{
		case 0:		// X�{�^��
			is_push[nCnt][KEYINFO::A] = true;
			break;

		case 2:		// A�{�^��
			is_push[nCnt][KEYINFO::A] = true;
			break;

		case 3:		// B�{�^��
			is_push[nCnt][KEYINFO::B] = true;
			break;

		case 10:	// Pause�{�^��
			is_push[nCnt][KEYINFO::P] = true;
			break;

		case 11:	// Pause�{�^��
			is_push[nCnt][KEYINFO::P] = true;
			break;

		case 12:	// Pause�{�^��
			is_push[nCnt][KEYINFO::P] = true;
			break;
		}
		//break;
	}

	// ���͏�񂩂�{�^���̏�Ԃ��X�V����
	for (int nCntButton = 0; nCntButton < KEYINFO::KEYINFO_MAX; nCntButton++)
	{
		if (is_push[nCnt][nCntButton] == true)
		{
			if (g_Control[nCnt].ButtonStates[nCntButton] == ButtonState::ButtonStateNone)
			{
				g_Control[nCnt].ButtonStates[nCntButton] = ButtonState::ButtonStateDown;
			}
			else
			{
				g_Control[nCnt].ButtonStates[nCntButton] = ButtonState::ButtonStatePush;
			}
		}
		else
		{
			if (g_Control[nCnt].ButtonStates[nCntButton] == ButtonState::ButtonStatePush)
			{
				g_Control[nCnt].ButtonStates[nCntButton] = ButtonState::ButtonStateUp;
			}
			else
			{
				g_Control[nCnt].ButtonStates[nCntButton] = ButtonState::ButtonStateNone;
			}
		}
	}
}

//==============================================================================
// 
//==============================================================================
bool CGamepad::IsButtonPush(KEYINFO button)
{
	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		if (g_Control[nCnt].ButtonStates[button] == ButtonState::ButtonStatePush)
		{
			return true;
		}
	}

	return false;
}

//==============================================================================
// 
//==============================================================================
bool CGamepad::IsButtonUp(KEYINFO button)
{
	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		if (g_Control[nCnt].ButtonStates[button] == ButtonState::ButtonStateUp)
		{
			return true;
		}
	}

	return false;
}

//==============================================================================
// 
//==============================================================================
bool CGamepad::IsButtonDown(KEYINFO button)
{
	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		if (g_Control[nCnt].ButtonStates[button] == ButtonState::ButtonStateDown)
		{
			return true;
		}
	}

	return false;
}

//==============================================================================
// 
//==============================================================================
bool CGamepad::BuPu(KEYINFO button, int nCnt)
{
	if (g_Control[nCnt].ButtonStates[button] == ButtonState::ButtonStatePush)
	{
		return true;
	}

	return false;
}

//==============================================================================
// 
//==============================================================================
bool CGamepad::BuUp(KEYINFO button, int nCnt)
{
	if (g_Control[nCnt].ButtonStates[button] == ButtonState::ButtonStateUp)
	{
		return true;
	}

	return false;
}

//==============================================================================
// 
//==============================================================================
bool CGamepad::BuDo(KEYINFO button, int nCnt)
{
	if (g_Control[nCnt].ButtonStates[button] == ButtonState::ButtonStateDown)
	{
		return true;
	}

	return false;
}

//==============================================================================
// 
//==============================================================================
BOOL CGamepad::EnumJoysticksCallback(const DIDEVICEINSTANCE * pdidoi, VOID * pContext)
{
	HRESULT hr;

	hr = g_InputInterface->CreateDevice(pdidoi->guidInstance, &g_Control[g_nController].Device, NULL);

	g_nController++;

	return DIENUM_CONTINUE;
}

//==============================================================================
// 
//==============================================================================
int CGamepad::GetNumControl(void)
{
	return g_nController;
}
