#ifndef _LINE_H_
#define _LINE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CLine : public CObject
{
public:
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	explicit CLine(int nPriority = PRIORITY_LEVEL3);
	~CLine() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init() override;									// ����������
	void Uninit() override;										// �I������						
	void Update() override;										// �X�V����
	void Draw() override;										// �`�揈��
	void VtxUpdate() override {};								// ���_���W�X�V����
	void SetPos(D3DXVECTOR3 pos) override;						// ���W�ݒ菈��
	void SetSize(D3DXVECTOR3 size) override;					// �T�C�Y�ݒ菈��
	void SetMove(D3DXVECTOR3 move) override;					// �ړ��ʐݒ菈��
	void SetCol(D3DXCOLOR col) override;						// �F�ݒ菈��
	void SetRot(D3DXVECTOR3 rot) override;						// �����ݒ菈��
	D3DXVECTOR3 GetPos(void) override { return m_pos; }			// ���W�擾����
	D3DXVECTOR3 GetSize(void) override { return m_size; }		// �T�C�Y�擾����
	D3DXVECTOR3 GetMove(void) override { return m_move; }		// �ړ��ʎ擾����
	D3DXVECTOR3 GetRot(void) override { return m_rot; }			// �����擾����
	D3DXCOLOR GetCol(void) override { return m_col; }			// �F�擾����
	void SetLine();												// �Z�b�g���C������

	static CLine *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 goal, D3DXCOLOR col, int nPriority);		// ��������

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	D3DXVECTOR3 m_pos;						// ���W
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_size;						// �T�C�Y
	D3DXVECTOR3 m_start;					// �n�_
	D3DXVECTOR3 m_goal;						// �I�_
	D3DXCOLOR m_col;						// �F
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
};

#endif