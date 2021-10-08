//=============================================================================
//
// ���C������ [item.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "player.h"
#include "scene2D.h"

//�}�N����`
#define ITEM_SIZE (70)
#define ITEM_TYPE (2)

//=============================================================================
// �G�N���X�̒�`
//=============================================================================
//�p����`��N���X
class CItem : public CScene2D
{
public:
	CItem();								//�R���X�g���N�^
	virtual ~CItem();						//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fmove, float fSizeX, float fSizeY, int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Animasion(void);

	//�G�̐���
	static CItem *Create(D3DXVECTOR3 pos, float fmove, float fSizeX, float fSizeY, int nType);

	static void Heart(D3DXVECTOR3 pos, float fmove, float fSizeX, float fSizeY, int nType);
	static void Heart2(D3DXVECTOR3 pos, float fmove, float fSizeX, float fSizeY, int nType, int nType2);

	//�e�N�X�`���֘A
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[ITEM_TYPE];			//�e�N�X�`���ւ̃|�C���^

	D3DXVECTOR3					m_pos;							//�ʒu
	int							m_nType;						//�G�̎�ނ��^�C�v�ŊǗ�
	float						m_fMove;						//�ړ��X�s�[�h
	
	//�A�j���[�V�����֘A
	int							m_nCounterAnime;				//�A�j���[�V�����J�E���^�[
	int							m_nPatternAnime;				//�A�j���[�V�����p�^�[��
	float						m_fAnimeX;
	float						m_fAnimeY;
	int							m_nX;
	int							m_nY;
};

#endif