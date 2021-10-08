//=============================================================================
//
// メイン処理 [renderer.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _RENDERE_H_
#define _RENDERE_H_

#include "main.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CRenderer
{
public:
	CRenderer();								//コンストラクタ
	~CRenderer();								//デストラクタ
	HRESULT Init(HWND hWnd, bool bWindow);		
	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

private:
	void DrawFPS();

	LPDIRECT3D9					m_pD3D = NULL;				// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9			m_pD3DDevice = NULL;		// Deviceオブジェクト(描画に必要)

	//FPSの情報
	LPD3DXFONT					m_pFont = NULL;				// フォントへのポインタ
};

#endif
