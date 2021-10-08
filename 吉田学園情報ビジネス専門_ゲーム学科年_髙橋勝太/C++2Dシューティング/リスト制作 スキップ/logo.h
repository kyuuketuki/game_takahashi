//=============================================================================
//
// ���C������ [logo.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _LOGO_H_
#define _LOGO_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"

#define MAX_LOGO		(33)					//�e�N�X�`�����\���Ă���|���S���̕`��

//=============================================================================
// ���S�N���X�̒�`
//=============================================================================
//�p����`��N���X
class CLogo : public CScene2D
{
public:
	CLogo(int nPriority = 3, int nType = 0);			//�R���X�g���N�^
	~CLogo();								//�f�X�g���N�^

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
	static LPDIRECT3DTEXTURE9 m_apTextureLogo[MAX_LOGO];	// �p�ӂ���e�N�X�`���̐�
	static CPlayer				*m_pPlayer;					//�v���C���[�ւ̃|�C���^	�z�[�~���O���Ɏg�p

	CScene2D *m_apScene2D[3];								// �V�[��2D�ւ̃|�C���^
	D3DXVECTOR3		m_pos;									// �ʒu���
	float			m_nCntAnime;							// �e�N�X�`�������炷
	int				m_nType;								//�^�C�v�Ńe�N�X�`�����Ǘ����Ă���
};

//=============================================================================
// ���S�N���X�̒�`(Pause)
//=============================================================================
class CLogoPause : public CLogo
{
public:
	CLogoPause(int nPriority = 4, int nType = 2);				//�R���X�g���N�^
	~CLogoPause();												//�f�X�g���N�^

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