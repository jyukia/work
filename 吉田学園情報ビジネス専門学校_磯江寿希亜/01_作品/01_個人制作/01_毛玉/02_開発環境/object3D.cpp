//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "object3D.h"
#include "renderer.h"
#include "application.h"
#include "main.h"
#include"camera.h"
#include"light.h"


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject3D::CObject3D(int nPriority) :
	CObject(nPriority),
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_fLength(0.0f),
	m_fAngle(0.0f),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f))
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject3D::~CObject3D()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	////�o�b�t�@����������Ă��畁�ʂɒʂ�(NULL�`�F�b�N)
	assert(m_pVtxBuff == nullptr);

}

//=============================================================================
// �I�u�W�F�N�g�̏�����
//=============================================================================
HRESULT CObject3D::Init()
{
	{
		m_bBillboard = false;							// �r���{�[�h���ǂ���
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D) * 4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̓ǂݍ���
	//LoadTexture("Data\\TEXTURE\\yuka000.jpg");

	//�Ίp���̒����Z�o
	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y)));

	//�p�x�̎Z�o
	m_fAngle = atan2f(m_size.x, m_size.y);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	pVtx[1].pos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	pVtx[2].pos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	pVtx[3].pos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//�e���_�̖@���̐ݒ�i���x�N�g���̑傫����1�ɂ���K�v������j
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I��
//=============================================================================
void CObject3D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	//�C���X�^���X�̉������
	Release();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V
//=============================================================================
void CObject3D::Update()
{
	//���_���W�X�V����
	VtxUpdate();
}

//=============================================================================
// �I�u�W�F�N�g�̕`��
//=============================================================================
void CObject3D::Draw()
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);			//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

	//�J�����̋t�s���ݒ�
	if (m_bBillboard)
	{
		// ���C�g�𖳌�
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// �r���[�}�g���b�N�X�̐ݒ�
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		// �J�����t�s���ݒ�
		D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
		m_mtxWorld._41 = 0.0f;
		m_mtxWorld._42 = 0.0f;
		m_mtxWorld._43 = 0.0f;
	}
	else
	{
		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z); //�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)
	}

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);					//���[���h���W�s��̐ݒ�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);

}
//=============================================================================
// ���_���W�X�V����
//=============================================================================
void CObject3D::VtxUpdate()
{
	if (m_pVtxBuff != nullptr)
	{
		//���_���ւ̃|�C���^
		VERTEX_3D*pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		if (m_bBillboard)	//�r���{�[�h��
		{
			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_size.x,  m_size.y,  0.0f);
			pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_size.x,  -m_size.y,  0.0f);
		}
		else
		{	
			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, m_size.z);
			pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, m_size.z);
			pVtx[2].pos = D3DXVECTOR3(-m_size.x, m_size.y, -m_size.z);
			pVtx[3].pos = D3DXVECTOR3(m_size.x, m_size.y, -m_size.z);
		}
		//���_�J���[�̍X�V
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;


		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// ���W�ݒ�֐�
//=============================================================================
void CObject3D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	VtxUpdate();
}

//=============================================================================
// �T�C�Y�ݒ�֐�
//=============================================================================
void CObject3D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// �ړ��͐ݒ�֐�
//=============================================================================
void CObject3D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// �F�ݒ�֐�
//=============================================================================
void CObject3D::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// �����ݒ�֐�
//=============================================================================
void CObject3D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �h���̃e�N�X�`���|�C���^��e�̃e�N�X�`���|�C���^�ɑ�����鏈��
//=============================================================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;		//�e�N�X�`���̃|�C���^
}

//=============================================================================
// �e�N�X�`�����W�X�V����
//=============================================================================
void CObject3D::SetUV(float x_1, float x_2, float y_1, float y_2)
{
	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(x_1, y_1);
	pVtx[1].tex = D3DXVECTOR2(x_2, y_1);
	pVtx[2].tex = D3DXVECTOR2(x_1, y_2);
	pVtx[3].tex = D3DXVECTOR2(x_2, y_2);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ��������
//=============================================================================
CObject3D * CObject3D::Create(D3DXVECTOR3 pos, int nPriority)
{
	//�|�C���^�錾
	CObject3D *pObject3D = nullptr;

	//�C���X�^���X����
	pObject3D = new CObject3D(nPriority);

	if (pObject3D != nullptr)
	{//�|�C���^�����݂�������s
		pObject3D->SetPos(pos);
		pObject3D->SetSize(D3DXVECTOR3(150.0f, 0.0f, 150.0f));
		pObject3D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pObject3D->Init();
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	//�|�C���^��Ԃ�
	return pObject3D;
}

CObject3D * CObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nPriority)
{
	//�|�C���^�錾
	CObject3D *pObject3D = nullptr;

	//�C���X�^���X����
	pObject3D = new CObject3D(nPriority);

	if (pObject3D != nullptr)
	{//�|�C���^�����݂�������s
		pObject3D->SetPos(pos);
		pObject3D->SetRot(rot);
		pObject3D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pObject3D->Init();
		pObject3D->SetSize(size);

	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	//�|�C���^��Ԃ�
	return pObject3D;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
void CObject3D::LoadTexture(const char * aFileName)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		aFileName,
		&m_pTexture);
}
