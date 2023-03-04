//#ifndef _MAP_CAMERA_H_
//#define _MAP_CAMERA_H_
//
//#include "main.h"
//
////=============================================================================
////�}�N����`
////=============================================================================
//#define CAMERA_SPEED	(10.0f)		//�J�����̈ړ����x
//
////=============================================================================
//// �N���X�̒�`
////=============================================================================
//class CMapcamera
//{
//public:
//	//-------------------------------------------------------------------------
//	// �R���X�g���N�^�ƃf�X�g���N�^
//	//-------------------------------------------------------------------------
//	explicit CMapcamera();
//	~CMapcamera();
//
//	//-------------------------------------------------------------------------
//	// �����o�[�֐�
//	//-------------------------------------------------------------------------
//	HRESULT Init(void);					// ����������
//	void Uninit(void);					// �I������
//	void Update(void);					// �X�V����
//
//	void SetCamera(bool bfixed, bool btypecom);				// �ݒ菈��
//	void SetViewport();	//�������̈�
//
//	static CMapcamera *Create();		// ��������
//
//	void SetTarget();
//
//	void SetSIz_Camera(D3DXVECTOR2 siz);
//	void SetPos_Camera(D3DXVECTOR2 pos);
//	void SetPosV(D3DXVECTOR3 posv) { m_posV = posv; }
//	void SetPosR(D3DXVECTOR3 posr) { m_posR = posr; }
//
//
//	D3DXVECTOR3 GetRot() { return m_rot; }
//
//	D3DXMATRIX GetMtxView() { return m_mtxView; }
//	D3DXMATRIX GetProjection() { return m_mtxProjection; }
//
//	D3DVIEWPORT9 GetViewPort() {return m_game_viewport;}
//
//private:
//	//-------------------------------------------------------------------------
//	// �����o�[�ϐ�
//	//-------------------------------------------------------------------------
//
//	D3DXVECTOR3	m_posV;				//[2]���_
//	D3DXVECTOR3	m_posR;				//[2]�����_
//	D3DXVECTOR3	m_vecU;				//[2]������x�N�g��
//	D3DXVECTOR3	m_posVDest;			//�ړI�̎��_
//	D3DXVECTOR3	m_posRDest;			//�ړI�̒����_
//	D3DXMATRIX	m_mtxProjection;	// [2]�v���W�F�N�V�����}�g���b�N�X
//	D3DXMATRIX	m_mtxView;			//[2] �r���[�}�g���b�N�X
//	float		m_fDistance;		//���_���璍���_�̋���
//	D3DXVECTOR3 m_rot;		//����
//
//	D3DXVECTOR3 m_CamPosVm;	//[2]�v�Z��
//	D3DXVECTOR3 m_CamPosRm;	//[2]
//
//	D3DXVECTOR2 m_Siz;		//��ʃT�C�Y
//
//	D3DVIEWPORT9 m_game_viewport;	//[2]��ʕ���
//
//protected:
//
//	CRenderer * m_prenderer;
//};
//#endif