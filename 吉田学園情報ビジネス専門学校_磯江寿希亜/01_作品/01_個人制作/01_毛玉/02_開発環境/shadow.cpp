//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "application.h"
#include "renderer.h"
#include "shadow.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShadow::CShadow(int nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShadow::~CShadow()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CShadow::Init(void)
{
	CObject3D::Init();

	//�e�N�X�`���̓ǂݍ���
	LoadTexture("Data\\TEXTURE\\shadow000.jpg");

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CShadow::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CShadow::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CShadow::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D::Draw();

	//���Z���������ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// ��������
//=============================================================================
CShadow *CShadow::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, int nPriority)
{
	//�|�C���^�錾
	CShadow *pShadow = nullptr;

	pShadow = new CShadow(nPriority);

	if (pShadow != nullptr)
	{
		pShadow->Init();
		pShadow->SetPos(pos);
		pShadow->SetSize(size);
	}

	return pShadow;
}