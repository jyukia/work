#include "Meshline.h"
#include"application.h"
#include "renderer.h"
#include "object3D.h"
#include "player.h"
#include "game.h"
#include "game1.h"
#include "mode.h"
#include "movelife.h"
#include "input.h"
#include "camera.h"
#include "Item.h"
#include "ranking.h"

#include"DebugProc.h"

bool CMeshLine::bIsLanding = false;

CMeshLine::CMeshLine(int nPriority) :m_pVtxMax(0), m_col(0.0f, 0.0f, 0.0f, 0.0f), m_Vtxcount(0), bUseflg(false)
{

}

CMeshLine::~CMeshLine()
{
}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
void CMeshLine::LoadTexture(const char * aFileName)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		aFileName,
		&m_pTexture);
}

//������
HRESULT CMeshLine::Init()
{
	if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_TITLE)
	{
		m_pVtxMax = MaxLineTitle;	//���_���ő吔
	}
	else
	{//������
		m_pVtxMax = MaxLine;	//���_���ő吔
	}

	if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_GAME)
	{
		m_pos = D3DXVECTOR3(110.0f, 610.0f, -600.0f);
	}
	else if(CApplication::Getinstnce()->GetMode() == CApplication::MODE_GAME1)
	{
		m_pos = D3DXVECTOR3(2300.0f, 20.0f, -2900.0f);
	}
	else if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_TITLE)
	{
		m_pos = D3DXVECTOR3(1850.0f, 20.0f, -600.0f);
	}
	else if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_RANKING)
	{
		m_pos = D3DXVECTOR3(1100.0f, 610.0f, -2600.0f);
	}

	LoadTexture("Data/TEXTURE/kedama.png");

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D) * m_pVtxMax),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int X = 0;
	for (int Cnt = 0; Cnt < m_pVtxMax; Cnt++)
	{
		// ���_����ݒ�
		//pVtx[Cnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[Cnt].pos = m_pos;

		//�e���_�̖@���̐ݒ�i���x�N�g���̑傫����1�ɂ���K�v������j
		pVtx[Cnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[Cnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̍��W�ݒ�
		pVtx[Cnt].tex = D3DXVECTOR2(0.0f, 1.0f);


		float Y = (float)Cnt / 2;
		pVtx[Cnt].tex = D3DXVECTOR2((float)X, Y);
		X++;
		if (X >= 2)	//�e�N�X�`��
		{
			X = 0;
		}

	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

void CMeshLine::Uninit()
{
	//���_�o�b�t�@�̉���E�폜
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

void CMeshLine::Update()
{

	D3DXVECTOR3 axis = CObjectX::GetAxis();

	//�v���C���[���
	if (CApplication::Getinstnce()->GetpMode()->GetPlayer() != nullptr)
	{
		D3DXVECTOR3 pPlayerPos = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetPos();
		D3DXVECTOR3 pPlayerPosOld = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetPosOld();

		//���_���ւ̃|�C���^
		VERTEX_3D*pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		if (pPlayerPosOld != pPlayerPos && !(axis.x == 0 && axis.y == 0 && axis.z == 0))	//�����Ă�Ƃ����s
		{
			pVtx[m_Vtxcount + 2].pos = pPlayerPos + axis * 5.0f;			//�����ύX
			pVtx[m_Vtxcount + 1].pos = pPlayerPos - axis * 5.0f;			//���_
			m_Vtxcount += 2;
		}

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();

		//�ړ����~�߂�v�Z
		if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_TITLE)
		{
			if (m_Vtxcount >= 900)	//�ő�ړ��ʂɒB�����ꍇ	�v���C���[�̈ړ��𐧌�
			{
				CMode::GetPlayer()->SetbMoveFlg(false);
			}
		}
		else
		{
			int a = 0;
			if (m_Vtxcount >= 5000)	//�ő�ړ��ʂɒB�����ꍇ	�v���C���[�̈ړ��𐧌�
			{
				CMode::GetPlayer()->SetbMoveFlg(false);
			}
			else
			{
				CMode::GetPlayer()->SetbMoveFlg(true);
			}
		}


#ifdef _DEBUG
		CDebugProc::Print("�v���C���[�̐i�s����       (axis)       | X : %.2f | Y : %.2f | Z : %.2f |\n", axis.x, axis.y, axis.z);

		CDebugProc::Print("�v���C���[�̍��W       (pPlayerPos)       | X : %.2f | Y : %.2f | Z : %.2f |\n", pPlayerPos.x, pPlayerPos.y, pPlayerPos.z);

		CDebugProc::Print("m_Vtxcount       (m_Vtxcount)       %d\n", m_Vtxcount);

#endif // _DEBUG
	}
}

void CMeshLine::Draw()
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//���C�g�ݒ�false�ɂ���ƃ��C�g�ƐH���Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);				//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f); //�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);		//���[���h���W�s��̐ݒ�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_Vtxcount - 2/*m_pVtxMax - 2*/);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);

}
void CMeshLine::SetMtxParent(D3DXMATRIX * pMtx)
{
	m_pMtxParent = pMtx;
}

void CMeshLine::SetOfSetPos(D3DXVECTOR3 ofsetpos)
{
	OfSetPos = ofsetpos;
}

void CMeshLine::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

}

void CMeshLine::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

void CMeshLine::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

CMeshLine * CMeshLine::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 distancepos)
{
	CMeshLine *pMeshLine = new CMeshLine(2);

	if (pMeshLine != nullptr)
	{
		pMeshLine->Init();
		pMeshLine->SetOfSetPos(distancepos);
		pMeshLine->SetCol(col);
		pMeshLine->SetPos(pos);
	}
	else
	{
		assert(false);
	}

	return pMeshLine;
}
//�ю�����Q���ɐG�ꂽ�ېڐG�����ۂ���鏈��
bool CMeshLine::Collision(D3DXVECTOR3 * PlayerPos, D3DXVECTOR3 * PlayerSize)
{
	//���_���ւ̃|�C���^
	VERTEX_3D * pVtx = nullptr;
	//WORD * pIdx;
	D3DXVECTOR3 IdxPos[3];				//Idx��pos
	D3DXVECTOR3 VecA[3];				//VecA
	D3DXVECTOR3 VecB[3];				//VecB

	bool bIsLanding = false;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return bIsLanding;
}
//=============================================================================
// �����蔻�� �v���C���[���߂����ۖю��̉�����s��
//=============================================================================
bool CMeshLine::CollisionReturn(D3DXVECTOR3 * PlayerPos)
{
	const int LineDiameter = 2;

	const int nPolygon = 100;
	D3DXVECTOR3 VecA[nPolygon * 3];				//VecA
	D3DXVECTOR3 VecB[nPolygon * 3];				//VecB
	float Calculation2D[nPolygon * 3];			//2�����O�ς̌v�Z����
	const int vecCount = 3;
	//���_���ւ̃|�C���^
	VERTEX_3D * pVtx = nullptr;
	bIsLanding = false;

	//�X�P�[���Ή������T�C�Y���v�Z		�����蔻��g�p
	D3DXVECTOR3 Scale = CMode::GetPlayer()->GetScale();
	D3DXVECTOR3 Size = CMode::GetPlayer()->GetSize();
	{
		//�X�P�[���ƃT�C�Y
		Size.x = Scale.x * Size.x;
		Size.y = Scale.y * Size.y;
		Size.z = Scale.z * Size.z;
	}

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int count = 0; count < nPolygon; count++)
	{
		//�x�N�g���̎擾 VecA
		VecA[count * 3] = pVtx[3 + count].pos - pVtx[2 + count].pos;
		VecA[count * 3 + 1] = pVtx[4 + count].pos - pVtx[3 + count].pos;
		VecA[count * 3 + 2] = pVtx[2 + count].pos - pVtx[4 + count].pos;

		//�v���C���[���_�𑪂�
		VecB[count * 3] = *PlayerPos - pVtx[2 + count].pos;
		VecB[count * 3 + 1] = *PlayerPos - pVtx[3 + count].pos;
		VecB[count * 3 + 2] = *PlayerPos - pVtx[4 + count].pos;

		Calculation2D[count * 3] = Vec2Cross(&VecA[count * 3], &VecB[count * 3]);
		Calculation2D[count * 3 + 1] = Vec2Cross(&VecA[count * 3 + 1], &VecB[count * 3 + 1]);
		Calculation2D[count * 3 + 2] = Vec2Cross(&VecA[count * 3 + 2], &VecB[count * 3 + 2]);

		//�v���C���[�̈ʒu���S��-��+
		if ((Calculation2D[count * 3] > 0 && Calculation2D[count * 3 + 1] > 0 && Calculation2D[count * 3 + 2] > 0) || (Calculation2D[count * 3] < 0 && Calculation2D[count * 3 + 1] < 0 && Calculation2D[count * 3 + 2] < 0))
		{//����������
			for (int Cnt = 0; Cnt < m_pVtxMax - 3; Cnt++)
			{
				CMode::GetPlayer()->SetScaleType(CPlayer::TypeScaleUp);

				//�z������ւ��鎖�ŏ����Ă���
				pVtx[Cnt] = pVtx[Cnt + 2];
			}

			m_Vtxcount -= 2;

			//false��������
			bUseflg = false;
			bIsLanding = true;
		}
		else
		{//�������Ă��Ȃ��Ƃ�
			int a = 1;
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return bIsLanding;
}

//���S�����߂�
D3DXVECTOR3 CMeshLine::GetCenterVtx()
{
	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�^�񒆂����߂邽�ߍ쐬
	m_returnpos = pVtx[m_Vtxcount].pos + (pVtx[m_Vtxcount - 1].pos - pVtx[m_Vtxcount].pos) / 2;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

return  m_returnpos; } 

//=========================================
// 2D�x�N�g���̊O��
// Author: Yuda Kaito
//=========================================
float CMeshLine::Vec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	return v1->x * v2->z - v1->z * v2->x;
}

//=========================================
// 2D�x�N�g���̓���
// Author: hamada ryuuga
//=========================================
float CMeshLine::Vec2Dot(D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	return v1->x * v2->x + v1->z * v2->z;
}
