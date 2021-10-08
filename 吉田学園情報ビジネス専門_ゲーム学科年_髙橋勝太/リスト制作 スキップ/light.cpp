#include "light.h"

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
D3DLIGHT9 g_light[3];		//ライト情報

CLight::CLight()
{
}

CLight::~CLight()
{
}

HRESULT CLight::Init()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir;			//設定用方向ベクトル

	for (int nCntShadow = 0; nCntShadow < MAX_LIGHT; nCntShadow++)
	{
		//ライトをクリアにする
		ZeroMemory(&m_light[nCntShadow], sizeof(D3DLIGHT9));

		//ライトの種類
		m_light[nCntShadow].Type = D3DLIGHT_DIRECTIONAL;

		//m_light拡散光の設定
		m_light[nCntShadow].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//ライトの方向を設定
		vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		D3DXVec3Normalize(&vecDir, &vecDir); //正規化
		m_light[nCntShadow].Direction = vecDir;

		//ライトを設定する
		pDevice->SetLight(0, &m_light[nCntShadow]);
	}

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);

	//ライトを有効にする
	pDevice->LightEnable(1, TRUE);

	//ライトを有効にする
	pDevice->LightEnable(2, TRUE);

	return S_OK;
}

void CLight::Uninit(void)
{

}

void CLight::Update(void)
{

}

void CLight::Draw(void)
{

}