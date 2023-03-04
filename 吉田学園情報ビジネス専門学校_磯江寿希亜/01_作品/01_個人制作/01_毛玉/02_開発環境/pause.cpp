//=============================================================================
// Author : ��]����
//
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "pause.h"
#include"input.h"
#include "renderer.h"
#include"application.h"
#include"object2D.h"
#include "inputjoypad.h"
#include "fade.h"

LPDIRECT3DTEXTURE9 CPause::m_pTexture = {};

bool CPause::PauseFlg;

//�R���X�g���N�^   CObject::PRIORITY_LEVEL3
CPause::CPause(int nPriority) :m_modecount(0)
{
}
//�f�X�g���N�^
CPause::~CPause()
{}
//-----------------------------------------
//������
//-----------------------------------------
HRESULT CPause::Init()
{
	m_modecount = 1;

	BindTexture("INIESUTA");

	//�v���C���[���͑I��
	m_pGame = CObject2D::Create("PAUSE", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (int)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), PRIORITY_LEVEL4);
	m_pGame->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	CObject2D::Init();
	return S_OK;
}
//-----------------------------------------
//�I��
//-----------------------------------------
void CPause::Uninit()
{
	CObject2D::Uninit();
}
//-----------------------------------------
//�X�V
//-----------------------------------------
void CPause::Update()
{
	// �L�[�{�[�h�̏��擾
	CInput *pInputKeyboard = CApplication::Getinstnce()->GetInput();
	//�R���g���[���[
	CInputJoyPad *pJoy = CApplication::GetJoy();

	if (pInputKeyboard->Trigger(DIK_P) || pJoy->GetTrigger(DirectJoypad::JOYPAD_START, 0))
	{
		if (PauseFlg)
		{
			m_pGame->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

			PauseFlg = false;
		}
		else
		{
			m_pGame->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

			PauseFlg = true;
		}
	}

	CObject2D::Update();
}
//-----------------------------------------
//�`��
//-----------------------------------------
void CPause::Draw()
{
	CObject2D::Draw();
}
//-----------------------------------------
//�z�u�ݒ�
//-----------------------------------------
void CPause::SetObject(D3DXVECTOR3 Pos)
{
	SetPos(Pos);
}
CPause * CPause::Create(const char *aFileName, D3DXVECTOR3 size,D3DXVECTOR3 pos,int nPriority)
{
	CPause* pPause = nullptr;

	//���I�m��
	pPause = new CPause(nPriority);

	//NULL�`�F�b�N
	if (pPause != nullptr)
	{
		//������
		pPause->Init();
		pPause->BindTexture(aFileName);
		pPause->SetSize(size);

		//�Z�b�g
		pPause->SetObject(pos);
	}
	else
	{//�������~�߂�
		assert(false);
	}

	return pPause;
}
//-----------------------------------------
//Tex�̓ǂݍ��݁@1�P���̂�����Ă���̂ł�����ꊇ�ŊǗ����y������	Unload�����l
//-----------------------------------------
HRESULT CPause::Load()
{
	//������
	m_pTexture = nullptr;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Tex/Map/pause.png",
		&m_pTexture);

	return S_OK;
}
//-----------------------------------------
//�e�N�X�`���̔j��
//-----------------------------------------
void CPause::Unload()
{
	//�e�N�X�`���j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}
