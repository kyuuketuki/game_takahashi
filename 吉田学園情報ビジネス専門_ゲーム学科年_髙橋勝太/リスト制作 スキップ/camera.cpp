#include "camera.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

void CCamera::Uninit(void)
{
}

void CCamera::Update(void)
{
}

void CCamera::Draw(void)
{
}

void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�r���[�|�[�g���擾
		//pDevice->SetViewport(&g_camera[nIdx].viewport);

		// �v���W�F�N�V�����}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxProjection);

		// �v���W�F�N�V�����}�g���b�N�X�̍쐬
		D3DXMatrixPerspectiveFovLH(
			&m_mtxProjection,
			D3DXToRadian(45.0f),									// ��p�̐ݒ�
			((float)SCREEN_WIDTH / 2.0f) / (float)SCREEN_HEIGHT,	// ��ʔ䗦�̐ݒ� �r���[�|�[�g�̕�����
			//860 / (float)SCREEN_HEIGHT,							// ��ʔ䗦�̐ݒ� �r���[�|�[�g�̕�����
			10.0f,													// ��O���E�̕`�拗��
			4000.0f);												// �����E�̕`�拗��

																	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

		// �r���[�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxView);

		// �r���[�}�g���b�N�X�̍쐬
		D3DXMatrixLookAtLH(&m_mtxView,&m_posV,&m_posR,&m_vecU);

		// �r���[�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	}
}
