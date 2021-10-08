//=============================================================================
//
// メイン処理 [explosion.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2D.h"

//=============================================================================
// 爆破クラスの定義
//=============================================================================

//継承先描画クラス
class CExplosion : public CScene2D
{
public:
	CExplosion();								//コンストラクタ
	virtual ~CExplosion();						//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CExplosion *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
	int m_nCounterAnime;					//アニメーションカウンター
	int m_nPatternAnime;					//アニメーションパターン
};

#endif