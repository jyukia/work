#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "objectX.h"

//=============================================================================
// �O����`
//=============================================================================
class CShadow;
class CMeshOrbit;
class CMeshLine;
//=============================================================================
// �N���X�̒�`
//=============================================================================
class CPlayer : public CObjectX
{
public:
	enum ScaleType
	{
	TypeScaleNone = 0,
	TypeScaleUp,
	TypeScaleDown,

	TypeScaleMax
	};

	const D3DXVECTOR3 m_PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	static const float SPEED_POWER;
	static const float JUMP_POWER;
	static const float GRAVITY_POWER;

	//�v���C���[�̐U��ނ�����
	const float PurposeRot = 0.08f;
public:
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	explicit CPlayer(int nPriority = PRIORITY_LEVEL3);
	~CPlayer() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init() override;			// ����������
	void Update() override;				// �X�V����

	//�X�e�[�W1�g�p��O�ɍs���Ȃ����邽�߂̏���
	void OutSide(D3DXVECTOR3 &Playerpos);
	//�X�e�[�W2�g�p��O�ɍs���Ȃ����邽�߂̏���
	void OutSide1(D3DXVECTOR3 &Playerpos);


	static CPlayer *Create(const D3DXVECTOR3 pos, int nPriority);    // ��������

	static int GetKeyCnt(void) { return keyCnt; }		// �J�E���g�擾����
	void SetKeyCnt(int keycnt) { keyCnt = keycnt; }

	void SetJumpFlag(bool fFlag) { m_bJumpFlag = fFlag; }

	void SetScaleType(ScaleType scaletype) { eScaleType = scaletype; }
	ScaleType GetscaleType() { return eScaleType; }

	bool GetMoveFlg() { return bMoveFlg; }
	void SetbMoveFlg(bool bmoveflg) { bMoveFlg = bmoveflg; }

	//�v���C���[�p�x
	D3DXVECTOR3 GetrotDest() { return m_rotDest; }

	//�v���C���[�̃X�s�[�h
	float Getnspeed() { return m_nSpeed; }
	void Setspeed(float Speed) { m_nSpeed = Speed; }

	//��[���h���܂ł̓v���C���[�𓮂����Ȃ��t���O
	void Setbredycheck(bool bredycheckflg) { redycheckflg = bredycheckflg; }
	bool Getbredycheck() { return redycheckflg; }
private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	ScaleType eScaleType;
	
	CShadow *m_shadow;					// �e�̃|�C���^
	CMeshOrbit *m_MeshEffect;	//���b�V���G�t�F�N�g

	D3DXVECTOR3 m_rotDest;				// �ړI�̊p�x
	D3DXVECTOR3 m_posOld;				// �O��̈ʒu
	float m_nSpeed;						// �X�s�[�h
	float m_inertia;					//����
	bool m_bIsLandingUp;				// �㑤�����蔻��t���O
	bool m_bIsLanding;					// �����蔻��t���O
	bool m_bJumpFlag;					// �W�����v�������ǂ����̃t���O
	bool m_bIsLandingMesh;				// ���b�V�������蔻��t���O
	bool bScale;
	bool bMoveFlg;

	CMeshLine *m_pMeshLine;

	//�N�H�[�^�j�I���v�Z���g�p
	static int keyCnt;
	//�N�H�[�^�j�I���g�p�̃t���O�擾
	bool Quaternionflg;

	//��[���h���܂ł̓v���C���[�𓮂����Ȃ��t���O
	bool redycheckflg;

	//�ړ����̃N�H�[�^�j�I������
	bool moverot;

	std::vector<D3DXVECTOR3> m_logPos;

};
#endif