//=============================================================================
//
// メイン処理 [number.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

//=============================================================================
// 番号クラスの定義
//=============================================================================
class CNumber
{
public:
	CNumber();								//コンストラクタ
	~CNumber();								//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);

	static CNumber *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	static HRESULT Load(void);
	static void Unload(void);

	//D3DXVECTOR3 GetPosition(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;				// 用意するテクスチャの数
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;				//
	int							m_nNumber;
	float						m_fLength;
	float						m_fAngle;
};								

#endif