//=============================================================================
//
// メイン処理 [effect.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "scene2D.h"

//マクロ定義
#define EFFECT_SIZE (10)

//=============================================================================
// 弾クラスの定義
//=============================================================================

//継承先描画クラス
class CEffect : public CScene2D
{
public:
	CEffect(int nPriority = 3);				//コンストラクタ
	virtual ~CEffect();						//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, int nLife, float fSizeX, float fSizeY, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffect *Create(D3DXVECTOR3 pos, int nLife, float fSizeX, float fSizeY, D3DXCOLOR col);
	static HRESULT Load(void);
	static void Unload(void);

private:
	D3DXVECTOR3 m_move;						//移動量
	D3DXCOLOR	m_col;						//色
	int			m_Life;						//ライフ
	float m_fSizeX;
	float m_fSizeY;
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
};

#endif