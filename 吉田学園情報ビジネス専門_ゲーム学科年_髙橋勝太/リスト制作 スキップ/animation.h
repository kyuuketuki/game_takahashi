//=============================================================================
//
// メイン処理 [animasion.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _ANIMASION_H_
#define _ANIMASION_H_

#include "main.h"
#include "scene2D.h"

//マクロ定義
#define MAX_ANIME (18)

//=============================================================================
// 爆破クラスの定義
//=============================================================================

//継承先描画クラス
class CAnimasion : public CScene2D
{
public:
	CAnimasion(int nPriority = 3, int nType = 0);			//コンストラクタ
	virtual ~CAnimasion();									//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CAnimasion *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);
	static HRESULT Load(void);
	static void Unload(void);

	static void UninitType(int nUninitType);
	static void UninitTypeClear(void);

protected:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ANIME];	//テクスチャのポインタ
	static int m_nUninitType;
	D3DXVECTOR3 m_pos;									//移動量
	int m_nType;
	int m_nTypeBuulet;
	int m_nCounterAnime;								//アニメーションカウンター
	int m_nPatternAnime;								//アニメーションパターン
	int m_fCriss;
	float m_fAnimeX;
	float m_fAnimeY;
	int m_nX;
	int m_nY;
	int m_nAnime;
	float m_fColorFa = 1.0f;
};

//=============================================================================
// アニメーションクラスの定義(背景)
//=============================================================================
class CAnimasionBg : public CAnimasion
{
public:
	CAnimasionBg(int nPriority = 1, int nType = 0);	//コンストラクタ
	virtual ~CAnimasionBg();						//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CAnimasionBg *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);
	static void UninitTypeClear(void);
};

#endif