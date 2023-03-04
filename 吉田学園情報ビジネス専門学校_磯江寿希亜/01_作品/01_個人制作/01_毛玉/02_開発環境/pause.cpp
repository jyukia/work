//=============================================================================
// Author : 磯江寿希亜
//
//=============================================================================
//*****************************************************************************
// インクルードファイル
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

//コンストラクタ   CObject::PRIORITY_LEVEL3
CPause::CPause(int nPriority) :m_modecount(0)
{
}
//デストラクタ
CPause::~CPause()
{}
//-----------------------------------------
//初期化
//-----------------------------------------
HRESULT CPause::Init()
{
	m_modecount = 1;

	BindTexture("INIESUTA");

	//プレイヤー入力選択
	m_pGame = CObject2D::Create("PAUSE", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (int)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), PRIORITY_LEVEL4);
	m_pGame->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	CObject2D::Init();
	return S_OK;
}
//-----------------------------------------
//終了
//-----------------------------------------
void CPause::Uninit()
{
	CObject2D::Uninit();
}
//-----------------------------------------
//更新
//-----------------------------------------
void CPause::Update()
{
	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::Getinstnce()->GetInput();
	//コントローラー
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
//描画
//-----------------------------------------
void CPause::Draw()
{
	CObject2D::Draw();
}
//-----------------------------------------
//配置設定
//-----------------------------------------
void CPause::SetObject(D3DXVECTOR3 Pos)
{
	SetPos(Pos);
}
CPause * CPause::Create(const char *aFileName, D3DXVECTOR3 size,D3DXVECTOR3 pos,int nPriority)
{
	CPause* pPause = nullptr;

	//動的確保
	pPause = new CPause(nPriority);

	//NULLチェック
	if (pPause != nullptr)
	{
		//初期化
		pPause->Init();
		pPause->BindTexture(aFileName);
		pPause->SetSize(size);

		//セット
		pPause->SetObject(pos);
	}
	else
	{//処理を止める
		assert(false);
	}

	return pPause;
}
//-----------------------------------------
//Texの読み込み　1つ１つ実体が作られているのでそれを一括で管理し軽くする	Unloadも同様
//-----------------------------------------
HRESULT CPause::Load()
{
	//初期化
	m_pTexture = nullptr;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Tex/Map/pause.png",
		&m_pTexture);

	return S_OK;
}
//-----------------------------------------
//テクスチャの破棄
//-----------------------------------------
void CPause::Unload()
{
	//テクスチャ破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}
