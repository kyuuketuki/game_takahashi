//=============================================================================
//
// ���C������ [game.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// �Q�[����ʃN���X�̒�`
//=============================================================================
//�p����`��N���X
class CGame : public CScene
{
public:
	CGame();									//�R���X�g���N�^
	~CGame();									//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Attack(void);
	void Attack2(void);

	static int GetTime(void);

	static CGame *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

private:
	LPD3DXFONT	m_pTimeFontGame;					// �\���p�t�H���g
};

#endif