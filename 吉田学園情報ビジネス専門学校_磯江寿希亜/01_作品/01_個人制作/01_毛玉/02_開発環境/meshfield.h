#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CMeshfield : CObject
{
	//-------------------------------------------------------------------------
	// �}�N����`
	//-------------------------------------------------------------------------
	#define POLYGON_DEPTH	(200.0f)			//�|���S���̉��s��
	#define POLYGON_HEIGHT	(200.0f)			//�|���S���̍���
	#define POLYGON_WIDTH	(200.0f)			//�|���S���̕�
	#define MESHFIELD_X_BLOCK	(30)			//X�����̃u���b�N��
	#define MESHFIELD_Z_BLOCK	(30)			//Z�����̃u���b�N��
	#define MESHFIELD_VERTEX_NUM	((MESHFIELD_X_BLOCK + 1) * (MESHFIELD_Z_BLOCK + 1))									//���_��
	#define MESHFIELD_INDEXNUM		((MESHFIELD_X_BLOCK + 1) * 2 * MESHFIELD_Z_BLOCK + (MESHFIELD_Z_BLOCK - 1) * 2)		//�C���f�b�N�X��
	#define	MESHFIELD_PRIMITIVE_NUM	(MESHFIELD_X_BLOCK * (MESHFIELD_Z_BLOCK * 2) + (MESHFIELD_Z_BLOCK - 1) * 4)			//�|���S����	

public:
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	explicit CMeshfield(int nPriority = PRIORITY_LEVEL3);
	~CMeshfield() override;

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
	void LoadTexture(const char *aFileName);					// �e�N�X�`���̓ǂݍ���

	static CMeshfield *Create(const D3DXVECTOR3 pos, int nPriority);    // ��������
	bool Collision(D3DXVECTOR3 *PlayerPos, D3DXVECTOR3 *PlayerSize, bool bQuaternion);		// �����蔻��
	float GetAnswer(void) { return m_AnswerKeep; }						// ���ς̌v�Z���ʎ擾

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_pos;						// ���W
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_size;						// �T�C�Y
	D3DXCOLOR m_col;						// �F
	float m_fLength;						// �Ίp���̒���
	float m_fAngle;							// �p�x
	float m_RandHeight;						// �����_���ȍ����i�[�p�ϐ�
	float m_fRotMove;						// sin�g
	float m_fRot;							// sin�g�̊p�x
	float m_AnswerKeep;						// ���ς̌v�Z���ʕۑ�
	EObjType m_type;						// �I�u�W�F�N�g�̃^�C�v
	D3DXMATRIX m_mtxWorldMeshField;			// ���b�V���t�B�[���h�̒��_���
};

#endif