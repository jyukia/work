//=============================================================================
//
// ���[�V�����L�����N�^�[3D�N���X(model3D.h)
// Author : �������l
// �T�v : ���[�V�����L�����N�^�[3D�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "motion_model3D.h"
#include "motion.h"
#include "renderer.h"
#include "application.h"
#include "objectX.h"
#include "parts.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : ���[�V�����L�����N�^�[3D�𐶐�����
//=============================================================================
CMotionModel3D * CMotionModel3D::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CMotionModel3D *pMotionModel3D = nullptr;

	// �������̉��
	pMotionModel3D = new CMotionModel3D;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pMotionModel3D != nullptr);

	// ���l�̏�����
	pMotionModel3D->Init();

	// �C���X�^���X��Ԃ�
	return pMotionModel3D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CMotionModel3D::CMotionModel3D(int nPriority) :
	CObject(nPriority),
	m_pMotion(nullptr),		// ���[�V�������
	m_mtxWorld(D3DXMATRIX()),									// ���[���h�}�g���b�N�X
	m_pos(D3DXVECTOR3()),										// �ʒu
	m_posOld(D3DXVECTOR3()),									// �ߋ��ʒu
	m_rot(D3DXVECTOR3()),										// ����
	m_size(D3DXVECTOR3()),										// �傫��
	m_isUpdateStop(false)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CMotionModel3D::~CMotionModel3D()
{
	assert(m_pMotion == nullptr);
}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CMotionModel3D::Init()
{
	// �ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ߋ��ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����

	return E_NOTIMPL;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CMotionModel3D::Uninit()
{
	if (m_pMotion != nullptr)
	{// �I������
		m_pMotion->Uninit();

		// �������̉��
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// �I�u�W�F�N�g2D�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CMotionModel3D::Update()
{
	if (m_pMotion != nullptr)
	{// ���[�V�����ԍ��̐ݒ�
		if (!m_isUpdateStop)
		{
			m_pMotion->Update();
		}
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CMotionModel3D::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);											// �s�񏉊����֐�

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			// �s���]�֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						// �s��|���Z�֐� 

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				// �s��ړ��֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);					// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	if (m_pMotion != nullptr)
	{// �p�[�c�̕`��ݒ�
		m_pMotion->SetParts(m_mtxWorld);
	}
}

//=============================================================================
// ���[�V�����̐ݒ�
// Author : �������l
// �T�v : ���[�V�����̓ǂݍ��݂��s��
//=============================================================================
void CMotionModel3D::SetMotion(const char * pName)
{
	if (m_pMotion != nullptr)
	{// �I������
		m_pMotion->Uninit();

		// �������̉��
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// ���[�V�������
	m_pMotion = new CMotion(pName);
	assert(m_pMotion != nullptr);

	// ���[�V�����̏����ݒ�
	m_pMotion->SetMotion(0);

	// ���[�V�����ԍ��̐ݒ�
	m_pMotion->SetNumMotion(0);

	SetMaxMinVtx();
}


void CMotionModel3D::SetMaxMinVtx()
{

	D3DXVECTOR3 minVtx(FLT_MAX, FLT_MAX, FLT_MAX);
	D3DXVECTOR3 maxVtx(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (int nCntParts = 0; nCntParts < m_pMotion->GetMaxParts(); nCntParts++)
	{
		D3DXVECTOR3 partsMinVtx = m_pMotion->GetParts(nCntParts)->GetMinVtx();
		D3DXVECTOR3 partsMaxVtx = m_pMotion->GetParts(nCntParts)->GetMaxVtx();

		//X
		if (partsMinVtx.x < minVtx.x)
		{//�ŏ��l
			minVtx.x = partsMinVtx.x;
		}
		if (partsMaxVtx.x > maxVtx.x)
		{//�ő�l
			maxVtx.x = partsMaxVtx.x;
		}

		//Y
		if (partsMinVtx.y < minVtx.y)
		{//�ŏ��l
			minVtx.y = partsMinVtx.y;
		}
		if (partsMaxVtx.y > maxVtx.y)
		{//�ő�l
			maxVtx.y = partsMaxVtx.y;
		}

		//Z
		if (partsMinVtx.z < minVtx.z)
		{//�ŏ��l
			minVtx.z = partsMinVtx.z;
		}
		if (partsMaxVtx.z > maxVtx.z)
		{//�ő�l
			maxVtx.z = partsMaxVtx.z;
		}
	}

	m_MinVtx = minVtx;
	m_MaxVtx = maxVtx;
}

//=============================================================================
// �����̓����蔻��
//=============================================================================
bool CMotionModel3D::SegmentCollision(CObjectX* inObjectX)
{
	if (!inObjectX->IsCollision())
	{
		return false;
	}

	// �ϐ��錾
	D3DXVECTOR3 interval = GetPos() - inObjectX->GetPos();

	D3DXVECTOR3 thisVecX;
	D3DXVECTOR3 thisVecY;
	D3DXVECTOR3 thisVecZ;
	D3DXVECTOR3 thisNormalizeVecX;
	D3DXVECTOR3 thisNormalizeVecY;
	D3DXVECTOR3 thisNormalizeVecZ;

	{
		// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot;

		D3DXMATRIX mtxWorld;
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	// �s���]�֐�
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);				// �s��|���Z�֐� 

		thisVecX = D3DXVECTOR3(m_size.x, 0.0f, 0.0f);
		thisVecY = D3DXVECTOR3(0.0f, m_size.y, 0.0f);
		thisVecZ = D3DXVECTOR3(0.0f, 0.0f, m_size.z);
		D3DXVec3TransformCoord(&thisVecX, &thisVecX, &mtxWorld);
		D3DXVec3TransformCoord(&thisVecY, &thisVecY, &mtxWorld);
		D3DXVec3TransformCoord(&thisVecZ, &thisVecZ, &mtxWorld);
		D3DXVec3Normalize(&thisNormalizeVecX, &thisVecX);
		D3DXVec3Normalize(&thisNormalizeVecY, &thisVecY);
		D3DXVec3Normalize(&thisNormalizeVecZ, &thisVecZ);
	}

	D3DXVECTOR3 targetVecX;
	D3DXVECTOR3 targetVecY;
	D3DXVECTOR3 targetVecZ;
	D3DXVECTOR3 targetNormalizeVecX;
	D3DXVECTOR3 targetNormalizeVecY;
	D3DXVECTOR3 targetNormalizeVecZ;

	{
		// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot;

		D3DXMATRIX mtxWorld;
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		D3DXVECTOR3 rot = inObjectX->GetRot();
		D3DXVECTOR3 size = inObjectX->GetSize();

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);	// �s���]�֐�
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);			// �s��|���Z�֐� 

		targetVecX = D3DXVECTOR3(size.x, 0.0f, 0.0f);
		targetVecY = D3DXVECTOR3(0.0f, size.y, 0.0f);
		targetVecZ = D3DXVECTOR3(0.0f, 0.0f, size.z);
		D3DXVec3TransformCoord(&targetVecX, &targetVecX, &mtxWorld);
		D3DXVec3TransformCoord(&targetVecY, &targetVecY, &mtxWorld);
		D3DXVec3TransformCoord(&targetVecZ, &targetVecZ, &mtxWorld);
		D3DXVec3Normalize(&targetNormalizeVecX, &targetVecX);
		D3DXVec3Normalize(&targetNormalizeVecY, &targetVecY);
		D3DXVec3Normalize(&targetNormalizeVecZ, &targetVecZ);
	}

	float thisRadius;
	float targetRadius;
	float length;

	//A.e1
	thisRadius = D3DXVec3Length(&thisVecX);
	targetRadius = LenSegOnSeparateAxis(&thisNormalizeVecX, &targetVecX, &targetVecY, &targetVecZ);
	length = fabs(D3DXVec3Dot(&interval, &thisNormalizeVecX));
	if (length > thisRadius + targetRadius)
	{
		return false;
	}

	//A.e2
	thisRadius = D3DXVec3Length(&thisVecY);
	targetRadius = LenSegOnSeparateAxis(&thisNormalizeVecY, &targetVecX, &targetVecY, &targetVecZ);
	length = fabs(D3DXVec3Dot(&interval, &thisNormalizeVecY));
	if (length > thisRadius + targetRadius)
	{
		return false;
	}

	//A.e3
	thisRadius = D3DXVec3Length(&thisVecZ);
	targetRadius = LenSegOnSeparateAxis(&thisNormalizeVecZ, &targetVecX, &targetVecY, &targetVecZ);
	length = fabs(D3DXVec3Dot(&interval, &thisNormalizeVecZ));
	if (length > thisRadius + targetRadius)
	{
		return false;
	}

	//B.e1
	thisRadius = D3DXVec3Length(&targetVecX);
	targetRadius = LenSegOnSeparateAxis(&targetNormalizeVecX, &thisVecX, &thisVecY, &thisVecZ);
	length = fabs(D3DXVec3Dot(&interval, &targetNormalizeVecX));
	if (length > thisRadius + targetRadius)
	{
		return false;
	}

	//B.e2
	thisRadius = D3DXVec3Length(&targetVecY);
	targetRadius = LenSegOnSeparateAxis(&targetNormalizeVecY, &thisVecX, &thisVecY, &thisVecZ);
	length = fabs(D3DXVec3Dot(&interval, &targetNormalizeVecY));
	if (length > thisRadius + targetRadius)
	{
		return false;
	}

	//B.e3
	thisRadius = D3DXVec3Length(&targetVecZ);
	targetRadius = LenSegOnSeparateAxis(&targetNormalizeVecZ, &thisVecX, &thisVecY, &thisVecZ);
	length = fabs(D3DXVec3Dot(&interval, &targetNormalizeVecZ));
	if (length > thisRadius + targetRadius)
	{
		return false;
	}

	//C11
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecX, &targetNormalizeVecX);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecY, &thisVecZ);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecY, &targetVecZ);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C12
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecX, &targetNormalizeVecY);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecY, &thisVecZ);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecX, &targetVecZ);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C13
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecX, &targetNormalizeVecZ);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecY, &thisVecZ);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecX, &targetVecZ);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C21
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecY, &targetNormalizeVecX);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecX, &thisVecZ);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecY, &targetVecZ);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C22
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecY, &targetNormalizeVecY);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecX, &thisVecZ);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecX, &targetVecZ);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C23
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecY, &targetNormalizeVecZ);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecX, &thisVecZ);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecX, &targetVecY);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C31
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecZ, &targetNormalizeVecX);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecX, &thisVecY);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecX, &targetVecZ);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C32
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecZ, &targetNormalizeVecX);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecX, &thisVecY);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecX, &targetVecZ);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C33
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecZ, &targetNormalizeVecZ);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecX, &thisVecY);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecX, &targetVecY);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}
	return true;
}

float CMotionModel3D::LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	float r1 = fabs(D3DXVec3Dot(Sep, e1));
	float r2 = fabs(D3DXVec3Dot(Sep, e2));
	float r3 = e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0;
	return r1 + r2 + r3;
}
