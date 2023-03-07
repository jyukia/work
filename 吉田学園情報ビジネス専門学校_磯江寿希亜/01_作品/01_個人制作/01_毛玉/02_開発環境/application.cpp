//=============================================================================
// インクルードファイル
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

//紅茶で移動速度を落とすギミック追加
//２つ目のマップ坂を作り移動、虫の追加はねられて移動ベクトル変更

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CApplication *CApplication::m_pApplication = nullptr;
CInputJoyPad *CApplication::m_pJoy = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CApplication::CApplication():m_pRenderer(nullptr), m_pInput(nullptr), m_pMode(nullptr), m_pCamera(nullptr), m_pTexture(nullptr), m_pObjectXGroup(nullptr), m_pSound(nullptr), m_pDebugProc(nullptr), m_Item(nullptr)//, m_Imgui(nullptr)
{
	CApplication::m_mode = MODE_TITLE;//MODE_RANKING
}
//=============================================================================
// デストラクタ
//=============================================================================
CApplication::~CApplication()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	Hwnd = hWnd;

	//乱数の初期化
	srand((unsigned int)time(0));

	//レンダリングクラスの生成
	m_pRenderer = new CRenderer;
	//レンダリングの初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{ //初期化処理が失敗した場合
		return -1;
	}
	//インプットクラスの生成
	m_pInput = CInput::Create();
	//インプットの初期化処理
	if (FAILED(m_pInput->Init(hInstance, hWnd)))
	{ //初期化処理が失敗した場合
		return -1;
	}
	m_pJoy = new CInputJoyPad;
	if (FAILED(m_pJoy->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	m_pDebugProc = new CDebugProc;
	// 初期化
	assert(m_pDebugProc != nullptr);
	m_pDebugProc->Init();

	LPDIRECT3DDEVICE9 pDevice = m_pRenderer->GetDevice();
	//m_Imgui = new CStageImgui;
	//// 初期化
	//assert(m_Imgui != nullptr);
	//m_Imgui->Init(hWnd, pDevice);

	// カメラの初期化
	m_pCamera = new CCamera;
	assert(m_pCamera != nullptr);

	// テクスチャの生成
	m_pTexture = new CTexture;
	assert(m_pTexture != nullptr);
	m_pTexture->LoadAll();

	// モデルの生成
	m_pObjectXGroup = new CObjectXGroup;
	assert(m_pObjectXGroup != nullptr);
	m_pObjectXGroup->LoadAll();

	// サウンドの生成
	m_pSound = new CSound;
	assert(m_pSound != nullptr);
	m_pSound->Init(hWnd);

	//モード生成
	CFade::Create(m_mode);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CApplication::Uninit(void)
{

	// テクスチャの削除
	if (m_pTexture != nullptr)
	{
		m_pTexture->UnloadAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}
	//デバック表示
	if (m_pDebugProc != nullptr)
	{// 終了処理
		m_pDebugProc->Uninit();

		// メモリの解放
		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}
	// サウンドの削除
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
	// Xモデルの削除
	if (m_pObjectXGroup != nullptr)
	{
		m_pObjectXGroup->UnloadAll();
		delete m_pObjectXGroup;
		m_pObjectXGroup = nullptr;
	}
	//レンダリングの解放・削除
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	//インプットの解放・削除
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
	//カメラの解放・削除
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	//imguiの解放
	//if (m_Imgui != nullptr)
	//{
	//	//m_Imgui->Uninit(Hwnd, wcex);
	//	delete m_Imgui;
	//	m_Imgui = nullptr;
	//}
	//オブジェクトの全開放
	CObject::UninitAll();

}

//=============================================================================
// 更新処理
//=============================================================================
void CApplication::Update(void)
{
#ifdef _DEBUG
	int FPS = GetFPS();

	CDebugProc::Print("フレームレート : %d\n", FPS);

	CDebugProc::Print("現在の画面遷移番号 : [%d] \n", m_mode);
#endif // _DEBUG

	m_pJoy->Update();

	//インプットの更新処理
	if (m_pInput != nullptr)
	{
		m_pInput->Update();
	}
	//レンダリングの更新処理
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}
	//カメラの更新処理
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}
	//imguiの更新処理
	//if (m_Imgui != nullptr)
	//{
	//	m_Imgui->Update();
	//}
}

//=============================================================================
// 描画処理
//=============================================================================
void CApplication::Draw(void)
{
	//レンダリングの描画処理
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
	//imguiの描画処理
	//if (m_Imgui != nullptr)
	//{
	//	m_Imgui->Draw();
	//}
}

//=============================================================================
// レンダリングのポインタを返す処理
//=============================================================================
CRenderer * CApplication::GetRenderer()
{
	return m_pRenderer;
}

//=============================================================================
// インプットのポインタを返す処理
//=============================================================================
CInput * CApplication::GetInput()
{
	return m_pInput;
}

//=============================================================================
// モードセット処理
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
	case MODE_SELECT_STAGE:			//ステージ選択
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
// モードを取得する処理
//=============================================================================
CApplication::MODE CApplication::GetMode()
{
	return m_mode;
}

//アプリケーション
namespace ease
{
	// 正弦で算出
	float InSine(float x) { return 1 - cosf((x * D3DX_PI) * 0.5f); }
	float OutSine(float x) { return sinf((x * D3DX_PI) * 0.5f); }
	float InOutSine(float x) { return -(cosf(D3DX_PI * x) - 1.0f) * 0.5f; }

	// 2の累乗で算出
	float InQuad(float x) { return x * x; }
	float OutQuad(float x) { return 1.0f - (1.0f - x) * (1 - x); }
	float InOutQuad(float x) { return x < 0.5f ? 2.0f * x * x : 1.0f - powf(-2.0f * x + 2.0f, 2) * 0.5f; }

	// 3の累乗で算出
	float InCubic(float x) { return x * x * x; }
	float OutCubic(float x) { return 1 - powf(1.0f - x, 3.0f); }
	float InOutCubic(float x) { return x < 0.5f ? 4.0f * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 3) * 0.5f; }

	// 4の累乗で算出
	float InQuart(float x) { return x * x * x * x; }
	//float OutQuart(float x);
	//float InOutQuart(float x);

	// 5の累乗で算出
	float InQuint(float x) { return x * x * x * x * x; }
	//float OutQuint(float x);
	//float InOutQuint(float x);

	// 指数関数で算出
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
	// sinカーブの値が1.0f～0.0fで帰ってくる
	//--------------------------------------------------
	float SinCurve(int nTime, float fCycle)
	{
		return  (sinf(D3DXToRadian(nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
	}//(float)(sinf(D3DXToRadian(Cnt * 20)) * 1.5f);

	//--------------------------------------------------
	// cosカーブの値が1.0f～0.0fで帰ってくる
	//--------------------------------------------------
	float CosCurve(int nTime, float fCycle)
	{
		return  (cosf(D3DXToRadian((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f)) * 0.5f;
	}

}