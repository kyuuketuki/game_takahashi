//=============================================================================
//
// ���C������ [animasion.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _ANIMASION_H_
#define _ANIMASION_H_

#include "main.h"
#include "scene2D.h"

//�}�N����`
#define MAX_ANIME (18)

//=============================================================================
// ���j�N���X�̒�`
//=============================================================================

//�p����`��N���X
class CAnimasion : public CScene2D
{
public:
	CAnimasion(int nPriority = 3, int nType = 0);			//�R���X�g���N�^
	virtual ~CAnimasion();									//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CAnimasion *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);
	static HRESULT Load(void);
	static void Unload(void);

	static void UninitType(int nUninitType);
	static void UninitTypeClear(void);

protected:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ANIME];	//�e�N�X�`���̃|�C���^
	static int m_nUninitType;
	D3DXVECTOR3 m_pos;									//�ړ���
	int m_nType;
	int m_nTypeBuulet;
	int m_nCounterAnime;								//�A�j���[�V�����J�E���^�[
	int m_nPatternAnime;								//�A�j���[�V�����p�^�[��
	int m_fCriss;
	float m_fAnimeX;
	float m_fAnimeY;
	int m_nX;
	int m_nY;
	int m_nAnime;
	float m_fColorFa = 1.0f;
};

//=============================================================================
// �A�j���[�V�����N���X�̒�`(�w�i)
//=============================================================================
class CAnimasionBg : public CAnimasion
{
public:
	CAnimasionBg(int nPriority = 1, int nType = 0);	//�R���X�g���N�^
	virtual ~CAnimasionBg();						//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CAnimasionBg *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);
	static void UninitTypeClear(void);
};

#endif