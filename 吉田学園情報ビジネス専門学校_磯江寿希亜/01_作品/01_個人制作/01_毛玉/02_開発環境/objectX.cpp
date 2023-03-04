//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "objectX.h"
#include "renderer.h"
#include "application.h"
#include "main.h"
#include "objectX_group.h"
#include "texture.h"
#include "player.h"
#include"light.h"
#include"camera.h"
#include "Mapcamera.h"

D3DXVECTOR3 CObjectX::m_axis;    // ��]��

CObjectX::MODEL_MATERIAL *CObjectX::m_material = nullptr;		// �}�e���A�����

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObjectX::CObjectX(int nPriority) :
	CObject(nPriority),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f)),
	m_scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_pParent(nullptr)
{
	//�I�u�W�F�N�g�̃^�C�v�Z�b�g����
	CObject::SetType(OBJTYPE_MODEL);

	pEffect = NULL;
	m_hmWVP = NULL;
	m_hmWIT = NULL;
	m_hvLightDir = NULL;
	m_hvCol = NULL;
	m_hvEyePos = NULL;
	m_hTechnique = NULL;
	m_hTexture = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObjectX::~CObjectX()
{
}

//=============================================================================
// �I�u�W�F�N�g�̏�����
//=============================================================================
HRESULT CObjectX::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

		{
			D3DXCreateEffectFromFile(
				pDevice, "Effect.fx", NULL, NULL,
				0, NULL, &pEffect, nullptr);

			m_hTechnique = pEffect->GetTechniqueByName("Diffuse");				//�G�t�F�N�g
			m_hTexture = pEffect->GetParameterByName(NULL, "Tex");				//�e�N�X�`��
			m_hmWVP = pEffect->GetParameterByName(NULL, "mWVP");				//���[�J��-�ˉe�ϊ��s��
			m_hmWIT = pEffect->GetParameterByName(NULL, "mWIT");				//���[�J��-���[���h�ϊ��s��
			m_hvLightDir = pEffect->GetParameterByName(NULL, "vLightDir");		//���C�g�̕���
			m_hvCol = pEffect->GetParameterByName(NULL, "vColor");				//���_�J���[
			m_hvEyePos = pEffect->GetParameterByName(NULL, "vEyePos");
			m_hBool = pEffect->GetParameterByName(NULL, "bTex");				// �e�N�X�`���̒��g�����邩�Ȃ������`�F�b�N����
	}
	{
		m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	// �N�H�[�^�j�I��������
	{
		m_quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
		bQuaternion = false;
	}

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I��
//=============================================================================
void CObjectX::Uninit()
{
	//�C���X�^���X�̉������
	Release();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V
//=============================================================================
void CObjectX::Update()
{
}

//=============================================================================
// �I�u�W�F�N�g�̕`��
//=============================================================================
void CObjectX::Draw()
{
		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

		D3DXMATRIX mtxRot, mtxTrans, mtxParent;		//�v�Z�p�}�g���b�N�X
		D3DMATERIAL9 matDef;				//���݂̃}�e���A���ۑ��p
		D3DXMATERIAL *pMat;					//�}�e���A���f�[�^�ւ̃|�C���^

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxSiz;

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxSiz);		//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

		D3DXMatrixScaling(&mtxSiz, m_scale.x, m_scale.y, m_scale.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxSiz);

		if (bQuaternion)
		{
			// �N�H�[�^�j�I���̎g�p�����p���̐ݒ�
			D3DXMatrixRotationQuaternion(&mtxRot, &m_quaternion);	// �N�I�[�^�j�I���ɂ��s���]
			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot); // �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
		}
		else
		{
			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
		}

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransPos, m_pos.x, m_pos.y, m_pos.z);		//(���s��ړ��֐�(��1������x,y,z�����̈ړ��s����쐬))
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransPos);

		if (m_pParent != nullptr)
		{
			mtxParent = *m_pParent->GetMtxWorld();

			// �s��|���Z�֐�
			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
		}

	Projection();

	//CMapcamera* pMapCamera = CApplication::Getinstnce()->GetMapCamera();
	//if(pMapCamera)
	//{
	//	//���[���h�}�g���b�N�X�̐ݒ�i���[���h���W�s��̐ݒ�j
	//	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//	//���݂̃}�e���A����ێ�
	//	pDevice->GetMaterial(&matDef);
	//	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	//	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	//	for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	//	{
	//		//�}�e���A���̐ݒ�
	//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
	//		//���f���p�[�c�̕`��
	//		m_pMesh->DrawSubset(nCntMat);
	//	}
	//	//�ێ����Ă����}�e���A����߂�
	//	pDevice->SetMaterial(&matDef);
	//}

	DrawMaterial();
}

