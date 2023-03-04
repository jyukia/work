//=============================================================================
// インクルードファイル
//=============================================================================
#include <stdio.h>
#include "application.h"
#include "fade.h"
#include "input.h"
#include "ranking.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "load_stage.h"
#include "light.h"
#include "goal.h"
#include "player.h"
#include "meshfield.h"
#include "object3D.h"
#include"Number.h"
#include"movelife.h"
#include "Meshline.h"
#include "inputjoypad.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
//CNumber *CRanking::m_apNumber[MAX_RANKINGRANK][MAX_RANKING] = {};

CMovelife *CRanking::m_pMovelife[MAX_RANKING] = {};
CMovelife *CRanking::m_pMovelife1[MAX_RANKING] = {};

int CRanking::aData[MAX_RANKINGRANK] = {};
int CRanking::bData[MAX_RANKINGRANK] = {};

int CRanking::m_nRanking = 0;
int CRanking::m_nRanking1 = 0;
CLight *CRanking::m_pLight = nullptr;
CGoal* CRanking::m_pGoal = nullptr;
CMeshfield *CRanking::m_pMeshField = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CRanking::CRanking(): m_bmodeflg(false)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRanking::Init(void)
{
	//ファイル書き出し処理
	Save();
	Save1();


	//ライトの生成
	m_pLight = CLight::Create();

	{//初期化
		m_bmodeflg = false;
	}

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//タイトル配置
	//m_pObject2D[0] = CObject2D::Create("RANKING", D3DXVECTOR3(1280.0f / 2, -20.0f, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f), PRIORITY_LEVEL0);

	//プレイヤーの生成
	CApplication::Getinstnce()->GetpMode()->SetPlayer(CPlayer::Create(D3DXVECTOR3(1100.0f, 610.0f, -2600.0f), CObject::PRIORITY_LEVEL3));
	CApplication::Getinstnce()->GetpMode()->GetPlayer()->LoadModel("Kedama");

	//メッシュフィールドの生成
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-1500.0f, 0.0f, 1500.0f), CObject::PRIORITY_LEVEL3);
	m_pMeshField->LoadTexture("Data\\TEXTURE\\wood.png");

	CObject2D* stagename = CObject2D::Create("STAGENAME1", D3DXVECTOR3(SCREEN_WIDTH / 2 - 300, 160, 0.0f), D3DXVECTOR3(500, 450, 0), CObject::PRIORITY_LEVEL4);	//背景
	CObject2D* stagename1 = CObject2D::Create("STAGENAME", D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, 160, 0.0f), D3DXVECTOR3(500, 450, 0), CObject::PRIORITY_LEVEL4);	//背景

	CObject2D* bg = CObject2D::Create("RANKINGBG", D3DXVECTOR3(SCREEN_WIDTH / 2 - 300, 420, 0.0f), D3DXVECTOR3(500, 450, 0), CObject::PRIORITY_LEVEL4);//背景
	CObject2D* bg1 = CObject2D::Create("RANKINGBG", D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, 420, 0.0f), D3DXVECTOR3(500, 450, 0), CObject::PRIORITY_LEVEL4);//背景
	CObject2D* bg2 = CObject2D::Create("RANKING_UI_BG", D3DXVECTOR3(SCREEN_WIDTH / 2, 50, 0.0f), D3DXVECTOR3(1000, 700, 0), CObject::PRIORITY_LEVEL4);//背景

	CObject2D* rankingbg = CObject2D::Create("RANKING_UI", D3DXVECTOR3(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 + 50, 0.0f), D3DXVECTOR3(600, 550, 0), CObject::PRIORITY_LEVEL4);	//背景
	CObject2D* rankingbg1 = CObject2D::Create("RANKING_UI", D3DXVECTOR3(SCREEN_WIDTH / 2 +100, SCREEN_HEIGHT / 2 + 50, 0.0f), D3DXVECTOR3(600, 550, 0), CObject::PRIORITY_LEVEL4);	//背景

	for (int Cnt = 0; Cnt < MAX_RANKING; Cnt++)
	{
		m_pMovelife[Cnt] = nullptr;
		m_pMovelife[Cnt] = CMovelife::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 +200, 250 + 70.0f* Cnt, 0.0f), CObject::PRIORITY_LEVEL4);
	}
	for (int Cnt = 0; Cnt < MAX_RANKING; Cnt++)
	{
		m_pMovelife1[Cnt] = nullptr;
		m_pMovelife1[Cnt] = CMovelife::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 400, 250 + 70.0f* Cnt, 0.0f), CObject::PRIORITY_LEVEL4);
	}

	CObject2D* UI_B = CObject2D::Create("B", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 480, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);
	CObject2D* UI_BG1 = CObject2D::Create("CHABG", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 550, 670.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), PRIORITY_LEVEL4);
	CObject2D* UI_Modoru = CObject2D::Create("MODORU", D3DXVECTOR3((float)SCREEN_WIDTH_HALF + 550, 670.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), PRIORITY_LEVEL4);

	{//壁
		D3DXVECTOR3 WallSize(3050, 0.0f, 1000.0f);

		CObject3D* wallX = CObject3D::Create(D3DXVECTOR3(1300.0f, 700.0f, 1750.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), WallSize, 3);
		wallX->LoadTexture("Data/TEXTURE/Background_6.png");

		CObject3D* wallX1 = CObject3D::Create(D3DXVECTOR3(1300.0f, 700.0f, -4300.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, D3DX_PI), WallSize, 3);
		wallX1->LoadTexture("Data/TEXTURE/Background_6.png");

		CObject3D* wallX2 = CObject3D::Create(D3DXVECTOR3(4300.0f, 700.0f, -1300.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, D3DX_PI / 2), WallSize, 3);
		wallX2->LoadTexture("Data/TEXTURE/Background_6.png");

		CObject3D* wallX3 = CObject3D::Create(D3DXVECTOR3(-1700.0f, 700.0f, -1300.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, -D3DX_PI / 2), WallSize, 3);
		wallX3->LoadTexture("Data/TEXTURE/Background_6.png");
	}

	//タイトル画像(仮)の生成
	//CObject2D* test = CObject2D::Create("INIESUTA", D3DXVECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(700.0f, 500.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_RESULT);


	//ファイル読み込み処理
	CLoadStage::LoadAllTest(0);

	//ファイル読み込み処理
	Load();
	Load1();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	//インスタンスの解放処理
	CObject::Release();

	CApplication::Getinstnce()->GetSound()->Stop(CSound::LABEL_RESULT);
}

