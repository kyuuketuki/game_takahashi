//=============================================================================
//
// メイン処理 [player3D.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "player3D.h"
#include "manager.h"
#include "model.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CPlayer3D::CPlayer3D(int nPriority, int nType)
{
}

//==============================================================================
// デストラクタ
//==============================================================================
CPlayer3D::~CPlayer3D()
{
}

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT CPlayer3D::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	//Ｘファイルの読み込み
	m_pTextName[0] = "data/MODEL/胴体.x";

	//親の番号
	m_aIndexParent[0] = 0;

	//位置を設定
	m_aOffset[0][0] = 0.0f;
	m_aOffset[0][1] = 0.0f;
	m_aOffset[0][2] = 0.0f;
	m_aOffset[0][3] = 0.0f;
	m_aOffset[0][4] = 0.0f;
	m_aOffset[0][5] = 0.0f;

	//モデルを生成
	m_apModel[0] = CModel::Create(D3DXVECTOR3(m_aOffset[0][0], m_aOffset[0][1], m_aOffset[0][2]), 
		D3DXVECTOR3(m_aOffset[0][3], m_aOffset[0][4], m_aOffset[0][5]), m_pTextName[0]);

	//親の番号
	m_apModel[0]->SetParent(NULL);

	//Ｘファイルの読み込み
	m_pTextName[1] = "data/MODEL/頭.x";

	m_aIndexParent[1] = 0;

	//位置を設定
	m_aOffset[1][0] = 0.0f;
	m_aOffset[1][1] = 30.0f;
	m_aOffset[1][2] = 0.0f;
	m_aOffset[1][3] = 0.0f;
	m_aOffset[1][4] = 0.0f;
	m_aOffset[1][5] = 0.0f;

	//モデルを生成
	m_apModel[1] = CModel::Create(D3DXVECTOR3(m_aOffset[1][0], m_aOffset[1][1], m_aOffset[1][2]), 
		D3DXVECTOR3(m_aOffset[1][3], m_aOffset[1][4], m_aOffset[1][5]), m_pTextName[1]);

	m_apModel[1]->SetParent(m_apModel[m_aIndexParent[1]]);

	//Ｘファイルの読み込み
	m_pTextName[2] = "data/MODEL/右肩.x";

	m_aIndexParent[2] = 0;

	//親の番号
	m_aOffset[2][0] = -15.0f;
	m_aOffset[2][1] = 20.0f;
	m_aOffset[2][2] = 0.0f;
	m_aOffset[2][3] = 0.0f;
	m_aOffset[2][4] = 0.0f;
	m_aOffset[2][5] = 0.0f;

	m_apModel[2] = CModel::Create(D3DXVECTOR3(m_aOffset[2][0], m_aOffset[2][1], m_aOffset[2][2]), 
		D3DXVECTOR3(m_aOffset[2][3], m_aOffset[2][4], m_aOffset[2][5]), m_pTextName[2]);

	m_apModel[2]->SetParent(m_apModel[m_aIndexParent[2]]);

	//Ｘファイルの読み込み
	m_pTextName[3] = "data/MODEL/右腕.x";

	m_aIndexParent[3] = 2;

	//位置を設定
	m_aOffset[3][0] = -10.0f;
	m_aOffset[3][1] = 0.0f;
	m_aOffset[3][2] = 0.0f;
	m_aOffset[3][3] = 0.0f;
	m_aOffset[3][4] = 0.0f;
	m_aOffset[3][5] = 0.0f;

	m_apModel[3] = CModel::Create(D3DXVECTOR3(m_aOffset[3][0], m_aOffset[3][1], m_aOffset[3][2]), 
		D3DXVECTOR3(m_aOffset[3][3], m_aOffset[3][4], m_aOffset[3][5]), m_pTextName[3]);

	m_apModel[3]->SetParent(m_apModel[m_aIndexParent[3]]);

	//Ｘファイルの読み込み
	m_pTextName[4] = "data/MODEL/右手.x";

	//親の番号
	m_aIndexParent[4] = 3;

	//位置を設定
	m_aOffset[4][0] = -10.0f;
	m_aOffset[4][1] = 0.0f;
	m_aOffset[4][2] = 0.0f;
	m_aOffset[4][3] = 0.0f;
	m_aOffset[4][4] = 0.0f;
	m_aOffset[4][5] = 0.0f;

	m_apModel[4] = CModel::Create(D3DXVECTOR3(m_aOffset[4][0], m_aOffset[4][1], m_aOffset[4][2]), 
		D3DXVECTOR3(m_aOffset[4][3], m_aOffset[4][4], m_aOffset[4][5]), m_pTextName[4]);

	m_apModel[4]->SetParent(m_apModel[m_aIndexParent[4]]);

	//Ｘファイルの読み込み
	m_pTextName[5] = "data/MODEL/左肩.x";

	//親の番号
	m_aIndexParent[5] = 0;

	//位置を設定
	m_aOffset[5][0] = 15.0f;
	m_aOffset[5][1] = 20.0f;
	m_aOffset[5][2] = 0.0f;
	m_aOffset[5][3] = 0.0f;
	m_aOffset[5][4] = 0.0f;
	m_aOffset[5][5] = 0.0f;

	m_apModel[5] = CModel::Create(D3DXVECTOR3(m_aOffset[5][0], m_aOffset[5][1], m_aOffset[5][2]),
		D3DXVECTOR3(m_aOffset[5][3], m_aOffset[5][4], m_aOffset[5][5]), m_pTextName[5]);

	m_apModel[5]->SetParent(m_apModel[m_aIndexParent[5]]);

	//Ｘファイルの読み込み
	m_pTextName[6] = "data/MODEL/左腕.x";

	//大家の番号
	m_aIndexParent[6] = 5;

	//位置を設定
	m_aOffset[6][0] = 10.0f;
	m_aOffset[6][1] = 0.0f;
	m_aOffset[6][2] = 0.0f;
	m_aOffset[6][3] = 0.0f;
	m_aOffset[6][4] = 0.0f;
	m_aOffset[6][5] = 0.0f;

	m_apModel[6] = CModel::Create(D3DXVECTOR3(m_aOffset[6][0], m_aOffset[6][1], m_aOffset[6][2]),
		D3DXVECTOR3(m_aOffset[6][3], m_aOffset[6][4], m_aOffset[6][5]), m_pTextName[6]);

	//Ｘファイルの読み込み
	m_pTextName[7] = "data/MODEL/左手.x";

	//親の番号
	m_aIndexParent[7] = 6;

	//位置を設定
	m_aOffset[7][0] = 10.0f;
	m_aOffset[7][1] = 0.0f;
	m_aOffset[7][2] = 0.0f;
	m_aOffset[7][3] = 0.0f;
	m_aOffset[7][4] = 0.0f;
	m_aOffset[7][5] = 0.0f;

	m_apModel[7] = CModel::Create(D3DXVECTOR3(m_aOffset[7][0], m_aOffset[7][1], m_aOffset[7][2]),
		D3DXVECTOR3(m_aOffset[7][3], m_aOffset[7][4], m_aOffset[7][5]), m_pTextName[7]);

	m_apModel[7]->SetParent(m_apModel[m_aIndexParent[7]]);

	//Ｘファイルの読み込み
	m_pTextName[8] = "data/MODEL/腰.x";

	//親の番号
	m_aIndexParent[8] = 0;

	//位置を設定
	m_aOffset[8][0] = 0.0f;
	m_aOffset[8][1] = -5.0f;
	m_aOffset[8][2] = 0.0f;
	m_aOffset[8][3] = 0.0f;
	m_aOffset[8][4] = 0.0f;
	m_aOffset[8][5] = 0.0f;

	m_apModel[8] = CModel::Create(D3DXVECTOR3(m_aOffset[8][0], m_aOffset[8][1], m_aOffset[8][2]),
		D3DXVECTOR3(m_aOffset[8][3], m_aOffset[8][4], m_aOffset[8][5]), m_pTextName[8]);

	m_apModel[8]->SetParent(m_apModel[m_aIndexParent[8]]);

	//Ｘファイルの読み込み
	m_pTextName[9] = "data/MODEL/01_右足.x";

	//親の番号
	m_aIndexParent[9] = 8;

	//位置を設定
	m_aOffset[9][0] = -5.0f;
	m_aOffset[9][1] = -10.0f;
	m_aOffset[9][2] = 0.0f;
	m_aOffset[9][3] = 0.0f;
	m_aOffset[9][4] = 0.0f;
	m_aOffset[9][5] = 0.0f;

	m_apModel[9] = CModel::Create(D3DXVECTOR3(m_aOffset[9][0], m_aOffset[9][1], m_aOffset[9][2]),
		D3DXVECTOR3(m_aOffset[9][3], m_aOffset[9][4], m_aOffset[9][5]), m_pTextName[9]);

	m_apModel[9]->SetParent(m_apModel[m_aIndexParent[9]]);

	//Ｘファイルの読み込み
	m_pTextName[10] = "data/MODEL/右ひざ下.x";

	//親の番号
	m_aIndexParent[10] = 9;

	//位置を設定
	m_aOffset[10][0] = 0.0f;
	m_aOffset[10][1] = -15.0f;
	m_aOffset[10][2] = 0.0f;
	m_aOffset[10][3] = 0.0f;
	m_aOffset[10][4] = 0.0f;
	m_aOffset[10][5] = 0.0f;

	m_apModel[10] = CModel::Create(D3DXVECTOR3(m_aOffset[10][0], m_aOffset[10][1], m_aOffset[10][2]),
		D3DXVECTOR3(m_aOffset[10][3], m_aOffset[10][4], m_aOffset[10][5]), m_pTextName[10]);

	m_apModel[10]->SetParent(m_apModel[m_aIndexParent[10]]);

	//Ｘファイルの読み込み
	m_pTextName[11] = "data/MODEL/右靴.x";

	//親の番号
	m_aIndexParent[11] = 10;

	//位置を設定
	m_aOffset[11][0] = 0.0f;
	m_aOffset[11][1] = -25.0f;
	m_aOffset[11][2] = 0.0f;
	m_aOffset[11][3] = 0.0f;
	m_aOffset[11][4] = 0.0f;
	m_aOffset[11][5] = 0.0f;

	m_apModel[11] = CModel::Create(D3DXVECTOR3(m_aOffset[11][0], m_aOffset[11][1], m_aOffset[11][2]),
		D3DXVECTOR3(m_aOffset[11][3], m_aOffset[11][4], m_aOffset[11][5]), m_pTextName[11]);

	m_apModel[11]->SetParent(m_apModel[m_aIndexParent[11]]);

	//Ｘファイルの読み込み
	m_pTextName[12] = "data/MODEL/01_左足.x";

	//親の番号
	m_aIndexParent[12] = 8;

	//位置を設定
	m_aOffset[12][0] = 5.0f;
	m_aOffset[12][1] = -10.0f;
	m_aOffset[12][2] = 0.0f;
	m_aOffset[12][3] = 0.0f;
	m_aOffset[12][4] = 0.0f;
	m_aOffset[12][5] = 0.0f;

	m_apModel[12] = CModel::Create(D3DXVECTOR3(m_aOffset[12][0], m_aOffset[12][1], m_aOffset[12][2]),
		D3DXVECTOR3(m_aOffset[12][3], m_aOffset[12][4], m_aOffset[12][5]), m_pTextName[12]);

	m_apModel[12]->SetParent(m_apModel[m_aIndexParent[12]]);

	//Ｘファイルの読み込み
	m_pTextName[13] = "data/MODEL/左ひざ下.x";

	//親の番号
	m_aIndexParent[13] = 12;

	//位置を設定
	m_aOffset[13][0] = 0.0f;
	m_aOffset[13][1] = -15.0f;
	m_aOffset[13][2] = 0.0f;
	m_aOffset[13][3] = 0.0f;
	m_aOffset[13][4] = 0.0f;
	m_aOffset[13][5] = 0.0f;

	m_apModel[13] = CModel::Create(D3DXVECTOR3(m_aOffset[13][0], m_aOffset[13][1], m_aOffset[13][2]),
		D3DXVECTOR3(m_aOffset[13][3], m_aOffset[13][4], m_aOffset[13][5]), m_pTextName[13]);

	m_apModel[13]->SetParent(m_apModel[m_aIndexParent[13]]);

	//Ｘファイルの読み込み
	m_pTextName[14] = "data/MODEL/左靴.x";

	//親の番号
	m_aIndexParent[14] = 13;

	//位置を設定
	m_aOffset[14][0] = 0.0f;
	m_aOffset[14][1] = -25.0f;
	m_aOffset[14][2] = 0.0f;
	m_aOffset[14][3] = 0.0f;
	m_aOffset[14][4] = 0.0f;
	m_aOffset[14][5] = 0.0f;

	m_apModel[14] = CModel::Create(D3DXVECTOR3(m_aOffset[14][0], m_aOffset[14][1], m_aOffset[14][2]),
		D3DXVECTOR3(m_aOffset[14][3], m_aOffset[14][4], m_aOffset[14][5]), m_pTextName[14]);

	m_apModel[14]->SetParent(m_apModel[m_aIndexParent[14]]);

	//位置
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//向き
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CPlayer3D::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//==============================================================================
// 更新処理
//==============================================================================
void CPlayer3D::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER_PARTS; nCnt++)
	{
		m_apModel[nCnt]->Update();
	}

	//m_fRot += 0.01f;
	//m_rot.y = m_fRot;
	//m_rot.x = m_fRot;

	//キーボード取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//移動処理
	//Wを押したとき
	if (pInputKeyboard->GetPress(DIK_LEFT) == true)
	{
		m_pos.x -= 5.0f;
	}

	//Sを押したとき
	if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{
		m_pos.x += 5.0f;
	}

	//Aを押したとき
	if (pInputKeyboard->GetPress(DIK_UP) == true)
	{
		m_pos.z += 5.0f;
	}

	//Dを押したとき
	if (pInputKeyboard->GetPress(DIK_DOWN) == true)
	{
		m_pos.z -= 5.0f;
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void CPlayer3D::Draw(void)
{
	//ローカル
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存
	D3DXMATERIAL *pMat;				//マテリアルへのポインタ

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きの反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置の反転
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	////パーツの描画
	//m_apModel[0]->Draw();
	//m_apModel[1]->Draw();
	//m_apModel[2]->Draw();
	//m_apModel[3]->Draw();

	/*for (int nCnt = 0; nCnt < MAX_PLAYER_PARTS; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}*/

	for (int nCnt = 0; nCnt < 15; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}

	//m_apModel[0]->Draw();
	////m_apModel[8]->Draw();
	////m_apModel[9]->Draw();
	//m_apModel[11]->Draw();

	//保存したマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//==============================================================================
// 生成処理
//==============================================================================
CPlayer3D * CPlayer3D::Create()
{
	//プレイヤーを生成
	CPlayer3D *pPlayer3D = NULL;
	pPlayer3D = new CPlayer3D;

	//NULLチェック
	if (pPlayer3D != NULL)
	{
		pPlayer3D->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
	}

	return pPlayer3D;
}
