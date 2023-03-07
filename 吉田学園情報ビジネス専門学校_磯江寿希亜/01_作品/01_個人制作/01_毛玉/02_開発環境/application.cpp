//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "application.h"
#include "renderer.h"
#include "object.h"
#include "input.h"
#include "camera.h"
#include "Mapcamera.h"

#include "light.h"
#include "texture.h"
#include "title.h"

#include "game.h"
#include "game1.h"

#include "ranking.h"
#include "tutorial.h"
#include "fade.h"
#include "objectX_group.h"
#include "sound.h"
#include"DebugProc.h"
#include"SelectStage.h"
#include "inputjoypad.h"

//#include"stage_imgui.h"

//�g���ňړ����x�𗎂Ƃ��M�~�b�N�ǉ�
//�Q�ڂ̃}�b�v������ړ��A���̒ǉ��͂˂��Ĉړ��x�N�g���ύX

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CApplication *CApplication::m_pApplication = nullptr;
CInputJoyPad *CApplication::m_pJoy = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CApplication::CApplication():m_pRenderer(nullptr), m_pInput(nullptr), m_pMode(nullptr), m_pCamera(nullptr), m_pTexture(nullptr), m_pObjectXGroup(nullptr), m_pSound(nullptr), m_pDebugProc(nullptr), m_Item(nullptr)//, m_Imgui(nullptr)
{
	CApplication::m_mode = MODE_TITLE;//MODE_RANKING
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CApplication::~CApplication()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	Hwnd = hWnd;

	//�����̏�����
	srand((unsigned int)time(0));

	//�����_�����O�N���X�̐���
	m_pRenderer = new CRenderer;
	//�����_�����O�̏���������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{ //���������������s�����ꍇ
		return -1;
	}
	//�C���v�b�g�N���X�̐���
	m_pInput = CInput::Create();
	//�C���v�b�g�̏���������
	if (FAILED(m_pInput->Init(hInstance, hWnd)))
	{ //���������������s�����ꍇ
		return -1;
	}
	m_pJoy = new CInputJoyPad;
	if (FAILED(m_pJoy->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	m_pDebugProc = new CDebugProc;
	// ������
	assert(m_pDebugProc != nullptr);
	m_pDebugProc->Init();

	LPDIRECT3DDEVICE9 pDevice = m_pRenderer->GetDevice();
	//m_Imgui = new CStageImgui;
	//// ������
	//assert(m_Imgui != nullptr);
	//m_Imgui->Init(hWnd, pDevice);

	// �J�����̏�����
	m_pCamera = new CCamera;
	assert(m_pCamera != nullptr);

	// �e�N�X�`���̐���
	m_pTexture = new CTexture;
	assert(m_pTexture != nullptr);
	m_pTexture->LoadAll();

	// ���f���̐���
	m_pObjectXGroup = new CObjectXGroup;
	assert(m_pObjectXGroup != nullptr);
	m_pObjectXGroup->LoadAll();

	// �T�E���h�̐���
	m_pSound = new CSound;
	assert(m_pSound != nullptr);
	m_pSound->Init(hWnd);

	//���[�h����
	CFade::Create(m_mode);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CApplication::Uninit(void)
{

	// �e�N�X�`���̍폜
	if (m_pTexture != nullptr)
	{
		m_pTexture->UnloadAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}
	//�f�o�b�N�\��
	if (m_pDebugProc != nullptr)
	{// �I������
		m_pDebugProc->Uninit();

		// �������̉��
		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}
	// �T�E���h�̍폜
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
	// X���f���̍폜
	if (m_pObjectXGroup != nullptr)
	{
		m_pObjectXGroup->UnloadAll();
		delete m_pObjectXGroup;
		m_pObjectXGroup = nullptr;
	}
	//�����_�����O�̉���E�폜
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	//�C���v�b�g�̉���E�폜
	if (m_pInput != nullptr)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = nullptr;
	}
	if (m_pJoy != nullptr)
	{
		m_pJoy->Uninit();
		delete m_pJoy;
		m_pJoy = nullptr;
	}
	//�J�����̉���E�폜
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	//imgui�̉��
	//if (m_Imgui != nullptr)
	//{
	//	//m_Imgui->Uninit(Hwnd, wcex);
	//	delete m_Imgui;
	//	m_Imgui = nullptr;
	//}
	//�I�u�W�F�N�g�̑S�J��
	CObject::UninitAll();

}

//=============================================================================
// �X�V����
//=============================================================================
void CApplication::Update(void)
{
#ifdef _DEBUG
	int FPS = GetFPS();

	CDebugProc::Print("�t���[�����[�g : %d\n", FPS);

	CDebugProc::Print("���݂̉�ʑJ�ڔԍ� : [%d] \n", m_mode);
#endif // _DEBUG

	m_pJoy->Update();

	//�C���v�b�g�̍X�V����
	if (m_pInput != nullptr)
	{
		m_pInput->Update();
	}
	//�����_�����O�̍X�V����
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}
	//�J�����̍X�V����
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}
	//imgui�̍X�V����
	//if (m_Imgui != nullptr)
	//{
	//	m_Imgui->Update();
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CApplication::Draw(void)
{
	//�����_�����O�̕`�揈��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
	//imgui�̕`�揈��
	//if (m_Imgui != nullptr)
	//{
	//	m_Imgui->Draw();
	//}
}

