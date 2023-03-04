//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "object2D.h"
#include "renderer.h"
#include "application.h"
#include "main.h"
#include "texture.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject2D::CObject2D(int nPriority) :
	CObject(nPriority),
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_nTime(0),
	m_fLength(0.0f),
	m_fAngle(0.0f),
	m_fSquareSize(10.0f),
	m_bRotate(false),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject2D::~CObject2D()
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
HRESULT CObject2D::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer((sizeof(VERTEX_2D) * 4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒����Z�o
	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y)));

	//�p�x�̎Z�o
	m_fAngle = atan2f(m_size.x, m_size.y);

	// ���_����ݒ�
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
void CObject2D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�C���X�^���X�̉������
	Release();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V
//=============================================================================
void CObject2D::Update()
{
	//�ʒu�X�V
	m_pos += m_move;

	//���_���W�X�V����
	VtxUpdate();

	if (m_bRotate)
	{
		m_nTime++;

		D3DXVECTOR3 addPos[4];
		D3DXMATRIX mtx;    // �v�Z�p�}�g���b�N�X

		VERTEX_2D*pVtx;        //���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �}�g���b�N�X�̐���
		D3DXMatrixIdentity(&mtx);

		// ���[�A�s�b�`�A���[�����w�肵�ă}�g���b�N�X���쐬
		D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, ((D3DX_PI * 1.5f) / 50.0f) * m_nTime);

		// ���_���W
		for (int i = 0; i < 4; ++i)
		{
			D3DXVec3TransformCoord(&addPos[i], &sVtx[i], &mtx);
			pVtx[i].pos = m_pos + addPos[i] * (m_fSquareSize);
		}

		//���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// �I�u�W�F�N�g�̕`��
//=============================================================================
void CObject2D::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);

	//�A���t�@�e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// ���_���W�X�V����
//=============================================================================
void CObject2D::VtxUpdate()
{
	if (m_pVtxBuff != nullptr)
	{
		//���_���ւ̃|�C���^
		VERTEX_2D*pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�Ίp���̒����Z�o
		m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y))) / 2;

		//�p�x�̎Z�o
		m_fAngle = atan2f(m_size.x, m_size.y);

		//���_���W�̍X�V
		pVtx[0].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[0].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[1].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[2].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[3].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[3].pos.z = 0.0f;

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
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	VtxUpdate();
}

//=============================================================================
// �T�C�Y�ݒ�֐�
//=============================================================================
void CObject2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// �ړ��͐ݒ�֐�
//=============================================================================
void CObject2D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// �F�ݒ�֐�
//=============================================================================
void CObject2D::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// �����ݒ�֐�
//=============================================================================
void CObject2D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �h���̃e�N�X�`���|�C���^��e�̃e�N�X�`���|�C���^�ɑ�����鏈��
//=============================================================================
void CObject2D::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::Getinstnce()->GetTexture()->GetTexture(inPath);		//�e�N�X�`���̃|�C���^
}

//=============================================================================
// �e�N�X�`�����W�X�V����
//=============================================================================
void CObject2D::SetUV(float x_1, float x_2, float y_1, float y_2)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

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
// ���W�X�V����
//=============================================================================
void CObject2D::SetPosUV(float x_1, float x_2, float y_1, float y_2, float x_width1, float x_width2)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(x_1, y_1,0.f);
	pVtx[1].pos = D3DXVECTOR3(x_2, y_1,0.f);
	pVtx[2].pos = D3DXVECTOR3(x_width1, y_2,0.f);
	pVtx[3].pos = D3DXVECTOR3(x_width2, y_2,0.f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//---------------------------------------------------------------------------
//�X�R�A�g�p
//---------------------------------------------------------------------------
void CObject2D::ScoreVtx(float fstposX, float fstposY, float secdposX, float secdposY)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(fstposX, fstposY);
	pVtx[1].tex = D3DXVECTOR2(secdposX, fstposY);
	pVtx[2].tex = D3DXVECTOR2(fstposX, secdposY);
	pVtx[3].tex = D3DXVECTOR2(secdposX, secdposY);

	//���_���A�����b�N����
	m_pVtxBuff->Unlock();
}

//---------------------------------------------------------------------------
// �A�j���[�V�������_�ݒ�
//---------------------------------------------------------------------------
void CObject2D::AnimVtx(int nummax, int PtternAnim)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�\�����W���X�V
	pVtx[0].tex = D3DXVECTOR2((1.0f / nummax)*PtternAnim, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / nummax)*(PtternAnim + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / nummax)*PtternAnim, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / nummax)*(PtternAnim + 1), 1.0f);

	//���_���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// ��������
//=============================================================================
CObject2D * CObject2D::Create(const char *aFileName, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriority)
{
	//�|�C���^�錾
	CObject2D *pObject2D = nullptr;

	//�C���X�^���X����
	pObject2D = new CObject2D(nPriority);

	if (pObject2D != nullptr)
	{//�|�C���^�����݂�������s
		pObject2D->BindTexture(aFileName);
		pObject2D->SetPos(pos);
		pObject2D->SetSize(size);
		pObject2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pObject2D->Init();
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	//�|�C���^��Ԃ�
	return pObject2D;
}
