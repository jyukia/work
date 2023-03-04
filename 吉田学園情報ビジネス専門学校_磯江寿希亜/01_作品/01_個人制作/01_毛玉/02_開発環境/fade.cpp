#include "application.h"
#include "fade.h"
#include "mode.h"
#include "renderer.h"

CApplication::MODE CFade::m_ModeNext = {};	//���̉��(���[�h)
CFade::FADE CFade::m_pfade = {};			//�t�F�[�h�̏��	
D3DXCOLOR CFade::m_color = {};				//�J���[

CFade::CFade(int nPriority) : CObject2D(nPriority)
{
	SetType(OBJTYPE_MODE);
}

CFade::~CFade()
{
}

void CFade::Init(CApplication::MODE modeNext)
{
	m_pfade = FADE_IN;		//�t�F�[�h�C����Ԃ�
	m_ModeNext = modeNext;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	CObject2D::Init();

	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	SetSize(D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));
	SetCol(m_color);

	//���[�h�̐ݒ�
	CApplication::Getinstnce()->SetMode(m_ModeNext);
}

void CFade::Uninit(void)
{
	CObject2D::Release();
}

void CFade::Update(void)
{
	CObject2D::Update();

	if (m_pfade != FADE_NONE)
	{
		if (m_pfade == FADE_IN)
		{//�t�F�[�h�C�����
			m_color.a -= 0.02f;			//�|���S���𓧖��ɂ��Ă���
			if (m_color.a <= 0.0f)
			{
				m_color.a = 0.0f;
				m_pfade = FADE_NONE;	//�������Ă��Ȃ���Ԃ�
			}
		}

		else if (m_pfade == FADE_OUT)
		{ //�t�F�[�h�A�E�g���
			m_color.a += 0.02f;		//�|���S����s�����ɂ��Ă���
			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;
				m_pfade = FADE_IN;		//�t�F�[�h�C����Ԃ�

				//���[�h�ݒ�(���̉�ʂɈڍs)
				CApplication::Getinstnce()->SetMode(m_ModeNext);
			}
		}

		SetCol(m_color);
	}
}

void CFade::SetFade(CApplication::MODE modeNext)
{
	m_pfade = FADE_OUT;								//�t�F�[�h�A�E�g��Ԃ�
	m_ModeNext = modeNext;							//���̉��(���[�h)��ݒ�
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�����|���S��(����)�ɂ��Ă���
}

CFade::FADE CFade::GetFade(void)
{
	return m_pfade;
}

CFade * CFade::Create(CApplication::MODE modeNext)
{
	CFade *pFade = new CFade;

	if (pFade != nullptr)
	{
		pFade->Init(modeNext);
	}

	return pFade;
}