void CObjectX::Draw(D3DXMATRIX mtxParent)
{
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScaling;

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	// �s���]�֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				// �s��|���Z�֐� 

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		// �s��ړ��֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);			// �s��|���Z�֐�

	// �s��|���Z�֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture = CApplication::Getinstnce()->GetTexture();

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	if (m_pBuffMat != nullptr)
	{// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
		{// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->GetTexture("NULL"));

			// ���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCntMat);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture[nCntMat]);
		}
	}

	// �ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	//DrawMaterial();

}
//=============================================================================
// �}�e���A���`��
//=============================================================================
void CObjectX::DrawMaterial()
{
	if (pEffect != NULL)
	{
		CCamera* pCamera = CApplication::Getinstnce()->GetCamera();

		D3DMATRIX viewMatrix = pCamera->GetMtxView();
		D3DMATRIX projMatrix = pCamera->GetProjection();

		CLight* lightClass = CApplication::Getinstnce()->GetLight();
		D3DLIGHT9 light = lightClass->GetLight();

		D3DXVECTOR4 v, light_pos;

		D3DXMATRIX m;

		//-------------------------------------------------
		// �V�F�[�_�̐ݒ�
		//-------------------------------------------------
		pEffect->SetTechnique(m_hTechnique);
		pEffect->Begin(NULL, 0);

		D3DXMatrixTranslation(&m, 1.0f, 0.0f, 0.0f);

		// ���[�J��-�ˉe�ϊ��s��
		D3DXMatrixInverse(&m, NULL, &m_mtxWorld);
		D3DXMatrixTranspose(&m, &m);
		pEffect->SetMatrix(m_hmWIT, &m);

		// ���[�J��-�ˉe�ϊ��s��
		m = m_mtxWorld * viewMatrix * projMatrix;
		pEffect->SetMatrix(m_hmWVP, &m);

		// ���C�g�̕���
		light_pos = D3DXVECTOR4(light.Direction.x, light.Direction.y, light.Direction.z, 0);

		D3DXMatrixInverse(&m, NULL, &m_mtxWorld);
		D3DXVec4Transform(&v, &-light_pos, &m);

		D3DXVec3Normalize((D3DXVECTOR3 *)&v, (D3DXVECTOR3 *)&v);

		//�����̑傫��
		v.w = -0.8f;
		pEffect->SetVector(m_hvLightDir, &v);

		// ���_
		m = m_mtxWorld *viewMatrix;
		D3DXMatrixInverse(&m, NULL, &m);

		//����
		v = D3DXVECTOR4(1, 0, 0, 1);

		//�}�e���A���f�[�^�̃|�C���^���擾����
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		D3DMATERIAL9 *pMtrl = &pMat->MatD3D;

		D3DXVec4Transform(&v, &v, &m);

		//���_���V�F�[�_�[�ɓn��
		pEffect->SetVector(m_hvEyePos, &v);

		for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
		{
			{
				// ���f���̐F�̐ݒ� 
				D3DXVECTOR4 Diffuse;
				Diffuse = D3DXVECTOR4(pMat[nCntMat].MatD3D.Diffuse.r, pMat[nCntMat].MatD3D.Diffuse.g, pMat[nCntMat].MatD3D.Diffuse.b, pMat[nCntMat].MatD3D.Diffuse.a);

				pEffect->SetVector(m_hvCol, &Diffuse);
			} 

			if (pTex0 != nullptr)
			{// �e�N�X�`���̓K��
				pTex0 = m_pTexture[nCntMat];
				// �e�N�X�`���̐ݒ�
				pEffect->SetTexture(m_hTexture, pTex0);
				pEffect->SetBool(m_hBool, true);
			}
			else
			{
				pEffect->SetBool(m_hBool, false);
				pEffect->SetTexture(m_hTexture,0);
			}


			pEffect->BeginPass(0);

			//���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCntMat);

			pEffect->EndPass();

			pMtrl++;
		}

		pEffect->End();
	}
	else
	{
		assert(false);
	}
}


//=============================================================================
// ���_�ő召�l�̌v�Z����
//=============================================================================
void CObjectX::CalculationVtx()
{
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;

	D3DXMatrixIdentity(&mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	// �s���]�֐�
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);					// �s��|���Z�֐�

	D3DXVec3TransformCoord(&m_MaxVtx, &m_MaxVtx, &mtxWorld);
	D3DXVec3TransformCoord(&m_MinVtx, &m_MinVtx, &mtxWorld);


	if (m_MaxVtx.x < m_MinVtx.x)
	{
		float change = m_MaxVtx.x;
		m_MaxVtx.x = m_MinVtx.x;
		m_MinVtx.x = change;
	}

	if (m_MaxVtx.y < m_MinVtx.y)
	{
		float change = m_MaxVtx.y;
		m_MaxVtx.y = m_MinVtx.y;
		m_MinVtx.y = change;
	}

	if (m_MaxVtx.z < m_MinVtx.z)
	{
		float change = m_MaxVtx.z;
		m_MaxVtx.z = m_MinVtx.z;
		m_MinVtx.z = change;
	}
}

