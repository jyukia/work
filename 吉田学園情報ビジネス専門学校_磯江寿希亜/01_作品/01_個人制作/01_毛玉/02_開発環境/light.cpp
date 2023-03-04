//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "light.h"
#include "application.h"
#include "renderer.h"

D3DLIGHT9 CLight::m_aLight[MAX_LIGHT];

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLight::CLight()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLight::~CLight()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLight::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir1;		//���C�g�̕����x�N�g��
	D3DXVECTOR3 vecDir2;		//���C�g�̕����x�N�g��
	D3DXVECTOR3 vecDir3;		//���C�g�̕����x�N�g��
	D3DXVECTOR3 vecDir4;		//���C�g�̕����x�N�g��
	D3DXVECTOR3 vecDir5;		//���C�g�̕����x�N�g��

	//���C�g���N���A����
	ZeroMemory(&m_aLight[0], sizeof(m_aLight));		//���\���̕ϐ����[���N���A�ł���֗��֐�(memset�Ɠ���)

	//���C�g�̎�ނ�ݒ�
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;		//���s����
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;		//���s����
	m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;		//���s����
	m_aLight[3].Type = D3DLIGHT_DIRECTIONAL;		//���s����
	m_aLight[4].Type = D3DLIGHT_DIRECTIONAL;		//���s����

	//���C�g�̊g�U����ݒ�
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//���C�g�̐F
	m_aLight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//���C�g�̐F
	m_aLight[2].Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);		//���C�g�̐F
	m_aLight[3].Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);		//���C�g�̐F
	m_aLight[4].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//���C�g�̐F

	//���C�g�̕�����ݒ�
	vecDir1 = D3DXVECTOR3(-1.0f, 0.5f, -0.5f);
	vecDir2 = D3DXVECTOR3(-0.3f, 0.8f, 0.4f);
	vecDir3 = D3DXVECTOR3(0.6f, -0.4f, -0.2f);
	vecDir4 = D3DXVECTOR3(-0.8f, 0.4f, 0.2f);
	vecDir5 = D3DXVECTOR3(0.0f, 0.4f, 0.4f);

	//���K������i�傫��1�̃x�N�g���ɂ���j
	D3DXVec3Normalize(&vecDir1, &vecDir1);		//���x�N�g����傫��1�̂���֗��֐�
	D3DXVec3Normalize(&vecDir2, &vecDir2);		//���x�N�g����傫��1�̂���֗��֐�
	D3DXVec3Normalize(&vecDir3, &vecDir3);		//���x�N�g����傫��1�̂���֗��֐�
	D3DXVec3Normalize(&vecDir4, &vecDir4);		//���x�N�g����傫��1�̂���֗��֐�
	D3DXVec3Normalize(&vecDir5, &vecDir5);		//���x�N�g����傫��1�̂���֗��֐�

	m_aLight[0].Direction = vecDir1;
	m_aLight[1].Direction = vecDir2;
	m_aLight[2].Direction = vecDir3;
	m_aLight[3].Direction = vecDir4;
	m_aLight[4].Direction = vecDir5;

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &m_aLight[0]);			//0�Ԗڂ̃��C�g��ݒ�E�L���ɂ���
	pDevice->SetLight(1, &m_aLight[1]);
	pDevice->SetLight(2, &m_aLight[2]);
	pDevice->SetLight(3, &m_aLight[3]);
	pDevice->SetLight(4, &m_aLight[4]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);
	pDevice->LightEnable(3, TRUE);
	pDevice->LightEnable(4, TRUE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLight::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CLight::Update(void)
{

}

//=============================================================================
// ��������
//=============================================================================
CLight *CLight::Create()
{
	//�|�C���^�錾
	CLight *pLight = nullptr;

	//�C���X�^���X����
	pLight = new CLight;

	if (pLight != nullptr)
	{//�|�C���^�����݂�������s
		pLight->Init();
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	//�|�C���^��Ԃ�
	return pLight;
}