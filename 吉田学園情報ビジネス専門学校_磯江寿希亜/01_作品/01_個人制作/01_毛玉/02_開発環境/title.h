#ifndef _TITLE_H_
#define _TITLE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "object2D.h"
#include "mode.h"

//=============================================================================
// �O����`
//=============================================================================
class CTitleRogo;
class CFade;

class CPlayer;
class CCamera;
class CMeshfield;
class CLight;
class CMeshLine;
class CSkyField;
//=============================================================================
// �N���X�̒�`
//=============================================================================
class CTitle : public CMode
{
public:
	const int m_modeMax = 3;	//��ʑJ�ڂ̍ő吔	//���[�h���ɂ���ĕύX
	const int m_modeMin = 1;	//��ʑJ�ڂ̍ŏ���	//�ύX�s�v
public:
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	CTitle();
	~CTitle() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��
	static CTitle *Create();		// ��������

	static CPlayer *GetPlayer() { return m_pPlayer; }
	static CMeshfield *GetMeshfield() { return m_pMeshField; }

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���̃|�C���^
	CObject2D *m_pObject2D;					// �I�u�W�F�N�g2D�̃|�C���^
	static bool m_bTitleEnter;				// Enter�����������̃t���O

	CObject2D* m_pTitle;

	CObject2D* m_pGame;
	CObject2D* m_pRanking;
	CObject2D* m_ptutelial;


	static CPlayer *m_pPlayer;				// �v���C���[�̃|�C���^
	static CLight *m_pLight;				// ���C�g�̃|�C���^
	static CMeshfield *m_pMeshField;		// ���b�V���t�B�[���h�̃|�C���^
	static CMeshLine *m_pMeshLine;			//	���b�V�����C��
	
	CFade *m_pFade;							// �t�F�[�h�̃|�C���^

	bool m_bmodeflg;
	bool m_modebool;
	int cnt;

	int m_modecount;			//��ʑJ�ڂ̂��߂̃J�E���g

};

#endif