//=============================================================================
// �����_�����O�̃|�C���^��Ԃ�����
//=============================================================================
CRenderer * CApplication::GetRenderer()
{
	return m_pRenderer;
}

//=============================================================================
// �C���v�b�g�̃|�C���^��Ԃ�����
//=============================================================================
CInput * CApplication::GetInput()
{
	return m_pInput;
}

//=============================================================================
// ���[�h�Z�b�g����
//=============================================================================
void CApplication::SetMode(MODE mode)
{
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		m_pMode = nullptr;
	}

	CObject::ModeRelease();

	m_pCamera->Init();

	m_mode = mode;
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pMode = CTitle::Create();			//
		break;
	case MODE_GAME:
		m_pMode = CGame::Create();			//
		break;
	case MODE_GAME1:
		m_pMode = CGame1::Create();			//
		break;
	case MODE_SELECT_STAGE:			//�X�e�[�W�I��
		m_pMode = CSelectStage::Create();
		break;
	case MODE_RANKING:
		m_pMode = CRanking::Create();			//
		break;
	case MODE_TUTORIAL:			//
		m_pMode = CTutorial::Create();
		break;
	}
}

//=============================================================================
// ���[�h���擾���鏈��
//=============================================================================
CApplication::MODE CApplication::GetMode()
{
	return m_mode;
}

//�A�v���P�[�V����
namespace ease
{
	// �����ŎZ�o
	float InSine(float x) { return 1 - cosf((x * D3DX_PI) * 0.5f); }
	float OutSine(float x) { return sinf((x * D3DX_PI) * 0.5f); }
	float InOutSine(float x) { return -(cosf(D3DX_PI * x) - 1.0f) * 0.5f; }

	// 2�̗ݏ�ŎZ�o
	float InQuad(float x) { return x * x; }
	float OutQuad(float x) { return 1.0f - (1.0f - x) * (1 - x); }
	float InOutQuad(float x) { return x < 0.5f ? 2.0f * x * x : 1.0f - powf(-2.0f * x + 2.0f, 2) * 0.5f; }

	// 3�̗ݏ�ŎZ�o
	float InCubic(float x) { return x * x * x; }
	float OutCubic(float x) { return 1 - powf(1.0f - x, 3.0f); }
	float InOutCubic(float x) { return x < 0.5f ? 4.0f * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 3) * 0.5f; }

	// 4�̗ݏ�ŎZ�o
	float InQuart(float x) { return x * x * x * x; }
	//float OutQuart(float x);
	//float InOutQuart(float x);

	// 5�̗ݏ�ŎZ�o
	float InQuint(float x) { return x * x * x * x * x; }
	//float OutQuint(float x);
	//float InOutQuint(float x);

	// �w���֐��ŎZ�o
	float InExpo(float x) { return x == 0.0f ? 0 : powf(2.0f, 10.0f * x - 10.0f); }
	//float OutExpo(float x);
	//float InOutExpo(float x);

	float InCirc(float x) { return 1.0f - sqrtf(1.0f - powf(x, 2)); }
	//float OutCirc(float x);
	//float InOutCirc(float x);

	float InBack(float x, float s) { return (s + 1.0f) * x * x * x - s * x * x; }
	//float OutBack(float x);
	//float InOutBack(float x);

	float InElastic(float x, float c) { return x == 0 ? 0 : x == 1 ? 1 : -powf(2.f, 10.f * x - 10.f) * sinf((x * 10.f - 10.75f) * c); }
	float OutElastic(float x, float c) { return x == 0 ? 0 : x == 1 ? 1 : powf(2.f, -10.f * x) * sinf((x * 10.f - 0.75f) * c) + 1.f; }
	float InOutElastic(float x, float c) { return x == 0 ? 0 : x == 1 ? 1 : x < 0.5f ? -(powf(2.f, 20.f * x - 10.f) * sinf((x * 20.f - 11.125f) * c)) * 0.5f : (powf(2.f, -20.f * x + 10.f) * sinf((x * 20.f - 11.125f) * c)) * 0.5f + 1.f; }

	float InBounce(float x, float n, float d) { return 1.0f - OutBounce(1 - x, n, d); }
	float OutBounce(float x, float n, float d)
	{
		if (x < 1.0f / d)
		{
			return n * x * x;
		}
		else if (x < 2.0f / d)
		{
			return n * (x -= 1.5f / d) * x + 0.75f;
		}
		else if (x < 2.5f / d)
		{
			return n * (x -= 2.25f / d) * x + 0.9375f;
		}
		else
		{
			return n * (x -= 2.625f / d) * x + 0.984375f;
		}
	}
	float InOutBounce(float x, float n, float d) { return x < 0.5f ? (1.0f - OutBounce(1.0f - 2.0f * x, n, d)) * 0.5f : (1.0f + OutBounce(2.0f * x - 1.0f, n, d)) * 0.5f; }

	//--------------------------------------------------
	// sin�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
	//--------------------------------------------------
	float SinCurve(int nTime, float fCycle)
	{
		return  (sinf(D3DXToRadian(nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
	}//(float)(sinf(D3DXToRadian(Cnt * 20)) * 1.5f);

	//--------------------------------------------------
	// cos�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
	//--------------------------------------------------
	float CosCurve(int nTime, float fCycle)
	{
		return  (cosf(D3DXToRadian((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f)) * 0.5f;
	}

}