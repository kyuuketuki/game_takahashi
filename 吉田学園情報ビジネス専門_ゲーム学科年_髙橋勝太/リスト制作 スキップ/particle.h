//=============================================================================
//
// メイン処理 [particl.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _PARTICL_H_
#define _PARTICL_H_

#include "main.h"
#include "scene2D.h"

//マクロ定義
#define PARTICL_SIZE (10)

//=============================================================================
// 弾クラスの定義
//=============================================================================

//継承先描画クラス
class CParticl : public CScene2D
{
public:
	CParticl(int nPriority = 4);				//コンストラクタ
	virtual ~CParticl();						//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fSpeed, float fSizeX, float fSizeY, float fAngle);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CParticl *Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, float fSpeed, float fSizeX, float fSizeY, float fAngle);
	static HRESULT Load(void);
	static void Unload(void);

private:
	D3DXVECTOR3 m_pos;							//位置
	D3DXVECTOR3 m_move;							//移動量
	D3DXCOLOR	m_col;							//カラー
	int			m_nLife;						//ライフ
	float		m_fSpeed;						//速度
	float		m_fSizeX;						//サイズ
	float		m_fSizeY;						//サイズ

	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
};

#endif