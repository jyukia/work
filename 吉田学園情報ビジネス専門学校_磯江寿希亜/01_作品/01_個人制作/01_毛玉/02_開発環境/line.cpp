#include "Precompile.h"
#include "line.h"
#include "object3D.h"
#include "renderer.h"
#include "application.h"

CLine::CLine(int nPriority) :
	m_pos(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_move(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_size(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_rot(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_start(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_goal(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_col(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)),
	m_pVtxBuff(nullptr)
{
}

CLine::~CLine()
{
}

HRESULT CLine::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	return S_OK;
}

void CLine::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

void CLine::Update()
{
}

void CLine::Draw()
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX	mtxRot, mtxTrans, mtxView;		

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// ���e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Z�e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);

	// ���C�g�𖳌�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �����̔��f
	// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���C���`��
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);

	// ���C�g��L��	
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Z�e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

CLine * CLine::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 goal, D3DXCOLOR col, int nPriority)
{
	CLine * pLine = new CLine;

	if (FAILED(pLine->Init()))
	{
		return nullptr;
	}

	// �����o�ϐ��ɒl��ݒ�
	pLine->m_pos = pos;			// �ʒu
	pLine->m_rot = rot;			// �p�x
	pLine->m_start = start;		// �n�_
	pLine->m_goal = goal;		// �I�_
	pLine->m_col = col;			// �F

	// ���C���Z�b�g����
	pLine->SetLine();			

	// �|�C���^��Ԃ�
	return pLine;
}

void CLine::SetLine()
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(m_start.x, m_start.y, m_start.z);
	pVtx[1].pos = D3DXVECTOR3(m_goal.x, m_goal.y, m_goal.z);

	// ���_�J���[
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

void CLine::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CLine::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

void CLine::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

void CLine::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

void CLine::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
