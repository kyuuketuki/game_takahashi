//=============================================================================
//
// ���C������ [game2.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"

//=============================================================================
// �Q�[����ʃN���X�̒�`
//=============================================================================
//�p����`��N���X
class CResult : public CScene
{
public:
	CResult();									//�R���X�g���N�^
	~CResult();									//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Attack(void);

	static int GetTime(void);

	static CResult *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

private:
	static CPlayer				*m_pPlayer;			//�v���C���[�ւ̃|�C���^	�z�[�~���O���Ɏg�p
	LPD3DXFONT					m_pTimeFontGame;	// �\���p�t�H���g
};

#endif