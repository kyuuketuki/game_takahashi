//=============================================================================
//
// メイン処理 [model.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _MODEL_H_
#define _MODEL_H_

#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#include "main.h"
#include "scene.h"

//=============================================================================
// ポリゴンクラスの定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
} VERTEX_3D;

//継承先描画クラス
class CModel
{
public:
	CModel(int nPriority = 5, int nType = 0);								//コンストラクタ
	virtual ~CModel();														//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pTextName);		//初期化処理
	void Uninit(void);														//終了処理
	void Update(void);														//更新処理
	void Draw(void);														//描画処理

	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pTextName);								//生成処理

	void SetParent(CModel *pModel);
	D3DXMATRIX GetMtxWorld(void);

private:
	LPD3DXMESH		m_pMesh;			//メッシュ
	LPD3DXBUFFER	m_pBuffMat;			//バッファ
	DWORD			m_nNumMat;			//マトリックス
	D3DXMATRIX		m_mtxWorld;			//ワールドマトリックス
	D3DXVECTOR3		m_pos;				//位置
	D3DXVECTOR3		m_rot;				//向き
	int				m_nNumVtx;			//頂点数
	float			m_fRot;				//
	CModel			*m_pParent;			//

};

#endif