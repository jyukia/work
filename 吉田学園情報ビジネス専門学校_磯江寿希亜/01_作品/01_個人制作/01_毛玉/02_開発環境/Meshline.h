#ifndef _MESHLINE_H_
#define _MESHLINE_H_

//�O���錾
class CTexture;
class CMovelife;
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "objectX.h"
#include "object.h"
 
class CMeshLine : public CObject
{
public:
	//�������C����
	const int MaxLine = 10000;
	//�������C����	title
	const int MaxLineTitle = 9000;

public:

	explicit CMeshLine(int nPriority = PRIORITY_LEVEL3);
	~CMeshLine() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init()override;							// ����������
	void Uninit() override;							// �I������
	void Update() override;							// �X�V����
	void Draw()   override;							// �`�揈��

	void LoadTexture(const char * aFileName);

	//�Z�b�^�[
	void SetMtxParent(D3DXMATRIX *pMtx);
	void SetOfSetPos(D3DXVECTOR3 ofsetpos);

	void SetPos(D3DXVECTOR3 pos);			// ���W�ݒ菈��
	void SetCol(D3DXCOLOR col);				// �F�ݒ菈��
	void SetRot(D3DXVECTOR3 rot);			// �����ݒ菈��

	//�Q�b�^�[
	D3DXVECTOR3 GetOfSetPos(void) { return OfSetPos; }			//�T�C�Y�ύX
	D3DXVECTOR3 GetRot(void) { return m_rot; }		// �����擾����
	D3DXCOLOR GetCol(void) { return m_col; }			// �F�擾����

	bool GetbIsLanding() { return bIsLanding; }
	
	void SetVtxCount(int vtxcount) { m_pVtxMax = vtxcount; }

	bool GetbUseflg() { return bUseflg; }

	static CMeshLine *Create(D3DXVECTOR3 pos ,D3DXCOLOR col, D3DXVECTOR3 distancepos);		// ��������
	bool Collision(D3DXVECTOR3 *PlayerPos, D3DXVECTOR3 *PlayerSize);	//�����蔻��

	bool CollisionReturn(D3DXVECTOR3 * PlayerPos);

	int GetVtxcount() {return m_Vtxcount;}
	void AddVtxCount(int count) {	//���_�̑���
		m_Vtxcount += count;

		if (m_Vtxcount < 2)
		{
			m_Vtxcount = 2;
		}
	}


	void SetVtx(int vtx) {m_Vtxcount = vtx;}

	D3DXVECTOR3 GetCenterVtx();

	float Vec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2);
	float Vec2Dot(D3DXVECTOR3* v1, D3DXVECTOR3* v2);
private:
	D3DXMATRIX *m_pMtxParent;	//�O�Ղ̐e���f���̃}�g���b�N�X

	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X

	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_pos;
	D3DXCOLOR m_col;
	D3DXVECTOR3 OfSetPos;	//	�c���W�̕ϊ� �T�C�Y�ύX�\

	D3DXVECTOR3 m_returnpos;

	D3DXVECTOR3 m_buckpos;

	CMovelife *m_movelife;

	int m_pVtxMax;	//�ő吔

	bool bUseflg;

	int m_Vtxcount;

	static bool bIsLanding;	//���₷�ϐ�

	int m_Game_PlayerMove;
};

#endif