//=============================================================================
// ���W�ݒ�֐�
//=============================================================================
void CObjectX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �T�C�Y�ݒ�֐�
//=============================================================================
void CObjectX::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// �ړ��͐ݒ�֐�
//=============================================================================
void CObjectX::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// �F�ݒ�֐�
//=============================================================================
void CObjectX::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// �����ݒ�֐�
//=============================================================================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// ��������
//=============================================================================
CObjectX * CObjectX::Create(const char *aFileName, D3DXVECTOR3 pos, int nPriority)
{
	//�|�C���^�錾
	CObjectX *pObjectX = nullptr;

	//�C���X�^���X����
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != nullptr)
	{//�|�C���^�����݂�������s
		pObjectX->Init();

		pObjectX->Setstring(aFileName);
		pObjectX->LoadModel(aFileName);
		pObjectX->SetPos(pos);
		pObjectX->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pObjectX->CalculationVtx();
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	//�|�C���^��Ԃ�
	return pObjectX;
}
//=============================================================================
// ��������
//=============================================================================
CObjectX * CObjectX::Create(D3DXVECTOR3 pos, int nPriority)
{
	//�|�C���^�錾
	CObjectX *pObjectX = nullptr;

	//�C���X�^���X����
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != nullptr)
	{//�|�C���^�����݂�������s
		pObjectX->Init();
		pObjectX->SetPos(pos);
		pObjectX->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	//�|�C���^��Ԃ�
	return pObjectX;
}

CObjectX * CObjectX::Create(const char * aFileName, D3DXVECTOR3 rot, D3DXVECTOR3 pos, int nPriority)
{
	//�|�C���^�錾
	CObjectX *pObjectX = nullptr;

	//�C���X�^���X����
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != nullptr)
	{//�|�C���^�����݂�������s
		pObjectX->Init();

		pObjectX->Setstring(aFileName);
		pObjectX->LoadModel(aFileName);
		pObjectX->SetPos(pos);
		pObjectX->SetRot(rot);
		pObjectX->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pObjectX->CalculationVtx();
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	//�|�C���^��Ԃ�
	return pObjectX;
}

//=============================================================================
// ���f���̓ǂݍ���
//=============================================================================
void CObjectX::LoadModel(const char *aFileName)
{

	CObjectXGroup *xGroup = CApplication::Getinstnce()->GetObjectXGroup();
	m_pBuffMat = xGroup->GetBuffMat(aFileName);
	m_MaxVtx = xGroup->GetMaxVtx(aFileName);
	m_pMesh = xGroup->GetMesh(aFileName);
	m_MinVtx = xGroup->GetMinVtx(aFileName);
	m_NumMat = xGroup->GetNumMat(aFileName);
	m_size = xGroup->GetSize(aFileName);
	m_pTexture = xGroup->GetTexture(aFileName);
}

//=============================================================================
// ���s���e����
//=============================================================================
void CObjectX::Projection(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;				//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;					//�}�e���A���f�[�^�ւ̃|�C���^

	//�ϐ��錾
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;
	D3DMATERIAL9 Material;

	//�V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	vecLight = -D3DXVECTOR4(0.2f, -0.5f, 0.3f, 0.0f);

	if (m_pos.y < -20.0f)
	{
		pos = D3DXVECTOR3(0.0f, -209.1f, 0.0f);
	}

	if (m_pos.y >= -20.0f)
	{
		pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	}

	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	//���[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//���[���h�}�g���b�N�X�̐ݒ�i���[���h���W�s��̐ݒ�j
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		Material = pMat[nCntMat].MatD3D;

		Material.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		Material.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&Material);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �����蔻�� (���E,��,��O)
