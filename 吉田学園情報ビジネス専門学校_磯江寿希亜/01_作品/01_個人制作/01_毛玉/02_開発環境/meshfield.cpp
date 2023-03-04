//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "meshfield.h"
#include "object3D.h"
#include "renderer.h"
#include "application.h"
#include "main.h"
#include "game.h"
#include "player.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeshfield::CMeshfield(int nPriority) :
	CObject(nPriority),
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_fLength(0.0f),
	m_fAngle(0.0f),
	m_fRotMove(5.0f),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f))
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshfield::~CMeshfield()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshfield::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	//LoadTexture("Data\\TEXTURE\\wood.png");

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEXNUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//���_���W�ւ̃|�C���^
	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHFIELD_X_BLOCK + 1; nCntX++)
		{
			//m_RandHeight = (float)(rand() % 30 + 1);
			m_RandHeight = sinf(nCntX * 0.5f) * 120;

			//���_���W�̐ݒ�
			pVtx[nCntX + (nCntZ * (MESHFIELD_X_BLOCK + 1))].pos = D3DXVECTOR3(-POLYGON_WIDTH + (POLYGON_WIDTH * nCntX), 0.0f, POLYGON_DEPTH - (POLYGON_DEPTH * nCntZ));

			//�e���_�̖@���̐ݒ�
			pVtx[nCntX + (nCntZ * (MESHFIELD_X_BLOCK + 1))].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[nCntX + (nCntZ * (MESHFIELD_X_BLOCK + 1))].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[nCntX + (nCntZ * (MESHFIELD_X_BLOCK + 1))].tex = D3DXVECTOR2((float)nCntX, (float)nCntZ);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD * pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X�̐ݒ�
	for (int nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHFIELD_X_BLOCK + 1; nCntX++)
		{
			pIdx[0] = (MESHFIELD_X_BLOCK + 1) + nCntX + nCntZ * (MESHFIELD_X_BLOCK + 1);
			pIdx[1] = (MESHFIELD_X_BLOCK + 1) + nCntX + nCntZ * (MESHFIELD_X_BLOCK + 1) - (MESHFIELD_X_BLOCK + 1);

			pIdx += 2;
		}

		//�k�ރ|���S��
		if (nCntZ != MESHFIELD_Z_BLOCK)
		{
			pIdx[0] = (MESHFIELD_X_BLOCK + 1) * nCntZ + MESHFIELD_X_BLOCK;
			pIdx[1] = (MESHFIELD_X_BLOCK + 1) * (nCntZ + 2);

			pIdx += 2;
		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	D3DXVECTOR3 IdxPosNor[3];				//Idx��pos
	D3DXVECTOR3 Calculation3DNor[2];		//3�����O�ς̌v�Z����
	D3DXVECTOR3 VecAnswer;					//�O�ς̌v�Z����
	D3DXVECTOR3 SaveVtxNor[MESHFIELD_VERTEX_NUM];

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < MESHFIELD_PRIMITIVE_NUM - 2; nCnt++)
	{
		//Idx��pos
		IdxPosNor[0] = pVtx[pIdx[nCnt]].pos;
		IdxPosNor[1] = pVtx[pIdx[nCnt + 1]].pos;
		IdxPosNor[2] = pVtx[pIdx[nCnt + 2]].pos;

		//�k�ރ|���S���̏ꍇ���s
		if (pIdx[nCnt] == pIdx[nCnt + 1] || pIdx[nCnt + 1] == pIdx[nCnt + 2] || pIdx[nCnt + 2] == pIdx[nCnt])
		{
			continue;
		}

		//3�����O�ς̌v�Z
		Calculation3DNor[0] = IdxPosNor[1] - IdxPosNor[0];
		Calculation3DNor[1] = IdxPosNor[2] - IdxPosNor[0];
		D3DXVec3Cross(&VecAnswer, &Calculation3DNor[0], &Calculation3DNor[1]);

		if (nCnt % 2 == 0)
		{
			VecAnswer *= -1;
		}

		//���K��
		D3DXVec3Normalize(&VecAnswer, &VecAnswer);

		//�ۑ��p�z��ɖ@���x�N�g����ۑ�
		SaveVtxNor[pIdx[nCnt]] += VecAnswer;
		SaveVtxNor[pIdx[nCnt + 1]] += VecAnswer;
		SaveVtxNor[pIdx[nCnt + 2]] += VecAnswer;

		//���K��
		D3DXVec3Normalize(&SaveVtxNor[pIdx[nCnt]], &SaveVtxNor[pIdx[nCnt]]);
		D3DXVec3Normalize(&SaveVtxNor[pIdx[nCnt + 1]], &SaveVtxNor[pIdx[nCnt + 1]]);
		D3DXVec3Normalize(&SaveVtxNor[pIdx[nCnt + 2]], &SaveVtxNor[pIdx[nCnt + 2]]);

		pVtx[pIdx[nCnt]].nor = SaveVtxNor[pIdx[nCnt]];
		pVtx[pIdx[nCnt + 1]].nor = SaveVtxNor[pIdx[nCnt + 1]];
		pVtx[pIdx[nCnt + 2]].nor = SaveVtxNor[pIdx[nCnt + 2]];
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshfield::Uninit()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̉��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	//�C���X�^���X�̉������
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshfield::Update()
{
	//m_fRotMove += 0.1f;

	//if (m_fRotMove >= D3DX_PI)
	//{// �ړ������̐��K��
	//	m_fRotMove -= D3DX_PI * 2;
	//}
	//else if (m_fRotMove <= -D3DX_PI)
	//{// �ړ������̐��K��
	//	m_fRotMove += D3DX_PI * 2;
	//}

	////�����X�V
	//m_pos.y += sinf(m_fRotMove) * 4.0f;

	////���W�ݒ�
	//SetPos(m_pos);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshfield::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorldMeshField);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldMeshField);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//���b�V���t�B�[���h�̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIELD_VERTEX_NUM, 0, MESHFIELD_PRIMITIVE_NUM);

	//�|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 12);

	//�e�N�X�`���̐ݒ�	(�e�N�X�`�������f���ɂ��Ԃ�Ȃ��悤�ɂ���)
	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// ���_���W�X�V����
//=============================================================================
void CMeshfield::VtxUpdate()
{
	if (m_pVtxBuff != nullptr)
	{
		//���_���ւ̃|�C���^
		VERTEX_3D*pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̍X�V
		pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, m_size.z);
		pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, m_size.z);
		pVtx[2].pos = D3DXVECTOR3(-m_size.x, m_size.y, -m_size.z);
		pVtx[3].pos = D3DXVECTOR3(m_size.x, m_size.y, -m_size.z);

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
// ���W�ݒ菈��
//=============================================================================
void CMeshfield::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �T�C�Y�ݒ菈��
//=============================================================================
void CMeshfield::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// �ړ��ʐݒ菈��
//=============================================================================
void CMeshfield::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// �J���[�ݒ菈��
//=============================================================================
void CMeshfield::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// �����ݒ菈��
//=============================================================================
void CMeshfield::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �h���̃e�N�X�`���|�C���^��e�̃e�N�X�`���|�C���^�ɑ�����鏈��
//=============================================================================
void CMeshfield::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;		//�e�N�X�`���̃|�C���^
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
void CMeshfield::LoadTexture(const char * aFileName)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		aFileName,
		&m_pTexture);
}

//=============================================================================
// �e�N�X�`�����W�ݒ菈��
//=============================================================================
void CMeshfield::SetUV(float x_1, float x_2, float y_1, float y_2)
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
CMeshfield * CMeshfield::Create(const D3DXVECTOR3 pos, int nPriority)
{
	//�|�C���^�錾
	CMeshfield *pMeshfield = nullptr;

	//�C���X�^���X����
	pMeshfield = new CMeshfield(nPriority);

	if (pMeshfield != nullptr)
	{//�|�C���^�����݂�������s
		pMeshfield->SetPos(pos);
		pMeshfield->SetSize(D3DXVECTOR3(100.0f, 0.0f, 100.0f));
		pMeshfield->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pMeshfield->Init();
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	//�|�C���^��Ԃ�
	return pMeshfield;
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CMeshfield::Collision(D3DXVECTOR3 *PlayerPos, D3DXVECTOR3 *PlayerSize, bool bQuaternion)
{
	//���_���ւ̃|�C���^
	VERTEX_3D * pVtx = nullptr;
	WORD * pIdx;
	D3DXVECTOR3 IdxPos[3];				//Idx��pos
	D3DXVECTOR3 VecA[3];				//VecA
	D3DXVECTOR3 VecB[3];				//VecB
	D3DXVECTOR3 Calculation3D[2];		//3�����O�ς̌v�Z����
	float Calculation2D[3];				//2�����O�ς̌v�Z����
	D3DXVECTOR3 Answer;					//�O�ς̌v�Z����
	bool bIsLanding = false;

	CPlayer * pPlayer = CGame::GetPlayer();

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < MESHFIELD_PRIMITIVE_NUM; nCnt++)
	{
		//Idx��pos
		IdxPos[0] = pVtx[pIdx[nCnt]].pos;
		IdxPos[1] = pVtx[pIdx[nCnt + 1]].pos;
		IdxPos[2] = pVtx[pIdx[nCnt + 2]].pos;

		//VecA
		VecA[0] = IdxPos[1] - IdxPos[0];
		VecA[1] = IdxPos[2] - IdxPos[1];
		VecA[2] = IdxPos[0] - IdxPos[2];

		//VecB
		VecB[0] = *PlayerPos - (IdxPos[0] + m_pos);
		VecB[1] = *PlayerPos - (IdxPos[1] + m_pos);
		VecB[2] = *PlayerPos - (IdxPos[2] + m_pos);

		//2�����O�ς̌v�Z����
		Calculation2D[0] = VecA[0].x * VecB[0].z - VecB[0].x * VecA[0].z;
		Calculation2D[1] = VecA[1].x * VecB[1].z - VecB[1].x * VecA[1].z;
		Calculation2D[2] = VecA[2].x * VecB[2].z - VecB[2].x * VecA[2].z;

		//�v���C���[�̈ʒu���S��-��+
		if ((Calculation2D[0] >= 0 && Calculation2D[1] >= 0 && Calculation2D[2] >= 0) || (Calculation2D[0] <= 0 && Calculation2D[1] <= 0 && Calculation2D[2] <= 0))
		{
			//3�����O�ς̌v�Z
			Calculation3D[0] = IdxPos[1] - IdxPos[0];
			Calculation3D[1] = IdxPos[2] - IdxPos[0];
			D3DXVec3Cross(&Answer, &Calculation3D[0], &Calculation3D[1]);

			//���K��
			D3DXVec3Normalize(&Answer, &Answer);

			//if (PlayerPos->y <= posLineVec[0].y - (Normal.x*(PlayerPos->x - posLineVec[0].x) + Normal.z*(PlayerPos->z - posLineVec[0].z)) / Normal.y)
			//{
			//	//CGame::GetStage()->GetPlayer()->SetMove(D3DXVECTOR3(CGame::GetStage()->GetPlayer()->GetMove().x, 0.0f, CGame::GetStage()->GetPlayer()->GetMove().z));
			//	PlayerPos->y = (posLineVec[0].y - (Normal.x*(PlayerPos->x - posLineVec[0].x) + Normal.z*(PlayerPos->z - posLineVec[0].z)) / Normal.y) - 0.001f;
			//}

			if (bQuaternion)
			{
				//���ς̌v�Z
				PlayerPos->y = (IdxPos[0].y + m_pos.y) - ((PlayerPos->x - (IdxPos[0].x + m_pos.x)) * Answer.x + (PlayerPos->z - (IdxPos[0].z + m_pos.z)) * Answer.z) / Answer.y + PlayerSize->y / 2.0f;

				//���ς̌v�Z���ʕۑ�
				m_AnswerKeep = (IdxPos[0].y + m_pos.y) - ((PlayerPos->x - (IdxPos[0].x + m_pos.x)) * Answer.x + (PlayerPos->z - (IdxPos[0].z + m_pos.z)) * Answer.z) / Answer.y + PlayerSize->y / 2.0f;
			}
			else
			{
				//���ς̌v�Z
				PlayerPos->y = (IdxPos[0].y + m_pos.y) - ((PlayerPos->x - (IdxPos[0].x + m_pos.x)) * Answer.x + (PlayerPos->z - (IdxPos[0].z + m_pos.z)) * Answer.z) / Answer.y;

				//���ς̌v�Z���ʕۑ�
				m_AnswerKeep = (IdxPos[0].y + m_pos.y) - ((PlayerPos->x - (IdxPos[0].x + m_pos.x)) * Answer.x + (PlayerPos->z - (IdxPos[0].z + m_pos.z)) * Answer.z) / Answer.y;
			}

			bIsLanding = true;
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return bIsLanding;
}
