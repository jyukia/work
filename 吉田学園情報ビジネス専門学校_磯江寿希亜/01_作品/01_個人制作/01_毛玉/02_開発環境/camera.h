#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define CAMERA_SPEED	(10.0f)		//�J�����̈ړ����x

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CCamera
{
public:
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	explicit CCamera();
	virtual ~CCamera();

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	virtual HRESULT Init(void);					// ����������
	virtual void Uninit(void);					// �I������
	virtual void Update(void);					// �X�V����

	void SetCamera(bool bfixed, bool btypecom);				// �ݒ菈��
	static CCamera *Create();		// ��������

	void SetTarget();

	void SetSIz_Camera(D3DXVECTOR2 siz);
	void SetPos_Camera(D3DXVECTOR2 pos);

	D3DXVECTOR3 GetPosV() { return m_posV; }	//�ʒu�@������
	void SetPosV(D3DXVECTOR3 posv) { m_posV = posv; }

	D3DXVECTOR3 GetPosR() { return m_posR; }	//���x�X�@�������
	void SetPosR(D3DXVECTOR3 posr) { m_posR = posr; }

	static D3DXVECTOR3 GetRot() { return m_rot; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

	D3DVIEWPORT9 GetViewPort() { return m_game_viewport; }
	void SetViewPort(D3DVIEWPORT9 view) { m_game_viewport = view; }

	static D3DXMATRIX GetMtxView() { return m_mtxView; }
	static D3DXMATRIX GetProjection() { return m_mtxProjection; }

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------

	D3DXVECTOR3	m_posV;				//[2]���_
	D3DXVECTOR3	m_posR;				//[2]�����_
	D3DXVECTOR3	m_vecU;				//[2]������x�N�g��
	D3DXVECTOR3	m_posVDest;			//�ړI�̎��_
	D3DXVECTOR3	m_posRDest;			//�ړI�̒����_
	static D3DXMATRIX	m_mtxProjection;	// [2]�v���W�F�N�V�����}�g���b�N�X
	static D3DXMATRIX	m_mtxView;			//[2] �r���[�}�g���b�N�X
	float		m_fDistance;		//���_���璍���_�̋���

	D3DXVECTOR3 m_CamPosV;	// [2]�v�Z��
	D3DXVECTOR3 m_CamPosR;	//[2]

	D3DXVECTOR2 m_Siz;		//��ʃT�C�Y

	D3DVIEWPORT9 m_game_viewport;	//[2]��ʕ���

	int m_cnt;

	bool bcam;
	bool bcom1;
	bool flgstp;

protected:
	static D3DXVECTOR3 m_rot;		//����
};

#endif