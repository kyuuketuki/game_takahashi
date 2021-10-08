//=============================================================================
//
// メイン処理 [logo.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _LOGO_H_
#define _LOGO_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"

#define MAX_LOGO		(33)					//テクスチャが貼ってあるポリゴンの描画

//=============================================================================
// ロゴクラスの定義
//=============================================================================
//継承先描画クラス
class CLogo : public CScene2D
{
public:
	CLogo(int nPriority = 3, int nType = 0);			//コンストラクタ
	~CLogo();								//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CLogo *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType);
	static HRESULT Load(void);
	static void Unload(void);
	static void TypeUninit(int nType);
	static void TypeMove(D3DXVECTOR3 pos, int nTypeMove);

	static void TypeChangeCollar(D3DXCOLOR col, int nTypeCollar);

protected:
	static LPDIRECT3DTEXTURE9 m_apTextureLogo[MAX_LOGO];	// 用意するテクスチャの数
	static CPlayer				*m_pPlayer;					//プレイヤーへのポインタ	ホーミング時に使用

	CScene2D *m_apScene2D[3];								// シーン2Dへのポインタ
	D3DXVECTOR3		m_pos;									// 位置情報
	float			m_nCntAnime;							// テクスチャをずらす
	int				m_nType;								//タイプでテクスチャを管理している
};

//=============================================================================
// ロゴクラスの定義(Pause)
//=============================================================================
class CLogoPause : public CLogo
{
public:
	CLogoPause(int nPriority = 4, int nType = 2);				//コンストラクタ
	~CLogoPause();												//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CLogoPause *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType);
	static void Unload(void);
	static void TypeUninit(int nType);
	static void TypeMove(D3DXVECTOR3 pos, int nTypeMove);
	static void TypeChangeCollar(D3DXCOLOR col, int nTypeCollar);
};

#endif