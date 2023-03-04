#include "meshorbit.h"
#include"application.h"
#include "renderer.h"
#include "object3D.h"

CMeshOrbit::CMeshOrbit(int nPriority):m_pVtxMax(0), m_col(0.0f,0.0f,0.0f,0.0f)
{
}
CMeshOrbit::~CMeshOrbit()
{
}

HRESULT CMeshOrbit::Init()
{
	{//������
		m_pVtxMax = 100;	//���_���ő吔
	}

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

	for (int Cnt = 0; Cnt < m_pVtxMax ; Cnt ++)
	{
		// ���_����ݒ�
		pVtx[Cnt].pos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		//�e���_�̖@���̐ݒ�i���x�N�g���̑傫����1�ɂ���K�v������j
		pVtx[Cnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[Cnt].col = D3DXCOLOR(m_col);

		//�e�N�X�`���̍��W�ݒ�
		pVtx[Cnt].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

void CMeshOrbit::Uninit()
{
	//���_�o�b�t�@�̉���E�폜
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

void CMeshOrbit::Update()
{
	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int Cnt = m_pVtxMax -3; Cnt >= 0; Cnt--)
	{
		pVtx[Cnt+2].pos = pVtx[Cnt].pos;
	}
	D3DXVECTOR3 OfSetPos(0.0f,100.0f,0.0f);	//	�c���W�̕ϊ� �T�C�Y�ύX�\
	D3DXVec3TransformCoord(&OfSetPos, &OfSetPos, m_pMtxParent);
	D3DXVECTOR3 Pos(0.0f,0.0f,0.0f);	//���_
	D3DXVec3TransformCoord(&Pos, &Pos, m_pMtxParent);

	pVtx[1].pos = OfSetPos;	//�����ύX
	pVtx[0].pos = Pos;//���_

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

void CMeshOrbit::Draw()
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
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z); //�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)

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
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_pVtxMax - 2);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

void CMeshOrbit::SetMtxParent(D3DXMATRIX * pMtx)
{
	m_pMtxParent = pMtx;
}

void CMeshOrbit::SetOfSetPos(D3DXVECTOR3 ofsetpos)
{
	OfSetPos = ofsetpos;
}

void CMeshOrbit::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CMeshOrbit::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

void CMeshOrbit::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

CMeshOrbit * CMeshOrbit::Create(D3DXCOLOR col)
{
	CMeshOrbit *pMesh = new CMeshOrbit(3);

	if (pMesh != nullptr)
	{
		pMesh->SetCol(col);
		pMesh->Init();
	}
	else
	{
		assert(false);
	}

	return pMesh;
}
