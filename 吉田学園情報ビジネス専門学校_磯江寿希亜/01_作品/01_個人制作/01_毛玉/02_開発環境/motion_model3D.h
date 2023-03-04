//=============================================================================
//
// 3D���[�V�����L�����N�^�[�N���X(motion_model3D.h)
// Author : �������l
// �T�v : 3D�v���C���[�������s��
//
//=============================================================================
#ifndef _MOTION_MODEL3D_H_			// ���̃}�N����`������ĂȂ�������
#define _MOTION_MODEL3D_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CMotion;
class CObjectX;

//=============================================================================
// 3D�v���C���[�N���X
// Author : �������l
// �T�v : 3D�v���C���[�������s���N���X
//=============================================================================
class CMotionModel3D : public CObject
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CMotionModel3D *Create();			// 3D�v���C���[�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CMotionModel3D(int nPriority = PRIORITY_LEVEL3);
	~CMotionModel3D();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;											// ������
	void Uninit() override;												// �I��
	void Update() override;												// �X�V
	void VtxUpdate() override {};
	void Draw() override;												// �`��

	// Setter
	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; };				// �ʒu
	void SetPosOld(D3DXVECTOR3 posOld) { m_posOld = posOld; }			// �ߋ��ʒu
	void SetRot(D3DXVECTOR3 rot) override { m_rot = rot; };				// ����
	void SetSize(D3DXVECTOR3 size) override { m_size = size; }			// �傫��
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }	// ���[���h�}�g���b�N�X�̃Z�b�^�[
	void SetMotion(const char *pName);									// ���[�V�������̐ݒ�
	void SetMove(D3DXVECTOR3 inMove) override { m_move = inMove; }
	void SetCol(D3DXCOLOR) override {};
	void SetUpdateStop(bool isStop) { m_isUpdateStop = isStop; }
	void SetMaxMinVtx();

	// Getter
	D3DXVECTOR3 GetPos() override { return m_pos; }						// �ʒu
	D3DXVECTOR3 GetPosOld() { return m_posOld; }						// �ߋ��ʒu
	D3DXVECTOR3 GetRot()  override { return m_rot; }					// ����
	D3DXVECTOR3 GetSize()  override { return m_size; }					// �傫��
	//D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }					// ���[���h�}�g���b�N�X�̃Q�b�^�[
	CMotion *GetMotion() { return m_pMotion; }							// ���[�V�������̎擾
	D3DXVECTOR3 GetMove() override { return m_move; }
	D3DXCOLOR GetCol() override { return D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetMaxVtx() { return m_MaxVtx; }
	D3DXVECTOR3 GetMinVtx() { return m_MinVtx; }
	D3DXMATRIX *GetMtxWorld(void) { return &m_mtxWorld; }

	bool SegmentCollision(CObjectX* inObjectX);
	float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0);

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CMotion			*m_pMotion;				// ���[�V�����C���X�^���X
	D3DXVECTOR3		m_MinVtx;				// ���f���̒��_�ŏ��l
	D3DXVECTOR3		m_MaxVtx;				// ���f���̒��_�ő�l
	D3DXMATRIX		m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3		m_pos;					// �ʒu
	D3DXVECTOR3		m_move;					// 
	D3DXVECTOR3		m_posOld;				// �ߋ��ʒu
	D3DXVECTOR3		m_rot;					// ����
	D3DXVECTOR3		m_size;					// �傫��
	bool			m_isUpdateStop;			// �X�V���~������B
};

#endif