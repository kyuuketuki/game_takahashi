//=============================================================================
//
// メイン処理 [item.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "player.h"
#include "scene2D.h"

//マクロ定義
#define ITEM_SIZE (70)
#define ITEM_TYPE (2)

//=============================================================================
// 敵クラスの定義
//=============================================================================
//継承先描画クラス
class CItem : public CScene2D
{
public:
	CItem();								//コンストラクタ
	virtual ~CItem();						//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fmove, float fSizeX, float fSizeY, int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Animasion(void);

	//敵の生成
	static CItem *Create(D3DXVECTOR3 pos, float fmove, float fSizeX, float fSizeY, int nType);

	static void Heart(D3DXVECTOR3 pos, float fmove, float fSizeX, float fSizeY, int nType);
	static void Heart2(D3DXVECTOR3 pos, float fmove, float fSizeX, float fSizeY, int nType, int nType2);

	//テクスチャ関連
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[ITEM_TYPE];			//テクスチャへのポインタ

	D3DXVECTOR3					m_pos;							//位置
	int							m_nType;						//敵の種類をタイプで管理
	float						m_fMove;						//移動スピード
	
	//アニメーション関連
	int							m_nCounterAnime;				//アニメーションカウンター
	int							m_nPatternAnime;				//アニメーションパターン
	float						m_fAnimeX;
	float						m_fAnimeY;
	int							m_nX;
	int							m_nY;
};

#endif