////=============================================================================
//// �C���N���[�h�t�@�C��
////=============================================================================
//#include "mapcamera.h"
//#include "application.h"
//#include "renderer.h"
//#include "input.h"
//#include "player.h"
//#include "game.h"
//#include"DebugProc.h"
//#include"SelectStage.h"
//
//#include <math.h>
//
////=============================================================================
//// �ÓI�����o�ϐ��錾
////=============================================================================
//
////=============================================================================
//// �R���X�g���N�^
////=============================================================================
//CMapcamera::CMapcamera()
//{
//}
//
////=============================================================================
//// �f�X�g���N�^
////=============================================================================
//CMapcamera::~CMapcamera()
//{
//}
//
////=============================================================================
//// ����������
////=============================================================================
//HRESULT CMapcamera::Init(void)
//{
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
//
//	m_posV = D3DXVECTOR3(0.0f, 200.0f, -10.0f);							//���_
//	m_posR = D3DXVECTOR3(0.0f, 20.0f, -1.0f);								//�����_
//	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);									//������x�N�g�� ���Œ��OK!!
//
//	m_CamPosVm = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_CamPosRm = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//	float fLength1 = (m_posV.x - m_posR.x);									//���_���璍���_��X���̋���
//	float fLength2 = (m_posV.z - m_posR.z);									//���_���璍���_��Z���̋���
//	m_fDistance = sqrtf((fLength1 * fLength1) + (fLength2 * fLength2));		//���_���璍���_�܂ł̋���
//
//	return S_OK;
//}
//
////=============================================================================
//// �I������
////=============================================================================
//void CMapcamera::Uninit(void)
//{
//}
//
////=============================================================================
//// �X�V����
////=============================================================================
//void CMapcamera::Update(void)
//{
//	int mode = CApplication::Getinstnce()->GetMode();
//	if (mode == CApplication::MODE_TITLE)
//	{
//		//�r���[�|�[�g�\���̕ۑ�
//		m_game_viewport.X = 0;
//		m_game_viewport.Y = 0;
//		m_game_viewport.Width = 0;
//		m_game_viewport.Height = 0;
//		m_game_viewport.MaxZ = 1.0f;
//		m_game_viewport.MinZ = 0.0f;
//
//	}
//	else if (mode == CApplication::MODE_GAME || mode == CApplication::MODE_GAME1)
//	{//�v���C���[
//	 //���_�E�����_�E�������ݒ肷��i�\���̂̏������j
//		int mode = CApplication::Getinstnce()->GetMode();
//
//		//�r���[�|�[�g�\���̕ۑ�
//		m_game_viewport.X = 1050;
//		m_game_viewport.Y = 10;
//		m_game_viewport.Width = 200;
//		m_game_viewport.Height = 200;
//		m_game_viewport.MaxZ = 1.0f;
//		m_game_viewport.MinZ = 0.0f;
//
//	}
//
//	//�L�[�{�[�h�̏��擾
//	CInput *pInputKeyboard = CApplication::Getinstnce()->GetInput();
//
//	//�J�����̈ړ�
//	if (pInputKeyboard->Press(DIK_DOWN))
//	{//��Ɉړ�
//		m_posV.x -= sinf(m_rot.y) * CAMERA_SPEED;
//		m_posV.z -= cosf(m_rot.y) * CAMERA_SPEED;
//		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
//		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
//	}
//	if (pInputKeyboard->Press(DIK_UP))
//	{//���Ɉړ�
//		m_posV.x += sinf(m_rot.y) * CAMERA_SPEED;
//		m_posV.z += cosf(m_rot.y) * CAMERA_SPEED;
//		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
//		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
//	}
//	if (pInputKeyboard->Press(DIK_RIGHT))
//	{//���Ɉړ�
//		m_posV.x += sinf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
//		m_posV.z += cosf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
//		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
//		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
//	}
//	if (pInputKeyboard->Press(DIK_LEFT))
//	{//�E�Ɉړ�
//		m_posV.x -= sinf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
//		m_posV.z -= cosf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
//		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
//		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
//	}
//
//	//�����_�̐���
//	if (pInputKeyboard->Press(DIK_C))
//	{//���ɐ���
//		m_rot.y += 0.05f;
//		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
//		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
//	}
//	else if (pInputKeyboard->Press(DIK_Z))
//	{//�E�ɐ���
//		m_rot.y -= 0.05f;
//		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
//		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
//	}
//
//	//���_�̐���
//	if (pInputKeyboard->Press(DIK_E))
//	{//���ɐ���
//		m_rot.y += 0.05f;
//	}
//	else if (pInputKeyboard->Press(DIK_Q))
//	{//�E�ɐ���
//		m_rot.y -= 0.05f;
//	}
//
//
//}
////=============================================================================
//// �ݒ菈��	(����1 true �Œ�J���� false �t���[�J����)(����2 true ���e false ���s���e)(����3 true ��ʕ������� false ����)
////=============================================================================
//void CMapcamera::SetCamera(bool bfixed, bool btypecom)
//{
//	//�f�o�C�X�̎擾
//	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();
//
//	//�r���[�}�g���b�N�X��������
//	D3DXMatrixIdentity(&m_mtxView);
//
//	pDevice->SetViewport(&m_game_viewport);
//
//	if (bfixed)	//�Œ�J�������邩���Ȃ���
//	{
//		//�r���[�}�g���b�N�X�̍쐬
//		D3DXMatrixLookAtLH(&m_mtxView,
//			&m_CamPosVm,
//			&m_CamPosRm,
//			&m_vecU);
//	}
//	else
//	{
//		//�r���[�}�g���b�N�X�̍쐬
//		D3DXMatrixLookAtLH(&m_mtxView,
//			&m_posV,
//			&m_posR,
//			&m_vecU);
//	}
//	//�r���[�}�g���b�N�X�̐ݒ�
//	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
//
//	//�v���W�F�N�V�����}�g���b�N�X�̏�����
//	D3DXMatrixIdentity(&m_mtxProjection);
//	if (btypecom)	//���e���@
//	{
//		//�v���W�F�N�V�����}�g���b�N�X�̍쐬
//		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
//			D3DXToRadian(90.0f),							//����p
//			(float)m_game_viewport.Width / (float)m_game_viewport.Height,		//�A�X�y�N�g��
//			10.0f,											//�j�A�i�ǂ�����ǂ��܂ŃJ�����ŕ\�����邩�ݒ�j
//			5000.0f);										//�t�@�[
//	}
//	else
//	{
//		// �v���W�F�N�V�����}�g���b�N�X�̍쐬(���s���e)
//		D3DXMatrixOrthoLH(&m_mtxProjection,				// �v���W�F�N�V�����}�g���b�N�X
//			(float)m_game_viewport.Width,				// ��
//			(float)m_game_viewport.Height,				// ����
//			10.0f,													// �j�A
//			5000.0f);												// �t�@�[
//	}
//	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
//	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
//}
//
//void CMapcamera::SetViewport()
//{
//}
//
////=============================================================================
//// ��������
////=============================================================================
//CMapcamera * CMapcamera::Create()
//{
//	//�|�C���^�錾
//	CMapcamera *pCamera = nullptr;
//
//	//�C���X�^���X����
//	pCamera = new CMapcamera;
//
//	if (pCamera != nullptr)
//	{//�|�C���^�����݂�������s
//		pCamera->Init();
//	}
//	else
//	{//�|�C���^����������������s
//		assert(false);
//	}
//	//�|�C���^��Ԃ�
//	return pCamera;
//}
//
//void CMapcamera::SetTarget()
//{
//	//�v���C���[���
//	D3DXVECTOR3 pPlayerPos = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetPos();
//
//	//�v�Z�p�}�g���b�N�X
//	D3DXMATRIX mtxRot, mtxTrans;
//
//	D3DXMATRIX mtx;
//
//	//���[���h�}�g���b�N�X�̏�����
//	D3DXMatrixIdentity(&mtx);		//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)
//
//	 //�����𔽉f
//	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);//�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
//	D3DXMatrixMultiply(&mtx, &mtx, &mtxRot);//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)
//
//	//�ʒu�𔽉f
//	D3DXMatrixTranslation(&mtxTrans, pPlayerPos.x, pPlayerPos.y, pPlayerPos.z );//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
//	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);
//
//	D3DXVec3TransformCoord(&m_CamPosVm, &m_posV, &mtx);//���[���h�ϊ��s��
//	D3DXVec3TransformCoord(&m_CamPosRm, &m_posR, &mtx);//���[���h�ϊ��s��
//}
//
//void CMapcamera::SetSIz_Camera(D3DXVECTOR2 siz)
//{
//	m_game_viewport.Height = (DWORD)siz.y;
//	m_game_viewport.Width = (DWORD)siz.x;
//
//}
//
//void CMapcamera::SetPos_Camera(D3DXVECTOR2 pos)
//{
//	m_game_viewport.X = (DWORD)pos.x;
//	m_game_viewport.Y = (DWORD)pos.y;
//
//}