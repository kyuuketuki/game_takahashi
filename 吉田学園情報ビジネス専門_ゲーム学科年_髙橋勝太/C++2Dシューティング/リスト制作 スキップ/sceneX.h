//=============================================================================
//
// メイン処理 [sceneX.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _SCENEX_H_
#define _SCENEX_H_

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
class CSceneX : public CScene
{
public:
	CSceneX(int nPriority = 5, int nType = 0);								//コンストラクタ
	virtual ~CSceneX();					//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CSceneX *Create();

private:
	LPD3DXMESH		m_pMesh;
	LPD3DXBUFFER	m_pBuffMat;
	DWORD			m_nNumMat;
	D3DXMATRIX		m_mtxWorld;
	int				m_nNumVtx;			//頂点数
	D3DXVECTOR3		m_pos;				//位置
	D3DXVECTOR3		m_rot;				//向き
	float			m_fRot;

};

#endif