//=============================================================================
bool CObjectX::Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize, bool bQuaternion)
{
	// �ϐ��錾
	bool bIsLanding = false;

	if (bQuaternion)
	{
		// ���f���̍��������蔻��(�N�H�[�^�j�I��Ver)
		if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
			(pPosOld->x + pSize->x / 2.0f <= m_pos.x + m_MinVtx.x) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->x = m_pos.x + m_MinVtx.x - (pSize->x / 2.0f);
		}
		// ���f���̉E�������蔻��(�N�H�[�^�j�I��Ver)
		if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
			(pPosOld->x - pSize->x / 2.0f >= m_pos.x + m_MaxVtx.x) &&
			(pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->x = m_pos.x + m_MaxVtx.x + (pSize->x / 2.0f);
		}
		// ���f���̉��������蔻��(�N�H�[�^�j�I��Ver)
		if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
			(pPosOld->z - pSize->z / 2.0f >= m_pos.z + m_MaxVtx.z) &&
			(pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->z = m_pos.z + m_MaxVtx.z + (pSize->z / 2.0f);
		}
		// ���f���̎�O�������蔻��(�N�H�[�^�j�I��Ver)
		if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
			(pPosOld->z + pSize->z / 2.0f <= m_pos.z + m_MinVtx.z) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->z = m_pos.z + m_MinVtx.z - (pSize->z / 2.0f);
		}
	}

	else
	{
		// ���f���̍��������蔻��
		if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
			(pPosOld->x + pSize->x / 2.0f <= m_pos.x + m_MinVtx.x / 2.0f) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x / 2.0f) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->x = m_pos.x + m_MinVtx.x / 2.0f - pSize->x / 2.0f;
		}
		// ���f���̉E�������蔻��
		if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
			(pPosOld->x - pSize->x / 2.0f >= m_pos.x + m_MaxVtx.x / 2.0f) &&
			(pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x / 2.0f) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->x = m_pos.x + m_MaxVtx.x / 2.0f + pSize->x / 2.0f;
		}
		// ���f���̉��������蔻��
		if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
			(pPosOld->z - pSize->z / 2.0f >= m_pos.z + m_MaxVtx.z / 2.0f) &&
			(pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z / 2.0f) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->z = m_pos.z + m_MaxVtx.z / 2.0f + pSize->z / 2.0f;
		}
		// ���f���̎�O�������蔻��
		if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
			(pPosOld->z + pSize->z / 2.0f <= m_pos.z + m_MinVtx.z / 2.0f) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z / 2.0f) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->z = m_pos.z + m_MinVtx.z / 2.0f - pSize->z / 2.0f;
		}
	}

	// �l��Ԃ�
	return bIsLanding;
}

//=============================================================================
// �����蔻�� (�㑤)
//=============================================================================
bool CObjectX::UpCollision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize, D3DXVECTOR3 * pMove, bool bQuaternion)
{
	// �ϐ��錾
	bool bIsLanding = false;

	if (bQuaternion)
	{
		// ���f���̏㑤�����蔻��(�N�H�[�^�j�I��Ver)
		if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
			(pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
			(pPos->y <= m_pos.y + m_MaxVtx.y + (pSize->y / 2.0f)))
		{
			bIsLanding = true;
			if (pPos->y == pPosOld->y)
			{
				pMove->y = 0.0f;
			}
			pPos->y = m_pos.y + m_MaxVtx.y + (pSize->y / 2.0f);
		}
	}

	else
	{
		// ���f���̏㑤�����蔻��
		if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
			(pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
			(pPos->y <= m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			if (pPos->y == pPosOld->y)
			{
				pMove->y = 0.0f;
			}
			pPos->y = m_pos.y + m_MaxVtx.y;
		}
	}

	// �l��Ԃ�
	return bIsLanding;
}
//=============================================================================
//�N�I�[�^�j�I���v�Z��
void CObjectX::QuaternionCalculation(float ModelDiameter/*���f���̒��a*/, D3DXVECTOR3 *move, D3DXQUATERNION *FstQuaternion /*�v�Z��*/)
{
	// �N�I�[�^�j�I��
	D3DXQUATERNION quaternion;

	D3DXVECTOR3 inverseVec = -*move / (ModelDiameter/*(���f���̒��a)*/ * 2);
	// move�l�𔽑΂ɂ���
	D3DXVECTOR3 vecY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�傫�����P��	
	D3DXVec3Normalize(&inverseVec, &inverseVec);

	// �O�ςŉ�]�����Z�o
	D3DXVec3Cross(&m_axis, &inverseVec, &vecY);
	D3DXVec3Normalize(&m_axis, &m_axis);

	float fLength = D3DXVec3Length(move);

	int Cnt = CPlayer::GetKeyCnt();

	float Length = fLength / Cnt;
	// �N�I�[�^�j�I���̌v�Z
	D3DXQuaternionRotationAxis(&quaternion, &m_axis, Length *0.3f);	// ��]���Ɖ�]�p�x���w��

	*FstQuaternion *= quaternion;

	// �N�I�[�^�j�I���̃m�[�}���C�Y
	D3DXQuaternionNormalize(FstQuaternion, FstQuaternion);
}



//=============================================================================
// ���_�ő�l�ݒ菈��
//=============================================================================
void CObjectX::SetMaxVtx(D3DXVECTOR3 Maxvtx)
{
	m_MaxVtx = Maxvtx;
}

//=============================================================================
// ���_�ŏ��l�ݒ菈��
//=============================================================================
void CObjectX::SetMinVtx(D3DXVECTOR3 Minvtx)
{
	m_MinVtx = Minvtx;
}
