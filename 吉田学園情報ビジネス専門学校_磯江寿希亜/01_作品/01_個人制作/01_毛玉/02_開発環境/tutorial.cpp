//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "application.h"
#include "renderer.h"
#include "objectX.h"
#include "object3D.h"
#include "object2D.h"
#include "object.h"
#include "input.h"
#include "tutorial.h"
#include "fade.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "time.h"
#include "load_stage.h"
#include "goal.h"
#include "inputjoypad.h"
#include "sound.h"

CPlayer *CTutorial::m_pPlayer = nullptr;
CCamera *CTutorial::m_pCamera = nullptr;
CMeshfield *CTutorial::m_pMeshField = nullptr;
CLight *CTutorial::m_pLight = nullptr;
CTime *CTutorial::m_pTime = nullptr;
CObstacle *CTutorial::m_pObstacle = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	m_pObject2D = CObject2D::Create("TUTORIAL", D3DXVECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f), PRIORITY_LEVEL3);
	
	CObject2D* UI_B = CObject2D::Create("B", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 480, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);
	CObject2D* UI_BG1 = CObject2D::Create("CHABG", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 550, 670.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), PRIORITY_LEVEL4);
	CObject2D* UI_Modoru = CObject2D::Create("MODORU", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 550, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit(void)
{
	// �C���X�^���X�̉������
	CObject::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutorial::Update(void)
{
	// �L�[�{�[�h�̏��擾
	CInput *pInputKeyboard = CApplication::Getinstnce()->GetInput();
	//�R���g���[���[
	CInputJoyPad *pJoy = CApplication::GetJoy();

	if (m_pFade->GetFade() == CFade::FADE_NONE)
	{
		if (pInputKeyboard->Trigger(DIK_RETURN) || pJoy->GetTrigger(DirectJoypad::JOYPAD_B, 0))
		{
			// �J��
			CFade::SetFade(CApplication::MODE_TITLE);
			CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_SELECT);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTutorial::Draw(void)
{
}

//=============================================================================
// ��������
//=============================================================================
CTutorial * CTutorial::Create()
{
	//�|�C���^�錾
	CTutorial *pTutorial = nullptr;

	//�C���X�^���X����
	pTutorial = new CTutorial;

	if (pTutorial != nullptr)
	{//�|�C���^�����݂�������s
		pTutorial->Init();
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	//�|�C���^��Ԃ�
	return pTutorial;
}