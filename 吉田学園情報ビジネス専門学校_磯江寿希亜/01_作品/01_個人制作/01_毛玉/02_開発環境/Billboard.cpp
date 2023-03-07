//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "billboard.h"
#include "object3D.h"
#include "renderer.h"
#include "application.h"
#include "main.h"
#include "texture.h"
#include"mode.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBillboard::CBillboard(int nPriority) :
	CObject(nPriority),
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_PatternAnimX(1),
	m_PatternAnimY(1),
	m_fLength(0.0f),
	m_fAngle(0.0f),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f)),
	m_blend(BLEND_NONE)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBillboard::~CBillboard()
{
}

//=============================================================================
// �I�u�W�F�N�g�̏�����
//=============================================================================
HRESULT CBillboard::Init()
{
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
void CBillboard::Uninit()
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
void CBillboard::Update()
{
	m_pos += m_move;

	//���_���W�X�V����
	VtxUpdate();

	if (m_bAnimation)
	{// �e�N�X�`���A�j���[�V����������ꍇ
		m_CntTime++;

		if (m_CntTime >= m_Timer)
		{
			m_AnimationSpdCnt++;
			if (m_AnimationSpdCnt >= m_AnimationSpeed)
			{
				m_AnimationSpdCnt = 0;
				m_PatternAnimX++;

				if (m_PatternAnimX > m_DivisionX)
				{//�A�j���[�V����
					m_PatternAnimX = 0;
					m_PatternAnimY++;
					if (m_PatternAnimY >= m_DivisionY)
					{
						m_PatternAnimY = 0;
						if (!m_bLoop)
						{
							Uninit();
						}
						return;
					}
				}

				float U = 1.0f / (m_DivisionX);
				float V = 1.0f / (m_DivisionY);

				SetUV(U * (m_PatternAnimX)
					, U *(m_PatternAnimX)+U
					, V * (m_PatternAnimY)
					, V * (m_PatternAnimY)+V);
			}
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�̕`��
//=============================================================================
void CBillboard::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans, mtxRot, mtxView;

	switch (m_blend)
	{
	case BLEND_ADDITIVE:
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	case BLEND_SUBSTRUCT:
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	default:
		break;
	}

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);		//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�J�����̋t�s���ݒ�
	if (m_bIsRotate)
	{
		m_mtxWorld._11 = mtxView._11;
		m_mtxWorld._12 = mtxView._21;
		m_mtxWorld._13 = mtxView._31;
		m_mtxWorld._31 = mtxView._13;
		m_mtxWorld._32 = mtxView._23;
		m_mtxWorld._33 = mtxView._33;
	}
	else
	{
		m_mtxWorld._11 = mtxView._11;
		m_mtxWorld._12 = mtxView._21;
		m_mtxWorld._13 = mtxView._31;
		m_mtxWorld._21 = mtxView._12;
		m_mtxWorld._22 = mtxView._22;
		m_mtxWorld._23 = mtxView._32;
		m_mtxWorld._31 = mtxView._13;
		m_mtxWorld._32 = mtxView._23;
		m_mtxWorld._33 = mtxView._33;
	}

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	//�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�J�������猩�ċ߂��������㏑��
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

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

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Z�o�b�t�@�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);

}

//=============================================================================
// ���_���W�X�V����
//=============================================================================
void CBillboard::VtxUpdate()
{
	if (m_pVtxBuff != nullptr)
	{
		//���_���ւ̃|�C���^
		VERTEX_3D*pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̍X�V
		pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_size.x, -m_size.y, 0.0f);

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
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	VtxUpdate();
}

//=============================================================================
// �h���̃e�N�X�`���|�C���^��e�̃e�N�X�`���|�C���^�ɑ�����鏈��
//=============================================================================
void CBillboard::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::Getinstnce()->GetTexture()->GetTexture(inPath);		//�e�N�X�`���̃|�C���^
}

//=============================================================================
// �e�N�X�`�����W�X�V����
//=============================================================================
void CBillboard::SetUV(float x_1, float x_2, float y_1, float y_2)
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
// Animation�̖����ݒ�֐�
//=============================================================================
void CBillboard::SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop)
{
	m_DivisionX = U;
	m_DivisionY = V;
	m_DivisionMAX = m_DivisionY*m_DivisionX;

	m_PatternAnimX = 1;
	m_PatternAnimY = 1;
	m_AnimationSpeed = Speed;
	m_Timer = Drawtimer;
	m_bAnimation = true;
	m_bLoop = loop;

	//�\�����W���X�V
	SetUV(1.0f / m_DivisionX * (m_PatternAnimX / (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnimX / (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY));
}

//=============================================================================
// �A�j���[�V�������w��̃^�C�~���O�Ŏ~�߂鏈��
//=============================================================================
void CBillboard::SetStopAnim(const int X, const int Y)
{
	m_bAnimation = false;

	m_PatternAnimX = X;
	m_PatternAnimY = Y;

	float U = 1.0f / (m_DivisionX);
	float V = 1.0f / (m_DivisionY);

	SetUV(U * (m_PatternAnimX)
		, U *(m_PatternAnimX)+U
		, V * (m_PatternAnimY)
		, V * (m_PatternAnimY)+V);
}

//=============================================================================
// �e�N�X�`���̔��]����
//=============================================================================
void CBillboard::SetFlip(EFlip flip)
{
	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍X�V
	switch (flip)
	{
	case FLIP_VERTICAL:
		pVtx[0].tex.y = -pVtx[0].tex.y;
		pVtx[1].tex.y = -pVtx[1].tex.y;
		pVtx[2].tex.y = -pVtx[2].tex.y;
		pVtx[3].tex.y = -pVtx[3].tex.y;
		break;

	case FLIP_HORIZON:
		pVtx[0].tex.x = -pVtx[0].tex.x;
		pVtx[1].tex.x = -pVtx[1].tex.x;
		pVtx[2].tex.x = -pVtx[2].tex.x;
		pVtx[3].tex.x = -pVtx[3].tex.x;
		break;

	default:
		pVtx[0].tex = -pVtx[0].tex;
		pVtx[1].tex = -pVtx[1].tex;
		pVtx[2].tex = -pVtx[2].tex;
		pVtx[3].tex = -pVtx[3].tex;
		break;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ��������
//=============================================================================
CBillboard * CBillboard::Create(std::string inPath,D3DXVECTOR3 pos, int nPriority)
{
	//�|�C���^�錾
	CBillboard *pBillboard = nullptr;

	//�C���X�^���X����
	pBillboard = new CBillboard(nPriority);

	if (pBillboard != nullptr)
	{//�|�C���^�����݂�������s
		pBillboard->BindTexture(inPath);
		pBillboard->SetPos(pos);
		pBillboard->SetSize(D3DXVECTOR3(55.0f, 55.0f, 0.0f));
		pBillboard->Init();
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	//�|�C���^��Ԃ�
	return pBillboard;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
void CBillboard::LoadTexture(const char * aFileName)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		aFileName,
		&m_pTexture);
}
