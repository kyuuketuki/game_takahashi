//=============================================================================
//
// メイン処理 [player3D.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _PLAYER3D_H_
#define _PLAYER3D_H_

#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#include "main.h"
#include "scene.h"
#include "model.h"

#define MAX_PLAYER_PARTS (15)

//=============================================================================
// ポリゴンクラスの定義
//=============================================================================
//継承先描画クラス
class CPlayer3D : public CScene
{
public:
	CPlayer3D(int nPriority = 5, int nType = 0);								//コンストラクタ
	virtual ~CPlayer3D();														//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);					//初期化処理
	void Uninit(void);															//終了処理
	void Update(void);															//更新処理
	void Draw(void);															//描画処理

	static CPlayer3D *Create();													//生成処理

private:
	CModel			*m_apModel[MAX_PLAYER_PARTS];				//モデルへのポインタ
	int				m_aIndexParent[MAX_PLAYER_PARTS];			//モデルの親
	float			m_aOffset[MAX_PLAYER_PARTS][6];				//モデルの位置向きを設置
	char			*m_pTextName[MAX_PLAYER_PARTS];				//名前保存

	LPD3DXMESH		m_pMesh;			//メッシュ
	LPD3DXBUFFER	m_pBuffMat;			//バッファ
	DWORD			m_nNumMat;			//マトリックス
	D3DXMATRIX		m_mtxWorld;			//ワールドマトリックス
	D3DXVECTOR3		m_pos;				//位置
	D3DXVECTOR3		m_rot;				//向き
	int				m_nNumVtx;			//頂点数
	float			m_fRot;				//回転
};

#endif