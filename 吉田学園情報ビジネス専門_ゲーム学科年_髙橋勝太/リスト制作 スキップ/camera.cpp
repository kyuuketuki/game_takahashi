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
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//ビューポートを取得
		//pDevice->SetViewport(&g_camera[nIdx].viewport);

		// プロジェクションマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxProjection);

		// プロジェクションマトリックスの作成
		D3DXMatrixPerspectiveFovLH(
			&m_mtxProjection,
			D3DXToRadian(45.0f),									// 画角の設定
			((float)SCREEN_WIDTH / 2.0f) / (float)SCREEN_HEIGHT,	// 画面比率の設定 ビューポートの幅高さ
			//860 / (float)SCREEN_HEIGHT,							// 画面比率の設定 ビューポートの幅高さ
			10.0f,													// 手前限界の描画距離
			4000.0f);												// 奥限界の描画距離

																	// プロジェクションマトリックスの設定
		pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

		// ビューマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxView);

		// ビューマトリックスの作成
		D3DXMatrixLookAtLH(&m_mtxView,&m_posV,&m_posR,&m_vecU);

		// ビューマトリックスの設定
		pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	}
}
