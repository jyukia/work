#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "object2D.h"
#include "mode.h"

//=============================================================================
// �O����`
//=============================================================================
class CPlayer;
class CCamera;
class CMeshfield;
class CFade;
class CLight;
class CScore;
class CMovelife;
class CMeshLine;
class CGoal;
class CItem;
class Cpreparation;
class CBillboard;
class CTimer;
class CParticle2D;
class CSound;
class CPause;
class CObject3D;
//=============================================================================
// �N���X�̒�`
//=============================================================================
class CGame : public CMode
{
public:
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	CGame();
	~CGame() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��
	static CGame *Create();			// ��������

	static CMeshfield *GetMeshfield() { return m_pMeshField; }
	static CPause* GetPause() { return pPause; }

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	CObject2D *m_pObject2D;					// �I�u�W�F�N�g2D�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���̃|�C���^
	static CLight *m_pLight;				// ���C�g�̃|�C���^
	static CMeshfield *m_pMeshField;		// ���b�V���t�B�[���h�̃|�C���^	
	static CGoal *m_pGoal;				//�S�[���|�C���^
	
	static CPause* pPause;

	//�ړ��̓A�b�v
	static CItem *m_pItem;

	static CItem *m_pItemTimeUp;
	static CItem *m_pItemTimeUp1;

	CTimer *m_Timer;

	Cpreparation *m_pPreparation;	//�Q�[���J�n�̍��}�|�C���^

	CFade *m_pFade;
	CCamera *m_pCamera;

	CObject2D* m_pCompass;

	CObject2D* m_pTimeUi;
	CObject2D* m_pTime_Lope_Ui;
	CObject3D* goalui;
	CMovelife* m_Movelife;

	D3DXVECTOR3 m_rot;

	//�ړ��\����
	static CMovelife* GetMovelife() { return pMovelife; }
	static CMovelife* pMovelife;

	float Xslide;

	int CntTime;
	//���b�V�����C��
	CMeshLine *m_pMeshLine;

	CParticle2D* m_particle2d;

	CBillboard* m_Billboard;

	bool returnflg;

	bool Goalflg;

	int GoalCnt;
};
#endif