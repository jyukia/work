#ifndef _SELECT_STAGE_H_
#define _SELECT_STAGE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "object2D.h"
#include "mode.h"
#include "objectX.h"

//=============================================================================
// �O����`
//=============================================================================
class CFade;

class CCamera;
class CLight;
//=============================================================================
// �N���X�̒�`
//=============================================================================
class CSelectStage : public CMode
{
public:

	enum SELECTMODE
	{
		MODE_NONE = 0,
		MODE_MAP,
		MODE_MAP1,
		SELECTMODEMAX
	};

	float m_Angle = 10.0f;

	const int m_modeMax = 2;	//��ʑJ�ڂ̍ő吔	//���[�h���ɂ���ĕύX
	const int m_modeMin = 1;	//��ʑJ�ڂ̍ŏ���	//�ύX�s�v
public:
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	CSelectStage();
	~CSelectStage() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��
	static CSelectStage *Create();		// ��������

	static int GetModeCount(void) {return m_modeSelectcount;}

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���̃|�C���^
	CObject2D *m_pObject2D;					// �I�u�W�F�N�g2D�̃|�C���^
	static bool m_bSelectEnter;				// Enter�����������̃t���O

	CObject2D* m_pTex;

	CObjectX* pStage;		//�X�e�[�W���f��
	CObjectX* pStage1;		//�X�e�[�W���f��

	CObject2D* stagename;		//�X�e�[�W���O
	CObject2D* stagename1;		//�X�e�[�W���O�P��

	static CLight *m_pLight;				// ���C�g�̃|�C���^
	CFade *m_pFade;							// �t�F�[�h�̃|�C���^

	bool m_bmodeflg;

	static int m_modeSelectcount;			//��ʑJ�ڂ̂��߂̃J�E���g

	float radius;
	float add_x;
	float add_z;
};

#endif