//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "title.h"
#include "renderer.h"
#include "application.h"
#include "input.h"
#include "fade.h"
#include "object2D.h"

#include "objectX.h"
#include "object3D.h"
#include "object2D.h"


#include "player.h"
#include "light.h"
#include "meshfield.h"
#include "Meshline.h"
#include "camera.h"
#include"DebugProc.h"
#include "load_stage.h"
#include"skyfield.h"
#include "inputjoypad.h"
#include "ranking.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = nullptr;

CPlayer *CTitle::m_pPlayer = nullptr;
CMeshfield *CTitle::m_pMeshField = nullptr;
CLight *CTitle::m_pLight = nullptr;
CMeshLine *m_pMeshLine = nullptr;			//	メッシュライン

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle():m_modecount(0), m_bmodeflg(false)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	//ライトの生成
	m_pLight = CLight::Create();

	{//初期化
		m_modecount = 1;
		m_bmodeflg = false;
	}

	//プレイヤーの生成
	CApplication::Getinstnce()->GetpMode()->SetPlayer(CPlayer::Create(D3DXVECTOR3(1850.0f, 20.0f, -600.0f), CObject::PRIORITY_LEVEL3));
	CApplication::Getinstnce()->GetpMode()->GetPlayer()->LoadModel("Kedama");

	{//壁
		for (int cont = 0; cont < 5; cont++)
		{
			CObjectX* wallX = CObjectX::CObjectX::Create("FENCE", D3DXVECTOR3(700.0f + 520.0f * cont, 0.0f, -3500.0f), 3);
		}
		for (int cont = 0; cont < 6; cont++)
		{
			CObjectX* wallX1 = CObjectX::CObjectX::Create("FENCEROT", D3DXVECTOR3(3000.0f, 0.0f, -3200.0f + 515.0f * cont), 3);
		}
		for (int cont = 0; cont < 5; cont++)
		{
			CObjectX* wallX2 = CObjectX::CObjectX::Create("FENCE", D3DXVECTOR3(2780.0f - 515.0f * cont, 0.0f, -350.0f), 3);
		}
		for (int cont = 0; cont < 6; cont++)
		{
			CObjectX* wallX3 = CObjectX::CObjectX::Create("FENCEROT", D3DXVECTOR3(450.0f, 0, -3200.0f + 515.0f * cont), 3);
		}
	}

	//メッシュフィールドの生成
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-1500.0f, 0.0f, 1500.0f), CObject::PRIORITY_LEVEL3);
	m_pMeshField->LoadTexture("Data\\TEXTURE\\shiba.png");

	//タイトル配置
	m_pTitle = CObject2D::Create("TITLE",D3DXVECTOR3((float)SCREEN_WIDTH_HALF,-150.0f,0.0f), D3DXVECTOR3(800.0f, 500.0f, 0.0f), PRIORITY_LEVEL4);

	//プレイヤー入力選択
	m_pGame = CObject2D::Create("GAMEPLAY", D3DXVECTOR3((float)SCREEN_WIDTH_HALF -300, (int)SCREEN_HEIGHT_HALF + 150, 0.0f), D3DXVECTOR3(400.0f, 400.0f, 0.0f), PRIORITY_LEVEL4);
	m_pRanking = CObject2D::Create("RANKING", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 300, (int)SCREEN_HEIGHT_HALF + 150, 0.0f), D3DXVECTOR3(400.0f, 400.0f, 0.0f), PRIORITY_LEVEL4);
	m_ptutelial = CObject2D::Create("TUTORIALUI", D3DXVECTOR3((float)SCREEN_WIDTH_HALF , (int)SCREEN_HEIGHT_HALF + 150, 0.0f), D3DXVECTOR3(400.0f, 400.0f, 0.0f), PRIORITY_LEVEL4);

	CObject2D* UI_A = CObject2D::Create("A", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 300, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);
	CObject2D* UI_BG = CObject2D::Create("CHABG", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 380, 670.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), PRIORITY_LEVEL4);
	CObject2D* UI_Kxtutei = CObject2D::Create("KEXTUTEI", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 380, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);

	//CObject2D* UI_B = CObject2D::Create("B", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 480, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);
	//CObject2D* UI_BG1 = CObject2D::Create("CHABG", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 550, 670.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), PRIORITY_LEVEL4);
	//CObject2D* UI_Modoru = CObject2D::Create("MODORU", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 550, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);

	CObject2D* UI_JYU = CObject2D::Create("JYUUJI", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 130, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);
	CObject2D* UI_BG2 = CObject2D::Create("CHABG", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 200, 670.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), PRIORITY_LEVEL4);
	CObject2D* UI_Idou = CObject2D::Create("IDOU", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 200, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);

	CSkyField::Create();

	CRanking::GetRanking(0);	//スコアとなる値
	CRanking::GetRanking1(0);	//スコアとなる値

	CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_TITLE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
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

	CApplication::Getinstnce()->GetSound()->Stop(CSound::LABEL_TITLE);
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	{//デバック処理
		CDebugProc::Print("遷移のための選択カウント : [%d]\n", m_modecount);
	}

	D3DXVECTOR3 move = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetMove();
	bool flg = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetMoveFlg();

	D3DXVECTOR3 pos = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetPos();
	pos.y += 20;
	CApplication::Getinstnce()->GetpMode()->GetPlayer()->SetPos(pos);

	if (flg)	//移動可
	{
		move.z -= 1;
	}
	else	//移動不可
	{
		move.z = 0;
	}
	CApplication::Getinstnce()->GetpMode()->GetPlayer()->SetMove(move);

	//ゲームネームの情報取得
	D3DXVECTOR3 Titlepos = m_pTitle->GetPos();
	D3DXVECTOR3 Gamepos = m_pGame->GetPos();
	D3DXVECTOR3 Rankingpos = m_pRanking->GetPos();
	int stop = (int)SCREEN_HEIGHT_HALF - 110;
	int stop1 = (int)SCREEN_HEIGHT_HALF + 110;

	//タイトル止まる処理
	if (Titlepos.y >= stop)
	{
		m_pTitle->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		m_pTitle->SetMove(D3DXVECTOR3(0.0f, 2.0f, 0.0f));
	}

	////タイトル止まる処理
	//if (Gamepos.y >= stop1)
	//{
	//	m_pGame->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//	m_pRanking->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}
	//else
	//{
	//	m_pGame->SetMove(D3DXVECTOR3(0.0f, 2.0f, 0.0f));
	//	m_pRanking->SetMove(D3DXVECTOR3(0.0f, 2.0f, 0.0f));
	//}

	//コントローラー
	CInputJoyPad *pJoy = CApplication::GetJoy();
	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::Getinstnce()->GetInput();
	if (pInputKeyboard->Trigger(DIK_A) || pJoy->GetCrossTrigger(DirectJoypad::JOYPAD_LEFT, 0))
	{// 上に移動
		m_modecount++;
		CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_CHANGE);
	}
	if (pInputKeyboard->Trigger(DIK_D) || pJoy->GetCrossTrigger(DirectJoypad::JOYPAD_RIGHT, 0))
	{// 下に移動
		m_modecount--;
		CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_CHANGE);
	}
	if (pInputKeyboard->Trigger(DIK_RETURN) || pJoy->GetTrigger(DirectJoypad::JOYPAD_A, 0))		//選択シーン実行
	{
		D3DXVECTOR3 posV = CApplication::Getinstnce()->GetCamera()->GetPosV();
		if (m_pFade->GetFade() == CFade::FADE_NONE)
		{
			if (m_modecount == 1)
			{
				//遷移
				CFade::SetFade(CApplication::MODE_SELECT_STAGE);	//ゲーム遷移
			}
			if (m_modecount == 2)
			{
				//遷移
				CFade::SetFade(CApplication::MODE_RANKING); //ランキング遷移
			}
			if (m_modecount == 3)
			{
				//遷移
				CFade::SetFade(CApplication::MODE_TUTORIAL); //ランキング遷移
			}
		}
		CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_SELECT);
	}

	//選択カウントの制限
	if (m_modecount > m_modeMax)
	{
		m_modecount = m_modeMin;
	}
	if (m_modecount < m_modeMin)
	{
		m_modecount = m_modeMax;
	}

	//選択際色の変更分かりやすく
	if (m_modecount == 1)
	{
		m_pGame->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pRanking->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_ptutelial->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}
	if (m_modecount == 2)
	{
		m_pGame->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_pRanking->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_ptutelial->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}
	if (m_modecount == 3)
	{
		m_ptutelial->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pRanking->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_pGame->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CTitle * CTitle::Create()
{
	//ポインタ宣言
	CTitle *pTitle = nullptr;

	//インスタンス生成
	pTitle = new CTitle;

	if (pTitle != nullptr)
	{//ポインタが存在したら実行
		pTitle->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pTitle;
}
