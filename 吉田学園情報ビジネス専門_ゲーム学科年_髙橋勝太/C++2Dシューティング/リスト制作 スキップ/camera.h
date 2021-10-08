//=============================================================================
//
// メイン処理 [camera.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "manager.h"

//=============================================================================
// 弾クラスの定義
//=============================================================================

//継承先描画クラス
class CCamera
{
public:
	CCamera();								//コンストラクタ
	virtual ~CCamera();						//デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetCamera(void);

private:
	D3DXMATRIX m_mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			// ビューマトリックス
	D3DXVECTOR3 m_posV;			// 現在の視点
	D3DXVECTOR3 m_posR;			// 現在の注視点
	D3DXVECTOR3 m_vecU;			// 上方向ベクトル
	D3DXVECTOR3 m_rot;			// カメラの角度
	//D3DVIEWPORT9 viewport;		//ビューポート
};

#endif