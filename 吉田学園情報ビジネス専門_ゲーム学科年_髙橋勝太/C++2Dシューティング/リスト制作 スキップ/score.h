//=============================================================================
//
// メイン処理 [score.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "number.h"
#include "scene.h"

//=============================================================================
// スコアクラスの定義
//=============================================================================
//継承先描画クラス
class CScore : public CScene
{
public:
	CScore();								//コンストラクタ
	~CScore();								//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetScore(int nScore);

	static void AddScore(int nValue);
	static CScore *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

	int GetScore(void);

private:
	static CNumber *m_apNumber[8];			//桁数
	static int m_nScore;					//スコアの値
};

#endif