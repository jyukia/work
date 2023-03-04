#include "application.h"
#include "fade.h"
#include "mode.h"
#include "renderer.h"

CApplication::MODE CFade::m_ModeNext = {};	//次の画面(モード)
CFade::FADE CFade::m_pfade = {};			//フェードの状態	
D3DXCOLOR CFade::m_color = {};				//カラー

CFade::CFade(int nPriority) : CObject2D(nPriority)
{
	SetType(OBJTYPE_MODE);
}

CFade::~CFade()
{
}

void CFade::Init(CApplication::MODE modeNext)
{
	m_pfade = FADE_IN;		//フェードイン状態に
	m_ModeNext = modeNext;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	CObject2D::Init();

	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	SetSize(D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));
	SetCol(m_color);

	//モードの設定
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
		{//フェードイン状態
			m_color.a -= 0.02f;			//ポリゴンを透明にしていく
			if (m_color.a <= 0.0f)
			{
				m_color.a = 0.0f;
				m_pfade = FADE_NONE;	//何もしていない状態に
			}
		}

		else if (m_pfade == FADE_OUT)
		{ //フェードアウト状態
			m_color.a += 0.02f;		//ポリゴンを不透明にしていく
			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;
				m_pfade = FADE_IN;		//フェードイン状態に

				//モード設定(次の画面に移行)
				CApplication::Getinstnce()->SetMode(m_ModeNext);
			}
		}

		SetCol(m_color);
	}
}

void CFade::SetFade(CApplication::MODE modeNext)
{
	m_pfade = FADE_OUT;								//フェードアウト状態に
	m_ModeNext = modeNext;							//次の画面(モード)を設定
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//黒いポリゴン(透明)にしておく
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