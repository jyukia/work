#include"SelectStage.h"
#include "main.h"
#include "renderer.h"
#include "application.h"
#include "input.h"
#include "fade.h"
#include "objectX.h"
#include "object3D.h"
#include "object2D.h"
#include "light.h"
#include"DebugProc.h"
#include "inputjoypad.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CSelectStage::m_pTexture = nullptr;

CLight *CSelectStage::m_pLight = nullptr;

int CSelectStage::m_modeSelectcount;

//=============================================================================
// コンストラクタ
//=============================================================================
CSelectStage::CSelectStage(): m_bmodeflg(false)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CSelectStage::~CSelectStage()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSelectStage::Init(void)
{
	{//変数初期化
		m_modeSelectcount = 1;
		m_bmodeflg = false;
	}

	//ライトの生成
	m_pLight = CLight::Create();

	//ステージ選択
	CObject2D* selectstage = CObject2D::Create("SELECTSTAGE", D3DXVECTOR3(1000.0f, 40.0f, 0.0f), D3DXVECTOR3(600.0f, 400.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	//1つ目のステージ名
	stagename = CObject2D::Create("STAGENAME", D3DXVECTOR3(300.0f, 600.0f, 0.0f), D3DXVECTOR3(600.0f, 400.0f, 0.0f), CObject::PRIORITY_LEVEL3);
	//2つ目のステージ名
	stagename1 = CObject2D::Create("STAGENAME1", D3DXVECTOR3(300.0f, 600.0f, 0.0f), D3DXVECTOR3(600.0f, 400.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	//ステージ位置
	D3DXVECTOR3 pos = D3DXVECTOR3(730.0f, 10.0f, 0.0f);
	D3DXVECTOR3 pos1 = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//ステージ1
	pStage = CObjectX::Create(pos, CObject::PRIORITY_LEVEL3);
	pStage->LoadModel("MAP1");
	//ステージ2
	pStage1 = CObjectX::Create(pos1, CObject::PRIORITY_LEVEL3);
	pStage1->LoadModel("MAP2");

	CObject2D* UI_A = CObject2D::Create("A", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 300, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);
	CObject2D* UI_BG = CObject2D::Create("CHABG", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 380, 670.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), PRIORITY_LEVEL4);
	CObject2D* UI_Kxtutei = CObject2D::Create("KEXTUTEI", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 380, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);

	CObject2D* UI_B = CObject2D::Create("B", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 480, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);
	CObject2D* UI_BG1 = CObject2D::Create("CHABG", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 550, 670.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), PRIORITY_LEVEL4);
	CObject2D* UI_Modoru = CObject2D::Create("MODORU", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 550, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);

	CObject2D* UI_JYU = CObject2D::Create("JYUUJI", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 130, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);
	CObject2D* UI_BG2 = CObject2D::Create("CHABG", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 200, 670.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), PRIORITY_LEVEL4);
	CObject2D* UI_Idou = CObject2D::Create("IDOU", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 200, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);

	CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_SELECTSTAGE);
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CSelectStage::Uninit(void)
{
	//ライトの解放・削除
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	//インスタンスの解放処理
	CObject::Release();

	CApplication::Getinstnce()->GetSound()->Stop(CSound::LABEL_SELECTSTAGE);
}
//=============================================================================
// 更新処理
//=============================================================================
void CSelectStage::Update(void)
{
//円の計算式
	//計算式
	//radius = m_Angle * 3.14f / 180.0f;
	//// 三角関数を使用し、円の位置を割り出す。
	//add_x = cos(radius) * 10;
	//add_z = sin(radius) * 10;
	////向きを変える
	//m_Angle += 3.0f;
	//
	//CDebugProc::Print("add_x : %f\n", add_x);
	//CDebugProc::Print("add_z : %f\n", add_z);

	CDebugProc::Print("m_modeSelectcount : %d\n", m_modeSelectcount);

	//=====================================
	//1つ目のマップ宣言と処理
	D3DXVECTOR3 pos = pStage->GetPos();
	D3DXVECTOR3 rot = pStage->GetRot();
	//=====================================
	//2つ目のマップ宣言と処理
	D3DXVECTOR3 pos1 = pStage1->GetPos();
	D3DXVECTOR3 rot1 = pStage1->GetRot();

	// 入力処理用のポインタ宣言
	CInput *pInput = CApplication::Getinstnce()->GetInput();
	//コントローラー
	CInputJoyPad *pJoy = CApplication::GetJoy();

	if (m_modeSelectcount == 1)
	{
		//モデルの回転変更無し
		rot.y += 0.01f;

		//1つ目のステージ名
		stagename->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		//2つ目のステージ名
		stagename1->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		if (m_pFade->GetFade() == CFade::FADE_NONE)
		{
			if (pInput->Trigger(DIK_RETURN) || pJoy->GetTrigger(DirectJoypad::JOYPAD_A, 0))
			{
				//遷移
				CFade::SetFade(CApplication::MODE_GAME);	//ゲーム遷移
				CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_SELECT);
			}
		}

	}
	if (m_modeSelectcount == 2)
	{
		//モデルの回転変更無し
		rot1.y += 0.01f;

		//1つ目のステージ名
		stagename->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		//2つ目のステージ名
		stagename1->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		if (m_pFade->GetFade() == CFade::FADE_NONE)
		{
			if (pInput->Trigger(DIK_RETURN) || pJoy->GetTrigger(DirectJoypad::JOYPAD_A, 0))
			{
				//遷移
				CFade::SetFade(CApplication::MODE_GAME1);	//ゲーム遷移
				CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_SELECT);
			}
		}
	}
	if (m_pFade->GetFade() == CFade::FADE_NONE)	//　タイトルに戻る処理
	{
		if (pInput->Trigger(DIK_ESCAPE) || pJoy->GetTrigger(DirectJoypad::JOYPAD_B, 0))
		{
			//遷移
			CFade::SetFade(CApplication::MODE_TITLE);	//ゲーム遷移
		}
	}
	//=====================================
	pStage->SetPos(pos);
	pStage->SetRot(rot);
	//=====================================
	pStage1->SetPos(pos1);
	pStage1->SetRot(rot1);
	//=====================================

	//選択カウントの制限
	if (m_modeSelectcount > m_modeMax)
	{
		m_modeSelectcount = m_modeMin;
	}
	if (m_modeSelectcount < m_modeMin)
	{
		m_modeSelectcount = m_modeMax;
	}

	//セレクトの移動
	if (pInput->Trigger(DIK_D) || pJoy->GetTrigger(DirectJoypad::JOYPAD_RIGHT, 0))
	{
		m_modeSelectcount++;
		CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_CHANGE);

	}
	if (pInput->Trigger(DIK_A) || pJoy->GetTrigger(DirectJoypad::JOYPAD_LEFT, 0))
	{
		m_modeSelectcount--;
		CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_CHANGE);

	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CSelectStage::Draw(void)
{

}
//=============================================================================
// 生成処理
//=============================================================================
CSelectStage * CSelectStage::Create()
{
	//ポインタ宣言
	CSelectStage *pSelectStage = nullptr;

	//インスタンス生成
	pSelectStage = new CSelectStage;

	if (pSelectStage != nullptr)
	{//ポインタが存在したら実行
		pSelectStage->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pSelectStage;
}
