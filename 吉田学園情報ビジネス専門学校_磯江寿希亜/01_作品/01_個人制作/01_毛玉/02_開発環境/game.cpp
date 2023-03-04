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
#include "game.h"
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
#include "load_stage.h"

#include "movelife.h"
#include "Preparation.h"
#include "mode.h"
#include "Item.h"
#include "billboard.h"
#include "particle.h"
#include"Timer.h"
#include "Particle.h"
#include"2dParticle.h"
#include "sound.h"
#include "pause.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CMeshfield *CGame::m_pMeshField = nullptr;
CLight *CGame::m_pLight = nullptr;
CMovelife* CGame::pMovelife = nullptr;
CGoal* CGame::m_pGoal = nullptr;
CItem* CGame::m_pItem = nullptr;
CItem* CGame::m_pItemTimeUp = nullptr;
CItem* CGame::m_pItemTimeUp1 = nullptr;

CPause* CGame::pPause;

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	//ライトの生成
	m_pLight = CLight::Create();

	//ゲーム開始の合図
	m_pPreparation->Create("REDY", D3DXVECTOR3(SCREEN_WIDTH + 100, SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	{//初期化
		returnflg = false;
		Goalflg = false;
		m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}


	//モデル読み込み一番上に配置
	//	OutputStatus();

	//メッシュフィールドの生成
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-1500.0f, 0.0f, 1500.0f), CObject::PRIORITY_LEVEL3);
	m_pMeshField->LoadTexture("Data\\TEXTURE\\wood.png");

	//プレイヤーの生成
	CApplication::Getinstnce()->GetpMode()->SetPlayer(CPlayer::Create(D3DXVECTOR3(110.0f, 610.0f, -600.0f), CObject::PRIORITY_LEVEL3));
	CApplication::Getinstnce()->GetpMode()->GetPlayer()->LoadModel("Kedama");

	{//壁
		D3DXVECTOR3 WallSize(3050, 0.0f, 1000.0f);

		CObject3D* wallX = CObject3D::Create(D3DXVECTOR3(1300.0f, 700.0f, 1750.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), WallSize,3);
		wallX->LoadTexture("Data/TEXTURE/Background_6.png");

		CObject3D* wallX1 = CObject3D::Create(D3DXVECTOR3(1300.0f, 700.0f, -4300.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, D3DX_PI), WallSize, 3);
		wallX1->LoadTexture("Data/TEXTURE/Background_6.png");

		CObject3D* wallX2 = CObject3D::Create(D3DXVECTOR3(4300.0f, 700.0f, -1300.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, D3DX_PI / 2), WallSize, 3);
		wallX2->LoadTexture("Data/TEXTURE/Background_6.png");

		CObject3D* wallX3 = CObject3D::Create(D3DXVECTOR3(-1700.0f, 700.0f, -1300.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, -D3DX_PI / 2), WallSize, 3);
		wallX3->LoadTexture("Data/TEXTURE/Background_6.png");
	}

	//コンパス生成
	//m_pCompass = CObject2D::Create("COMPASS", D3DXVECTOR3(1140.0f, 120.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f), CObject::PRIORITY_LEVEL3);
	
	//タイムのUI
	m_pTime_Lope_Ui = CObject2D::Create("KEDAMA_Lope_UI", D3DXVECTOR3(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 90, 0.0f), D3DXVECTOR3(900.0f, 800.0f, 0.0f), CObject::PRIORITY_LEVEL4);
	m_pTimeUi = CObject2D::Create("KEDAMA_UI", D3DXVECTOR3(SCREEN_WIDTH-80, SCREEN_HEIGHT-90, 0.0f), D3DXVECTOR3(1500.0f, 1000.0f, 0.0f), CObject::PRIORITY_LEVEL4);
	m_Timer = CTimer::Create(D3DXVECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, 0),3);

	//スコア
	//CApplication::Getinstnce()->GetpMode()->SetScore(CScore::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f)));


	//CLoadStage::LoadAllTest(0);

	goalui = CObject3D::Create(D3DXVECTOR3(1890.0f, 1000.0f, -2300.0f), D3DXVECTOR3(0.f,0.f,0.f), D3DXVECTOR3(350, 350.0f, 0.0f), CObject::PRIORITY_LEVEL4);
	goalui->LoadTexture("Data/TEXTURE/GOALUI.png");//1890.0f, 605.0f, -2300.0f
	goalui->SetBillboard(true);

	m_pGoal = CGoal::Create(D3DXVECTOR3(1890.0f, 605.0f, -2300.0f), CObject::PRIORITY_LEVEL4);
	m_pGoal->LoadModel("BSKET");	//1890.0f, 605.0f, -2300.0f
	m_pGoal->Setstring("GOAL");

	m_pItem = CItem::Create(D3DXVECTOR3(560.0f, 605.0f, -1400.0f), CObject::PRIORITY_LEVEL3, CItem::ITEM_MOVE_SPEED_UP);	//ITEM_MOVELIFE_UP  ITEM_MOVE_SPEED_UP ITEM_SCORE_UP
	m_pItem->LoadModel("BOOTS");

	m_pItemTimeUp = CItem::Create(D3DXVECTOR3(560.0f, 605.0f, -660.0f), CObject::PRIORITY_LEVEL3, CItem::ITEM_GAMETIME_UP);	//ITEM_GAMETIME_UP  ITEM_MOVE_SPEED_UP ITEM_SCORE_UP
	m_pItemTimeUp->LoadModel("ITEMTIME");

	m_pItemTimeUp1 = CItem::Create(D3DXVECTOR3(1900.0f, 605.0f, -1010.0f), CObject::PRIORITY_LEVEL3, CItem::ITEM_GAMETIME_UP);	//ITEM_GAMETIME_UP  ITEM_MOVE_SPEED_UP ITEM_SCORE_UP
	m_pItemTimeUp1->LoadModel("ITEMTIME");

	CObjectX* i[9];
	//必須
	 i[0]= CObjectX::Create("CHAIR", D3DXVECTOR3(-500.0f, 0.0f, -1500.0f),  CObject::PRIORITY_LEVEL3);
	 i[1] = CObjectX::Create("CHAIR", D3DXVECTOR3(2300.0f, 0.0f, -1500.0f), CObject::PRIORITY_LEVEL3);
	 i[2] = CObjectX::Create("CHAIR", D3DXVECTOR3(1000.0f, 0.0f, -3000.0f), CObject::PRIORITY_LEVEL3);
	 i[3] = CObjectX::Create("CHAIR", D3DXVECTOR3(1000.0f, 0.0f, -200.0f),  CObject::PRIORITY_LEVEL3);
	 i[4] = CObjectX::Create("DOOR", D3DXVECTOR3(-1150.0f, 0.0f, 1700.0f),  CObject::PRIORITY_LEVEL3);
	 i[5] = CObjectX::Create("TABLE", D3DXVECTOR3(1000.0f, 0.0f, -1500.0f), CObject::PRIORITY_LEVEL3);
	 //--------
	 i[6] = CObjectX::Create("BOOKSHELF", D3DXVECTOR3(-1500.0f, 0.0f, -3700.0f), CObject::PRIORITY_LEVEL3);
	 i[6]->SetRot(D3DXVECTOR3(0.f,-1.5707963705062866f,0.f));

	 i[7] = CObjectX::Create("CHEST", D3DXVECTOR3(4000.0f, 0.0f, -3700.0f), CObject::PRIORITY_LEVEL3);
	 i[7]->SetRot(D3DXVECTOR3(0.f, 1.5707963705062866f, 0.f));

	 i[8] = CObjectX::Create("SCISSORS", D3DXVECTOR3(1100.0f, 600.0f, -1500.0f), CObject::PRIORITY_LEVEL3);

	// SCISSORS

	 for (int Cnt = 0;Cnt <3;Cnt++)
	 {
		 CObjectX* n = CObjectX::Create("CUP", D3DXVECTOR3(320.0f, 600.0f, -550.0f - 100 *Cnt ), CObject::PRIORITY_LEVEL3);
	 }
	 for (int Cnt = 0; Cnt <10; Cnt++)
	 {
		 CObjectX* v = CObjectX::Create("CUP", D3DXVECTOR3(320.0f + 100 * Cnt, 600.0f, -850.0f), CObject::PRIORITY_LEVEL3);
	 }
	 for (int Cnt = 0; Cnt <9; Cnt++)
	 {
		 CObjectX* z = CObjectX::Create("BOTTLE", D3DXVECTOR3(320.0f, 600.0f, -1200.0f - 100 * Cnt), CObject::PRIORITY_LEVEL3);
	 }
	 for (int Cnt = 0; Cnt <5; Cnt++)
	 {
		 CObjectX* x = CObjectX::Create("BOTTLE", D3DXVECTOR3(320.0f + 100 * Cnt, 600.0f, -1200.0f), CObject::PRIORITY_LEVEL3);
	 }
	 for (int Cnt = 0; Cnt <13; Cnt++)
	 {
		 CObjectX* x = CObjectX::Create("BOTTLE", D3DXVECTOR3(820.0f, 600.0f, -1200.0f - 90 * Cnt), CObject::PRIORITY_LEVEL3);
	 }
	 for (int Cnt = 0; Cnt <15; Cnt++)
	 {
		 CObjectX* x = CObjectX::Create("BOTTLE", D3DXVECTOR3(1450.0f, 600.0f, -830.0f - 100 * Cnt), CObject::PRIORITY_LEVEL3);
	 }
	 for (int Cnt = 0; Cnt <4; Cnt++)
	 {
		 CObjectX* x = CObjectX::Create("BEERBOTTLE", D3DXVECTOR3(1520.0f + 100 * Cnt, 600.0f, -1830.0f), CObject::PRIORITY_LEVEL3);
	 }
	 for (int Cnt = 0; Cnt <4; Cnt++)
	 {
		 CObjectX* x = CObjectX::Create("BEERMUG", D3DXVECTOR3(1350.0f - 100 * Cnt, 600.0f, -1830.0f), CObject::PRIORITY_LEVEL3);
	 }
	 for (int Cnt = 0; Cnt <5; Cnt++)
	 {
		 CObjectX* x = CObjectX::Create("BOTTLE1", D3DXVECTOR3(1050.0f , 600.0f, -2450.0f + 90 * Cnt), CObject::PRIORITY_LEVEL3);
	 }
	 for (int Cnt = 0; Cnt <5; Cnt++)
	 {
		 CObjectX* x = CObjectX::Create("BOTTLE", D3DXVECTOR3(1700.0f, 600.0f, -2450.0f + 100 * Cnt), CObject::PRIORITY_LEVEL3);
	 }
	 for (int Cnt = 0; Cnt <4; Cnt++)
	 {
		 CObjectX* x = CObjectX::Create("BOTTLE", D3DXVECTOR3(2000.0f - 100 * Cnt, 600.0f, -830.0f), CObject::PRIORITY_LEVEL3);
	 }
	 for (int Cnt = 0; Cnt <6; Cnt++)
	 {
		 CObjectX* x = CObjectX::Create("BOTTLE", D3DXVECTOR3(1700.0f, 600.0f, -930.0f - 100 * Cnt), CObject::PRIORITY_LEVEL3);
	 }
	 for (int Cnt = 0; Cnt <2; Cnt++)
	 {
		 CObjectX* x = CObjectX::Create("TEAPOT", D3DXVECTOR3(2000.0f - 200 * Cnt, 600.0f, -1630.0f), CObject::PRIORITY_LEVEL3);
		 x->SetRot(D3DXVECTOR3(0.0f,45.0f + 50 * Cnt,0.0f));
	 }

	//CObjectX* obje= CObjectX::Create("BOTTLE",D3DXVECTOR3(700,605,-880),3);
	//CObjectX* obje1 = CObjectX::Create("BOTTLE", D3DXVECTOR3(400, 605, -880), 3);

	/*for (int Cnt = 0; Cnt < 4; Cnt++)
	{
		CObjectX* obje2 = CObjectX::Create("BOTTLE", D3DXVECTOR3(300, 605, -880 +100 * Cnt), 3);
	}
	for (int Cnt = 0; Cnt < 3; Cnt++)
	{
		CObjectX* obje3 = CObjectX::Create("BOTTLE", D3DXVECTOR3(790 + 100 * Cnt, 605, -880), 3);
	}
	for (int Cnt = 0; Cnt < 5; Cnt++)
	{
		CObjectX* obje4 = CObjectX::Create("BEERBOTTLE", D3DXVECTOR3(200 + 100 * Cnt, 605, -1480), 3);
	}
	for (int Cnt = 0; Cnt < 6; Cnt++)
	{
		CObjectX* obje5 = CObjectX::Create("BEERBOTTLE", D3DXVECTOR3(600 , 605, -1600 - 100 * Cnt), 3);
	}
	for (int Cnt = 0; Cnt < 3; Cnt++)
	{
		CObjectX* obje5 = CObjectX::Create("TEAPOT", D3DXVECTOR3(1200 + 150 * Cnt, 605, -1400 ), 3);
	}
	for (int Cnt = 0; Cnt < 3; Cnt++)
	{
		CObjectX* obje6 = CObjectX::Create("HOURGLASS", D3DXVECTOR3(1642 + 100 * Cnt, 605, -2000), 3);
	}
	for (int Cnt = 0; Cnt < 3; Cnt++)
	{
		CObjectX* obje6 = CObjectX::Create("TEAPOT", D3DXVECTOR3(1625, 605, -700 - 200 * Cnt), 3);
		obje6->SetRot(D3DXVECTOR3(0.0f,0.0f + 300 * Cnt,0.0f));
	}*/

	//CObject3D* i = CObject3D::Create(D3DXVECTOR3(110.0f, 610.0f, -600.0f), D3DXVECTOR3(0.f,0.f,0.f), D3DXVECTOR3(150, 150.0f, 0.0f), CObject::PRIORITY_LEVEL3);
	//i->LoadTexture("Data/TEXTURE/01.png");//-D3DX_PI / 2.0f, 0.0f, D3DX_PI
	//i->SetBillboard(true);

	//Load();
	//CLoadStage::SaveAll();

	//CBillboard* bill = CBillboard::Create("EFFECT", D3DXVECTOR3(110.0f, 610.0f, -600.0f), CObject::PRIORITY_LEVEL4);

	//
	CObject2D* lifeui = CObject2D::Create("LIFE_UI", D3DXVECTOR3(150, 50, 0), D3DXVECTOR3(400, 200, 0),CObject::PRIORITY_LEVEL3);
	CObject2D* lifeBG = CObject2D::Create("CHABG", D3DXVECTOR3(150, 104, 0), D3DXVECTOR3(300, 80, 0), CObject::PRIORITY_LEVEL3);
	m_Movelife->Create(D3DXVECTOR3(70, 100, 0), CObject::PRIORITY_LEVEL3);

	pPause = CPause::Create("INIESUTA", D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f), D3DXVECTOR3((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2, 0.0f), CObject::PRIORITY_LEVEL4);

	CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_GAME);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
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
void CGame::Update(void)
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

	bool goalflg = CMode::GetGoal()->GetGoalFlg();
	if (goalflg)
	{
		CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_GOAL);
		goalui->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		Goalflg = true;
	}
	if (Goalflg)
	{
		GoalCnt++;
	}
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
void CGame::Draw(void)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CGame * CGame::Create()
{
	//ポインタ宣言
	CGame *pGame = nullptr;

	//インスタンス生成
	pGame = new CGame;

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