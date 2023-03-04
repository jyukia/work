//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "camera.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "game.h"
#include"DebugProc.h"
#include"SelectStage.h"
#include "goal.h"
#include "inputjoypad.h"

#include <math.h>

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
D3DXVECTOR3 CCamera::m_rot;
D3DXMATRIX	CCamera::m_mtxProjection;
D3DXMATRIX	CCamera::m_mtxView;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	{//�v���C���[
	 //���_�E�����_�E�������ݒ肷��i�\���̂̏������j
		int mode = CApplication::Getinstnce()->GetMode();
		if (mode == CApplication::MODE_SELECT_STAGE)
		{
			m_posV = D3DXVECTOR3(0.0f, 100.0f, -400.0f);								//���_
		}
		else
		{
			m_posV = D3DXVECTOR3(0.0f, 100.0f, -200.0f);								//���_
		}
		m_posR = D3DXVECTOR3(0.0f, 20.0f, -1.0f);								//�����_
		m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);									//������x�N�g�� ���Œ��OK!!

		m_CamPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_CamPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//{
		//	////�r���[�|�[�g�\���̕ۑ�
		//	//m_game_viewport.X = 0;
		//	//m_game_viewport.Y = 0;
		//	//m_game_viewport.Width = 1280;
		//	//m_game_viewport.Height = 720;
		//	//m_game_viewport.MaxZ = 1.0f;
		//	//m_game_viewport.MinZ = 0.0f;
		//}

	}

	float fLength1 = (m_posV.x - m_posR.x);									//���_���璍���_��X���̋���
	float fLength2 = (m_posV.z - m_posR.z);									//���_���璍���_��Z���̋���
	m_fDistance = sqrtf((fLength1 * fLength1) + (fLength2 * fLength2));		//���_���璍���_�܂ł̋���

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	//�L�[�{�[�h�̏��擾
	CInput *pInputKeyboard = CApplication::Getinstnce()->GetInput();

	int mode = CApplication::Getinstnce()->GetMode();
	//�S�[�����Ď��̃t���O
	bool goalflg = CApplication::Getinstnce()->GetpMode()->GetGoal()->Getflg();

	if (goalflg)
	{
		m_rot.y += 0.005f;
	}
	else
	{
		if (mode == CApplication::MODE_GAME || mode == CApplication::MODE_GAME1)
		{
			//�J�����̈ړ�
			//if (pInputKeyboard->Press(DIK_DOWN))
			//{//��Ɉړ�
			//	m_posV.x -= sinf(m_rot.y) * CAMERA_SPEED;
			//	m_posV.z -= cosf(m_rot.y) * CAMERA_SPEED;
			//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
			//}
			//if (pInputKeyboard->Press(DIK_UP))
			//{//���Ɉړ�
			//	m_posV.x += sinf(m_rot.y) * CAMERA_SPEED;
			//	m_posV.z += cosf(m_rot.y) * CAMERA_SPEED;
			//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
			//}
			//if (pInputKeyboard->Press(DIK_RIGHT))
			//{//���Ɉړ�
			//	m_posV.x += sinf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
			//	m_posV.z += cosf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
			//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
			//}
			//if (pInputKeyboard->Press(DIK_LEFT))
			//{//�E�Ɉړ�
			//	m_posV.x -= sinf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
			//	m_posV.z -= cosf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
			//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
			//}

			//�����_�̐���
			//if (pInputKeyboard->Press(DIK_C))
			//{//���ɐ���
			//	m_rot.y += 0.05f;
			//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
			//}
			//else if (pInputKeyboard->Press(DIK_Z))
			//{//�E�ɐ���
			//	m_rot.y -= 0.05f;
			//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
			//}

			//�R���g���[���[
			CInputJoyPad *pJoy = CApplication::GetJoy();
			//���_�̐���
			if (pInputKeyboard->Press(DIK_E)|| pJoy->GetPress(DirectJoypad::JOYPAD_R2, 0))
			{//���ɐ���
				m_rot.y += 0.03f;
			}
			else if (pInputKeyboard->Press(DIK_Q) || pJoy->GetPress(DirectJoypad::JOYPAD_L2, 0))
			{//�E�ɐ���
				m_rot.y -= 0.03f;
			}
		}
	}

	if (mode == CApplication::MODE_SELECT_STAGE)
	{
		//�v���C���[���
		D3DXVECTOR3 pos1 = D3DXVECTOR3(700.0f, 10.0f, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

		int modecount = CSelectStage::GetModeCount();
		//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans;

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxView);		//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z); //�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
		D3DXMatrixMultiply(&m_mtxView, &m_mtxView, &mtxRot);				//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)

		if (modecount == 1)
		{
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pos1.x, pos1.y, pos1.z);		//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
		}
		if (modecount == 2)
		{
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);		//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
		}

		D3DXMatrixMultiply(&m_mtxView, &m_mtxView, &mtxTrans);

		D3DXVec3TransformCoord(&m_CamPosV, &m_posV, &m_mtxView);	//���[���h�ϊ��s��
		D3DXVec3TransformCoord(&m_CamPosR, &m_posR, &m_mtxView);	//���[���h�ϊ��s��
	}
	else if (mode == CApplication::MODE_GAME || mode == CApplication::MODE_GAME1 || mode == CApplication::MODE_TITLE || mode == CApplication::MODE_RANKING)
	{
		SetTarget();
	}

}
//=============================================================================
// �ݒ菈��	(����1 true �Œ�J���� false �t���[�J����)(����2 true ���e false ���s���e)(����3 true ��ʕ������� false ����)
//=============================================================================
void CCamera::SetCamera(bool bfixed, bool btypecom)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//�r���[�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxView);

	pDevice->SetViewport(&m_game_viewport);

	if (bfixed)	//�Œ�J�������邩���Ȃ���
	{
		//�r���[�}�g���b�N�X�̍쐬
		D3DXMatrixLookAtLH(&m_mtxView,
			&m_CamPosV,
			&m_CamPosR,
			&m_vecU);
	}
	else
	{
		//�r���[�}�g���b�N�X�̍쐬
		D3DXMatrixLookAtLH(&m_mtxView,
			&m_posV,
			&m_posR,
			&m_vecU);
	}

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);
	if (btypecom)	//���e���@
	{
		//�v���W�F�N�V�����}�g���b�N�X�̍쐬
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(90.0f),							//����p
			(float)m_game_viewport.Width / (float)m_game_viewport.Height,		//�A�X�y�N�g��
			10.0f,											//�j�A�i�ǂ�����ǂ��܂ŃJ�����ŕ\�����邩�ݒ�j
			8000.0f);										//�t�@�[
	}
	else
	{
		// �v���W�F�N�V�����}�g���b�N�X�̍쐬(���s���e)
		D3DXMatrixOrthoLH(&m_mtxProjection,				// �v���W�F�N�V�����}�g���b�N�X
			(float)m_game_viewport.Width,				// ��
			(float)m_game_viewport.Height,				// ����
			10.0f,													// �j�A
			5000.0f);												// �t�@�[
	}

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//=============================================================================
// ��������
//=============================================================================
CCamera * CCamera::Create()
{
	//�|�C���^�錾
	CCamera *pCamera = nullptr;

	//�C���X�^���X����
	pCamera = new CCamera;

	if (pCamera != nullptr)
	{//�|�C���^�����݂�������s
		pCamera->Init();

	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	//�|�C���^��Ԃ�
	return pCamera;
}

void CCamera::SetTarget()
{
	//�v���C���[���
	D3DXVECTOR3 pPlayerPos = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetPos();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	D3DXMATRIX mtxa;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxa);        //�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

	 //�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);//�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&mtxa, &mtxa, &mtxRot);//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pPlayerPos.x, pPlayerPos.y, pPlayerPos.z);//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&mtxa, &mtxa, &mtxTrans);

	D3DXVec3TransformCoord(&m_CamPosV, &m_posV, &mtxa);//���[���h�ϊ��s��
	D3DXVec3TransformCoord(&m_CamPosR, &m_posR, &mtxa);//���[���h�ϊ��s��
}

void CCamera::SetSIz_Camera(D3DXVECTOR2 siz)
{
	m_game_viewport.Height = (DWORD)siz.y;
	m_game_viewport.Width = (DWORD)siz.x;

}

void CCamera::SetPos_Camera(D3DXVECTOR2 pos)
{
	m_game_viewport.X = (DWORD)pos.x;
	m_game_viewport.Y = (DWORD)pos.y;

}