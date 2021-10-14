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

	HRESULT Init(D3DXVECTOR3 pos, int nLife, float fSizeX, float fSizeY, D3DXCOLOR col);				  //初期化処理
	void Uninit(void);																					  //終了処理
	void Update(void);																					  //更新処理
	void Draw(void);																					  //描画処理

	static CEffect *Create(D3DXVECTOR3 pos, int nLife, float fSizeX, float fSizeY, D3DXCOLOR col);		  //生成処理
	static HRESULT Load(void);																			  //テクスチャ読み込み
	static void Unload(void);																			  //テクスチャ破棄

private:
	D3DXVECTOR3 m_move;						//移動量
	D3DXCOLOR	m_col;						//色
	int			m_Life;						//ライフ
	float		m_fSizeX;					//サイズ
	float		m_fSizeY;					//サイズ
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
};

#endif