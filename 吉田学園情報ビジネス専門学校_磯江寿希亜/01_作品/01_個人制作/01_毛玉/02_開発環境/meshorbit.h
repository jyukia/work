#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_

//�O���錾
class CTexture;

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "objectX.h"
#include "object.h"

class CMeshOrbit : public CObject
{
public:
	explicit CMeshOrbit(int nPriority = PRIORITY_LEVEL3);
	~CMeshOrbit() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init()override;							// ����������
	void Uninit() override;							// �I������
	void Update() override;							// �X�V����
	void Draw()   override;							// �`�揈��

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);				// �h���̃e�N�X�`���|�C���^��e�̃e�N�X�`���|�C���^�ɑ�����鏈��

	void LoadTexture(const char *aFileName);					// �e�N�X�`���̓ǂݍ���

	//�Z�b�^�[
	void SetMtxParent(D3DXMATRIX *pMtx);
	void SetOfSetPos(D3DXVECTOR3 ofsetpos);

	void SetPos(D3DXVECTOR3 pos);			// ���W�ݒ菈��
	void SetCol(D3DXCOLOR col);				// �F�ݒ菈��
	void SetRot(D3DXVECTOR3 rot);			// �����ݒ菈��

	//�Q�b�^�[
	D3DXVECTOR3 GetOfSetPos() { return OfSetPos;}			//�T�C�Y�ύX
	D3DXVECTOR3 GetRot(void) { return m_rot;}		// �����擾����
	D3DXCOLOR GetCol(void) { return m_col;}			// �F�擾����

	static CMeshOrbit *Create(D3DXCOLOR col);		// ��������


private:
	D3DXMATRIX *m_pMtxParent;	//�O�Ղ̐e���f���̃}�g���b�N�X

	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X

	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_pos;
	D3DXCOLOR m_col;
	D3DXVECTOR3 OfSetPos;	//	�c���W�̕ϊ� �T�C�Y�ύX�\


	int m_pVtxMax;	//�ő吔
};

#endif