//=============================================================================
// 更新処理
//=============================================================================
void CRanking::Update(void)
{
	//入力処理用のポインタ宣言
	CInput *pInput = CApplication::Getinstnce()->GetInput();
	//コントローラー
	CInputJoyPad *pJoy = CApplication::GetJoy();

	if (!m_bmodeflg)
	{
		if (pInput->Trigger(DIK_RETURN))
		{
			m_bmodeflg = true;
		}
	}
	if (pInput->Trigger(DIK_RETURN) || pJoy->GetPress(DirectJoypad::JOYPAD_B, 0) && m_pFade->GetFade() == CFade::FADE_NONE)
	{// ENTERキーが押されたら実行
		if (m_pFade->GetFade() == CFade::FADE_NONE)
		{
			//モード設定
			CFade::SetFade(CApplication::MODE_TITLE);
		}
		CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_SELECT);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CRanking::Draw(void)
{
}

//=============================================================================
// ファイル読み込み処理
//=============================================================================
void CRanking::Load(void)
{
	//ファイルポインタ宣言
	FILE*pFile;

	//ファイルを開く
	pFile = fopen("Data\\SAVE\\ranking.txt", "r");

	if (pFile != NULL)
	{//ファイルが開けた場合
		for (int nCntData = 0; nCntData < MAX_RANKINGRANK; nCntData++)
		{
			//ファイルに数値を書き出す
			fscanf(pFile, "%d\n", &aData[nCntData]);

			m_pMovelife[nCntData]->Setlife(aData[nCntData]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開かなかった場合
		printf("***ファイルが開けませんでした***");
	}
}

//=============================================================================
// ファイル書き出し処理
//=============================================================================
void CRanking::Save(void)
{
	//ファイルポインタ宣言
	FILE*pFile;

	//ファイルを開く
	pFile = fopen("data\\ranking.txt", "w");

	if (pFile != NULL)
	{//ファイルが開けた場合
		for (int nCnt = 0; nCnt < MAX_RANKINGRANK; nCnt++)
		{
			//ファイルに数値を書き出す
			fprintf(pFile, "%d\n", aData[nCnt]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開かなかった場合
		printf("***ファイルが開けませんでした***");
	}
}

void CRanking::Load1(void)
{
	//ファイルポインタ宣言
	FILE*pFile;

	//ファイルを開く
	pFile = fopen("Data\\SAVE\\ranking1.txt", "r");

	if (pFile != NULL)
	{//ファイルが開けた場合
		for (int nCntData = 0; nCntData < MAX_RANKINGRANK; nCntData++)
		{
			//ファイルに数値を書き出す
			fscanf(pFile, "%d\n", &bData[nCntData]);

			m_pMovelife1[nCntData]->Setlife(bData[nCntData]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開かなかった場合
		printf("***ファイルが開けませんでした***");
	}

}

void CRanking::Save1(void)
{
	//ファイルポインタ宣言
	FILE*pFile;

	//ファイルを開く
	pFile = fopen("data\\ranking1.txt", "w");

	if (pFile != NULL)
	{//ファイルが開けた場合
		for (int nCnt = 0; nCnt < MAX_RANKINGRANK; nCnt++)
		{
			//ファイルに数値を書き出す
			fprintf(pFile, "%d\n", bData[nCnt]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開かなかった場合
		printf("***ファイルが開けませんでした***");
	}
}

//=============================================================================
// スコアの設定処理
//=============================================================================
void CRanking::SetRankingScore()
{
	if (m_nRanking > aData[MAX_RANKINGRANK - 1])
	{
		aData[MAX_RANKINGRANK - 1] = m_nRanking;
	}

	for (int nCount = 0; nCount < MAX_RANKINGRANK - 1; nCount++)
	{
		for (int nCount2 = nCount + 1; nCount2 < MAX_RANKINGRANK; nCount2++)
		{
			if (aData[nCount] < aData[nCount2])
			{
				int nMin = aData[nCount];
				aData[nCount] = aData[nCount2];
				aData[nCount2] = nMin;
			}
		}
	}
	//for (int nCntScore = 0; nCntScore < MAX_RANKINGRANK; nCntScore++)
	//{
	//	aPosTexU[nCntScore][0] = aData[nCntScore] % 100000 / 10000;
	//	aPosTexU[nCntScore][1] = aData[nCntScore] % 10000 / 1000;
	//	aPosTexU[nCntScore][2] = aData[nCntScore] % 1000 / 100;
	//	aPosTexU[nCntScore][3] = aData[nCntScore] % 100 / 10;
	//	aPosTexU[nCntScore][4] = aData[nCntScore] % 10 / 1;
	//}
	////テクスチャ座標の設定
	//for (int nCnt = 0; nCnt < MAX_RANKINGRANK; nCnt++)
	//{
	//	for (int nCntScore = 0; nCntScore < MAX_RANKING; nCntScore++)
	//	{
	//		float fShiftWidth = 1.0f / 10;
	//		//m_apNumber[nCnt][nCntScore]->SetUV((float)aPosTexU[nCnt][nCntScore] * fShiftWidth, (fShiftWidth + (float)aPosTexU[nCnt][nCntScore] * fShiftWidth), 0.0f, 1.0f);
	//	}
	//}
}
//=============================================================================
// 情報の取得
//=============================================================================
void CRanking::GetRanking(int Ranking)
{
	m_nRanking = Ranking;
}
void CRanking::SetRankingScore1()
{

	if (m_nRanking1 > bData[MAX_RANKINGRANK - 1])
	{
		bData[MAX_RANKINGRANK - 1] = m_nRanking1;
	}

	for (int nCount = 0; nCount < MAX_RANKINGRANK - 1; nCount++)
	{
		for (int nCount2 = nCount + 1; nCount2 < MAX_RANKINGRANK; nCount2++)
		{
			if (bData[nCount] < bData[nCount2])
			{
				int nMin = bData[nCount];
				bData[nCount] = bData[nCount2];
				bData[nCount2] = nMin;
			}
		}
	}
}
void CRanking::GetRanking1(int Ranking)
{
	m_nRanking1 = Ranking;
}

//=============================================================================
// 生成処理
//=============================================================================
CRanking * CRanking::Create()
{
	CRanking *pRanking = new CRanking;

	if (pRanking != nullptr)
	{
		SetRankingScore();	//数値の整列
		SetRankingScore1();
		pRanking->Init();

	}

	return pRanking;
}
