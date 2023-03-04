//=============================================================================
// インクルードファイル
//=============================================================================
#include "application.h"
#include "renderer.h"
#include "objectX.h"
#include "object3D.h"
#include "object2D.h"
#include "object.h"
#include "input.h"
#include "title.h"
#include "game1.h"
#include "fade.h"
#include "player.h"
#include "light.h"
#include "meshfield.h"
#include "camera.h"
#include "Meshline.h"
#include"Number.h"
#include"score.h"
#include "file.h"
#include "goal.h"
#include"skyfield.h"
#include "movelife.h"
#include "Preparation.h"
#include "load_stage.h"
#include"Timer.h"
#include"2dParticle.h"
#include "Item.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CPlayer *CGame1::m_pPlayer = nullptr;
CMeshfield *CGame1::m_pMeshField = nullptr;
CLight *CGame1::m_pLight = nullptr;
CScore* CGame1::pScore = nullptr;
CMovelife* CGame1::pMovelife = nullptr;
CGoal* CGame1::m_pGoal = nullptr;
CItem* CGame1::m_pItemTimeUp = nullptr;
CItem* CGame1::m_pItem = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CGame1::CGame1()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CGame1::~CGame1()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame1::Init(void)
{
	//ゲーム開始の合図
	m_pPreparation->Create("REDY", D3DXVECTOR3(SCREEN_WIDTH + 100, SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	//ライトの生成
	m_pLight = CLight::Create();

	{//初期化
		returnflg = false;
		Goalflg = false;

		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//メッシュフィールドの生成
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-1500.0f, 0.0f, 1500.0f), CObject::PRIORITY_LEVEL3);
	m_pMeshField->LoadTexture("Data\\TEXTURE\\shiba.png");

	//プレイヤーの生成
	CApplication::Getinstnce()->GetpMode()->SetPlayer(CPlayer::Create(D3DXVECTOR3(2300.0f, 20.0f, -2900.0f), CObject::PRIORITY_LEVEL3));
	CApplication::Getinstnce()->GetpMode()->GetPlayer()->LoadModel("Kedama");

	//コンパス生成
	//m_pCompass = CObject2D::Create("COMPASS", D3DXVECTOR3(1150.0f, 110.0f, 0.0f), D3DXVECTOR3(220.0f, 220.0f, 0.0f), CObject::PRIORITY_LEVEL3);


	goalui = CObject3D::Create(D3DXVECTOR3(1100.0f, 400.0f, -600.0f), D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(350, 350.0f, 0.0f), CObject::PRIORITY_LEVEL4);
	goalui->LoadTexture("Data/TEXTURE/GOALUI.png");//1890.0f, 605.0f, -2300.0f
	goalui->SetBillboard(true);

	m_pGoal = CGoal::Create(D3DXVECTOR3(1100.0f, 0.0f, -600.0f), CObject::PRIORITY_LEVEL3);
	m_pGoal->LoadModel("BSKET");
	m_pGoal->Setstring("GOAL");

	m_pItem = CItem::Create(D3DXVECTOR3(1350.0f, 0.0f, -1900.0f), CObject::PRIORITY_LEVEL3, CItem::ITEM_MOVE_SPEED_UP);	//ITEM_MOVELIFE_UP  ITEM_MOVE_SPEED_UP ITEM_SCORE_UP
	m_pItem->LoadModel("BOOTS");

	m_pItemTimeUp = CItem::Create(D3DXVECTOR3(730.0f, 0.0f, -1860.0f), CObject::PRIORITY_LEVEL3, CItem::ITEM_GAMETIME_UP);	//ITEM_GAMETIME_UP  ITEM_MOVE_SPEED_UP ITEM_SCORE_UP
	m_pItemTimeUp->LoadModel("ITEMTIME");


	//CObjectX* obje = CObjectX::Create("CONE", D3DXVECTOR3(1680.0f ,0.0f ,- 2600.0f), CObject::PRIORITY_LEVEL3);

	//for (int Cnt = 0; Cnt < 4;Cnt++)
	//{
	//	CObjectX* obje1 = CObjectX::Create("CONE", D3DXVECTOR3(1730.0f + -300 * Cnt, 0.0f, -2250.0f),CObject::PRIORITY_LEVEL3);
	//}
	//for (int Cnt = 0; Cnt < 4; Cnt++)
	//{
	//	CObjectX* obje2 = CObjectX::Create("BOTTLE", D3DXVECTOR3(2525.0f + -100 * Cnt, 0.0f, -1800.0f),CObject::PRIORITY_LEVEL3);
	//}
	//for (int Cnt = 0; Cnt < 4; Cnt++)
	//{
	//	CObjectX* obje2 = CObjectX::Create("BOTTLE", D3DXVECTOR3(2553.0f, 0.0f, -1630.0f + 100 * Cnt),CObject::PRIORITY_LEVEL3);
	//}
	//for (int Cnt = 0; Cnt < 4; Cnt++)
	//{
	//	CObjectX* obje2 = CObjectX::Create("BOTTLE", D3DXVECTOR3(2470.0f - 100.0f * Cnt, 0.0f, - 1200.0f),CObject::PRIORITY_LEVEL3);
	//}
	//for (int Cnt = 0; Cnt < 4; Cnt++)
	//{
	//	CObjectX* obje2 = CObjectX::Create("BOTTLE", D3DXVECTOR3(2170.0f, 0.0f, -1080.0f + 100 * Cnt),CObject::PRIORITY_LEVEL3);
	//}
	for (int cont = 0; cont < 6; cont++)
	{
		CObjectX* botle = CObjectX::CObjectX::Create("BOTTLE", D3DXVECTOR3(1200.0f, 0.0f, -2050.0f + 100 * cont), CObject::PRIORITY_LEVEL3);
	}
	CObjectX* botle = CObjectX::CObjectX::Create("BOTTLE", D3DXVECTOR3(1300.0f, 0.0f, -2050.0f), CObject::PRIORITY_LEVEL3);
	for (int cont = 0; cont < 5; cont++)
	{
		CObjectX* botle = CObjectX::CObjectX::Create("BOTTLE", D3DXVECTOR3(1000.0f, 0.0f, -2050.0f + 100 * cont), CObject::PRIORITY_LEVEL3);
	}
	for (int cont = 0; cont < 5; cont++)
	{
		CObjectX* botle = CObjectX::CObjectX::Create("BOTTLE", D3DXVECTOR3(900.0f - 100 * cont, 0.0f, -2050.0f), CObject::PRIORITY_LEVEL3);
	}
	for (int cont = 0; cont < 3; cont++)
	{
		CObjectX* botle = CObjectX::CObjectX::Create("BOTTLE", D3DXVECTOR3(1150.0f - 100 * cont, 0.0f, -1300.0f), CObject::PRIORITY_LEVEL3);
	}
	for (int cont = 0; cont < 3; cont++)
	{
		CObjectX* botle = CObjectX::CObjectX::Create("BOTTLE", D3DXVECTOR3(550.0f + 100 * cont, 0.0f, -1300.0f), CObject::PRIORITY_LEVEL3);
	}

	for (int cont = 0; cont < 3; cont++)
	{
		CObjectX* beermug = CObjectX::CObjectX::Create("BEERMUG", D3DXVECTOR3(2200.0f-120* cont, 0.0f, -1650.0f), CObject::PRIORITY_LEVEL3);
	}
	for (int cont = 0; cont < 4; cont++)
	{
		CObjectX* beermug = CObjectX::CObjectX::Create("BEERMUG", D3DXVECTOR3(2300.0f, 0.0f, -1650.0f - 120 * cont), CObject::PRIORITY_LEVEL3);
	}
	for (int cont = 0; cont < 5; cont++)
	{
		CObjectX* beermug = CObjectX::CObjectX::Create("BEERMUG", D3DXVECTOR3(1830.0f, 0.0f, -1650.0f + 120 * cont), CObject::PRIORITY_LEVEL3);
	}
	for (int cont = 0; cont < 5; cont++)
	{
		CObjectX* beermug = CObjectX::CObjectX::Create("BEERMUG", D3DXVECTOR3(1950.0f + 120 * cont, 0.0f, -1150.0f), CObject::PRIORITY_LEVEL3);
	}
	for (int cont = 0; cont < 3; cont++)
	{
		CObjectX* botle = CObjectX::CObjectX::Create("BOTTLE", D3DXVECTOR3(950.0f, 0.0f, -1200.0f + 100 * cont), CObject::PRIORITY_LEVEL3);
	}
	for (int cont = 0; cont < 2; cont++)
	{
		CObjectX* botle = CObjectX::CObjectX::Create("BOTTLE", D3DXVECTOR3(850.0f - 100 * cont, 0.0f, -950.0f ), CObject::PRIORITY_LEVEL3);
	}
	//CObjectX* bottle = CObjectX::CObjectX::Create("BOTTLE", D3DXVECTOR3(540.0f, 0.0f, -970.0f), CObject::PRIORITY_LEVEL3);

	CObjectX* bottle1 = CObjectX::CObjectX::Create("BOTTLE", D3DXVECTOR3(2700.0f, 20.0f, -1700.0f), CObject::PRIORITY_LEVEL3);
	bottle1->SetRot(D3DXVECTOR3(0.0f,0.0f, D3DX_PI / 2));


	//for (int cont = 0; cont < 6; cont++)
	//{
	//	CObjectX* botle = CObjectX::CObjectX::Create("BEERBOTTLE", D3DXVECTOR3(1100.0f - 100 * cont, 0.0f, -1450.0f),CObject::PRIORITY_LEVEL3);
	//}
	//for (int cont = 0; cont < 3; cont++)
	//{
	//	CObjectX* botle = CObjectX::CObjectX::Create("BEERMUG", D3DXVECTOR3(1450.0f, 0.0f, -3330.0f + 100 * cont), CObject::PRIORITY_LEVEL3);
	//}

	//for (int cont = 0; cont < 3; cont++)
	//{
	//	CObjectX* botle = CObjectX::CObjectX::Create("BEERMUG", D3DXVECTOR3(1250.0f + 100 * cont, 0.0f, -2800.0f),CObject::PRIORITY_LEVEL3);
	//}
	//for (int cont = 0; cont < 2; cont++)
	//{
	//	CObjectX* botle = CObjectX::CObjectX::Create("CONE", D3DXVECTOR3(890.0f, 0.0f, -3300.0f + 230 * cont),CObject::PRIORITY_LEVEL3);
	//}
	////CObjectX* botle = CObjectX::CObjectX::Create("CONE", D3DXVECTOR3(630.0f, 0.0f, -3070.0f),CObject::PRIORITY_LEVEL3);
	//for (int cont = 0; cont < 3; cont++)
	//{
	//	CObjectX* botle = CObjectX::CObjectX::Create("BEERMUG", D3DXVECTOR3(860.0f, 0.0f, -2500.0f - 100 * cont), CObject::PRIORITY_LEVEL3);
	//}

	{//壁
		for (int cont = 0; cont < 5; cont++)
		{
			CObjectX* wallX = CObjectX::CObjectX::Create("FENCE", D3DXVECTOR3(700.0f + 520.0f * cont, 0.0f, -3500.0f), CObject::PRIORITY_LEVEL3);
		}
		for (int cont = 0; cont < 6; cont++)
		{
			CObjectX* wallX1 = CObjectX::CObjectX::Create("FENCEROT", D3DXVECTOR3(3000.0f, 0.0f, -3200.0f + 515.0f * cont), CObject::PRIORITY_LEVEL3);
		}
		for (int cont = 0; cont < 5; cont++)
		{
			CObjectX* wallX2 = CObjectX::CObjectX::Create("FENCE", D3DXVECTOR3(2780.0f - 515.0f * cont, 0.0f, -350.0f), CObject::PRIORITY_LEVEL3);
		}
		for (int cont = 0; cont < 6; cont++)
		{
			CObjectX* wallX3 = CObjectX::CObjectX::Create("FENCEROT", D3DXVECTOR3(450.0f, 0.0f, -3200.0f + 515.0f * cont), CObject::PRIORITY_LEVEL3);
		}
	}

	//初期
	{
		for (int cont = 0; cont < 10; cont++)
		{
			CObjectX* botle = CObjectX::CObjectX::Create("BEERBOTTLE", D3DXVECTOR3(2000.0f, 0.0f, -3400.0f + 70 * cont), CObject::PRIORITY_LEVEL3);
		}
		for (int cont = 0; cont < 10; cont++)
		{
			CObjectX* botle = CObjectX::CObjectX::Create("BEERBOTTLE", D3DXVECTOR3(2000.0f + 70 * cont, 0.0f, -2700.0f), CObject::PRIORITY_LEVEL3);
		}
		for (int cont = 0; cont < 7; cont++)
		{
			CObjectX* botle = CObjectX::CObjectX::Create("BEERBOTTLE", D3DXVECTOR3(2600.0f, 0.0f, -2700.0f - 70 * cont), CObject::PRIORITY_LEVEL3);
		}
		for (int cont = 0; cont < 10; cont++)
		{
			CObjectX* botle = CObjectX::CObjectX::Create("BEERBOTTLE", D3DXVECTOR3(2300.0f + 70 * cont, 0.0f, -2500.0f), CObject::PRIORITY_LEVEL3);
		}

		for (int cont = 0; cont < 2; cont++)
		{
			CObjectX* cone = CObjectX::CObjectX::Create("CONE", D3DXVECTOR3(2100.0f + 240 * cont, 0.0f, -2200.0f - 150 * cont), CObject::PRIORITY_LEVEL3);
		}
		for (int cont = 0; cont < 2; cont++)
		{
			CObjectX* cone = CObjectX::CObjectX::Create("CONE", D3DXVECTOR3(1500.0f + 240 * cont, 0.0f, -2700.0f - 150 * cont), CObject::PRIORITY_LEVEL3);
		}
		for (int cont = 0; cont < 2; cont++)
		{
			CObjectX* cone = CObjectX::CObjectX::Create("CONE", D3DXVECTOR3(1700.0f, 0.0f, -3100.0f - 250 * cont), CObject::PRIORITY_LEVEL3);
		}
		for (int cont = 0; cont < 2; cont++)
		{
			CObjectX* cone = CObjectX::CObjectX::Create("CONE", D3DXVECTOR3(1700.0f - 250 * cont, 0.0f, -2200.0f), CObject::PRIORITY_LEVEL3);
		}
		for (int cont = 0; cont < 3; cont++)
		{
			CObjectX* cone = CObjectX::CObjectX::Create("CONE", D3DXVECTOR3(1250.0f - 220 * cont, 0.0f, -2600.0f), CObject::PRIORITY_LEVEL3);
		}

		CObjectX* cone = CObjectX::CObjectX::Create("CONE", D3DXVECTOR3(550, 0.0f, -2600.0f), CObject::PRIORITY_LEVEL3);

		for (int cont = 0; cont < 2; cont++)
		{
			CObjectX* cone = CObjectX::CObjectX::Create("CONE", D3DXVECTOR3(2100.0f + 240 * cont, 0.0f, -2200.0f), 3);
		}
		for (int cont = 0; cont < 2; cont++)
		{
			CObjectX* cone = CObjectX::CObjectX::Create("CONE", D3DXVECTOR3(1300.0f, 0.0f, -1400.0f + 240 * cont), 3);
		}
		for (int cont = 0; cont < 2; cont++)
		{
			CObjectX* beermug = CObjectX::CObjectX::Create("CONE", D3DXVECTOR3(1790.0f - 270 * cont, 0.0f, -750.0f - 220 * cont), CObject::PRIORITY_LEVEL3);
		}
		for (int cont = 0; cont < 3; cont++)
		{
			CObjectX* beermug = CObjectX::CObjectX::Create("CONE", D3DXVECTOR3(2450.0f, 0.0f, -1000.0f + 250 * cont), CObject::PRIORITY_LEVEL3);
		}
	}

	CObject2D* lifeui = CObject2D::Create("LIFE_UI", D3DXVECTOR3(150, 50, 0), D3DXVECTOR3(400, 200, 0), CObject::PRIORITY_LEVEL3);
	CObject2D* lifeBG = CObject2D::Create("CHABG", D3DXVECTOR3(150, 104, 0), D3DXVECTOR3(300, 80, 0), CObject::PRIORITY_LEVEL3);
	CMovelife::Create(D3DXVECTOR3(70, 100, 0), CObject::PRIORITY_LEVEL3);

	//タイムのUI
	m_pTime_Lope_Ui = CObject2D::Create("KEDAMA_Lope_UI", D3DXVECTOR3(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 90, 0.0f), D3DXVECTOR3(900.0f, 800.0f, 0.0f), CObject::PRIORITY_LEVEL4);
	m_pTimeUi = CObject2D::Create("KEDAMA_UI", D3DXVECTOR3(SCREEN_WIDTH - 80, SCREEN_HEIGHT - 90, 0.0f), D3DXVECTOR3(1500.0f, 1000.0f, 0.0f), CObject::PRIORITY_LEVEL4);
	m_Timer = CTimer::Create(D3DXVECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, 0), CObject::PRIORITY_LEVEL3);

	CSkyField::Create();

	//CLoadStage::LoadAllTest(0);

	CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_GAME);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame1::Uninit(void)
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
	
	CApplication::Getinstnce()->GetSound()->Stop(CSound::LABEL_GAME);
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame1::Update(void)
{
	// 入力処理用のポインタ宣言
	CInput *pInput = CApplication::Getinstnce()->GetInput();

	//if (m_pFade->GetFade() == CFade::FADE_NONE)
	//{
	//	if (pInput->Trigger(DIK_RETURN))
	//	{
	//		// 遷移
	//		CFade::SetFade(CApplication::MODE_RANKING);
	//	}
	//}

	//コンパス処理
	//{
	//	m_rot = CCamera::GetRot();
	//	m_rot.z = m_rot.y;
	//	if (pInput->Press(DIK_Q))
	//	{
	//		m_rot.z += 0.05f;
	//	}
	//	if (pInput->Press(DIK_E))
	//	{
	//		m_rot.z -= 0.05f;
	//	}
	//	m_rot.y *= -1;
	//	m_pCompass->SetRot(m_rot);
	//}
	//ゴールしたときのフラグ
	bool flg = CApplication::Getinstnce()->GetpMode()->GetGoal()->GetGoalFlg();
	if (flg)		//ゴールとプレイヤーが触れたら
	{
		CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_GOAL);
		goalui->SetCol(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f));
		returnflg = true;
	}
	if (!flg)
	{
		if (returnflg)
		{
			//移動削除
			m_pTime_Lope_Ui->SetMove(D3DXVECTOR3(0.0f, 0.f, 0.f));

			return;
		}
		//エフェクト
		m_particle2d = CParticle2D::Create("EFFECT", D3DXVECTOR3(SCREEN_WIDTH_HALF + 50, SCREEN_HEIGHT_HALF + 330, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CObject::PRIORITY_LEVEL4);
		Xslide += 0.11f;
		m_particle2d->SetPos(D3DXVECTOR3(SCREEN_WIDTH_HALF + 50 + Xslide, SCREEN_HEIGHT_HALF + 320, 0.0f));

		//時間を分かりやすくするために糸をずらしている
		m_pTime_Lope_Ui->SetMove(D3DXVECTOR3(0.11f, 0.f, 0.f));
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CGame1::Draw(void)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CGame1 * CGame1::Create()
{
	//ポインタ宣言
	CGame1 *pGame = nullptr;

	//インスタンス生成
	pGame = new CGame1;

	if (pGame != nullptr)
	{//ポインタが存在したら実行
		pGame->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pGame;
}