//=============================================================================
//
// メイン処理 [bg.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// 背景クラスの定義
//=============================================================================
//継承先描画クラス
class CLife : public CScene2D
{
public:
	CLife(int nPriority = 5);								//コンストラクタ
	~CLife();								//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CLife *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	static HRESULT Load(void);
	static void Unload(void);

	static void Recovery(int nLife);

private:
	static LPDIRECT3DTEXTURE9 m_apTextureLife[1];		// 用意するテクスチャの数
	CScene2D *m_apScene2D[1];							// シーン2Dへのポインタ
	D3DXVECTOR3 m_pos;									// 位置情報
	float m_nCntAnime;									// テクスチャをずらす
	int m_nCount;
};

#endif