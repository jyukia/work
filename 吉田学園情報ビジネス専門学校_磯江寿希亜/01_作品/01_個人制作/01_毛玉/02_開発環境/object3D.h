#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "object.h"


//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �\���̒�`
//=============================================================================
// ���_�f�[�^
struct VERTEX_3D
{
	D3DXVECTOR3 pos;		//���_���W
	D3DXVECTOR3 nor;		//�@���x�N�g��
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
};

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CObject3D : public CObject
{
public:
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	explicit CObject3D(int nPriority = PRIORITY_LEVEL3);
	~CObject3D() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init() override;									// ����������
	void Uninit() override;										// �I������						
	void Update() override;										// �X�V����
	void Draw() override;										// �`�揈��

	void VtxUpdate() override;									// ���_���W�X�V����
	void SetPos(D3DXVECTOR3 pos) override;						// ���W�ݒ菈��
	void SetSize(D3DXVECTOR3 size) override;					// �T�C�Y�ݒ菈��
	void SetMove(D3DXVECTOR3 move) override;					// �ړ��ʐݒ菈��
	void SetCol(D3DXCOLOR col) override;						// �F�ݒ菈��
	void SetRot(D3DXVECTOR3 rot) override;						// �����ݒ菈��
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);				// �h���̃e�N�X�`���|�C���^��e�̃e�N�X�`���|�C���^�ɑ�����鏈��
	void SetUV(float x_1, float x_2, float y_1, float y_2);		// �e�N�X�`�����W�X�V����
	D3DXVECTOR3 GetPos(void) override { return m_pos; }			// ���W�擾����
	D3DXVECTOR3 GetSize(void) override { return m_size; }		// �T�C�Y�擾����
	D3DXVECTOR3 GetMove(void) override { return m_move; }		// �ړ��ʎ擾����
	D3DXVECTOR3 GetRot(void) override { return m_rot; }			// �����擾����
	D3DXCOLOR GetCol(void) override { return m_col; }			// �F�擾����
	void SetBillboard(bool bBillboard) { m_bBillboard = bBillboard; }				// �r���{�[�h�̐ݒ�
	bool GetBillboard() { return m_bBillboard; }									// �r���{�[�h�̎擾

	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }

	static CObject3D *Create(D3DXVECTOR3 pos, int nPriority);	// ��������
	static CObject3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size,int nPriority);	// ��������

	void LoadTexture(const char *aFileName);					// �e�N�X�`���̓ǂݍ���

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_pos;						// ���W
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_size;						// �T�C�Y
	D3DXCOLOR m_col;						// �F
	float m_fLength;						// �Ίp���̒���
	float m_fAngle;							// �p�x
	EObjType m_type;						// �I�u�W�F�N�g�̃^�C�v
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	bool	m_bBillboard;		// �r���{�[�h���ǂ���

};

#endif