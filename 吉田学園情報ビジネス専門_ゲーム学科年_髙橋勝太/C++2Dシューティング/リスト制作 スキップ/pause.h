//=============================================================================
//
// ���C������ [pause.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// �Q�[����ʃN���X�̒�`
//=============================================================================
//�p����`��N���X
class CPause : public CScene
{
public:
	CPause(int nPriority = 0, int nType = 2);				//�R���X�g���N�^;									//�R���X�g���N�^
	~CPause();												//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPause *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
};

#endif