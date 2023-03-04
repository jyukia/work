//=============================================================================
//
// timer.cpp
// Author : 磯江寿希亜
//
//=============================================================================
//*****************************************************************************
// インクルードファイル
//*****************************************************************************

#include "Timer.h"
#include"input.h"
#include "mode.h"
#include"Meshline.h"
#include"player.h"
#include "fade.h"
#include "goal.h"
#include "sound.h"
#include"Timer.h"
#include "application.h"
#include "Item.h"

CFade *m_pFadeTime;

//コンストラクタ
CTimer::CTimer(int nPriority)
{
}
//デストラクタ
CTimer::~CTimer()
{
}
//-----------------------------------------
//初期化
//-----------------------------------------
HRESULT CTimer::Init()
{
	returnflg = false;

	for (int numberCnt = 0; numberCnt <2; numberCnt++)
	{//
		pNumber[numberCnt] = CNumber::Create("NUMBER", D3DXVECTOR3(SCREEN_WIDTH - 90 + numberCnt *50.0f, SCREEN_HEIGHT - 90, 0.0f), D3DXVECTOR3(65.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);
	}

	Setlife(60);

	return S_OK;
}
//-----------------------------------------
//終了
//-----------------------------------------
void CTimer::Uninit()
{
}
//-----------------------------------------
//更新
//-----------------------------------------
void CTimer::Update()
{
	D3DXVECTOR3 pos = CObject2D::GetPos();

	//// キーボードの情報取得
	//CInput *pInputKeyboard = CApplication::Getinstnce()->GetInput();

	//if (pInputKeyboard->Press(DIK_T))
	//{// 下に移動
	//}

	bool bflg =CItem::GetSizdownflg();	//フラグを取得時間を増やす
	if (bflg)	
	{
			Addlife(5);
			CItem::SetSizdownflg(false);
	}

	bool flg = CApplication::Getinstnce()->GetpMode()->GetGoal()->GetGoalFlg();
	if (flg)		//ゴールとプレイヤーが触れたら
	{
		returnflg = true;
	}
	else			//触れいていないとき
	{
		bool flg = CApplication::Getinstnce()->GetpMode()->GetPlayer()->Getbredycheck();
		if (flg)
		{
			if (returnflg)
			{
				return;
			}
			TimeCnt++;
			//１秒経ったら
			if (TimeCnt >= 60)
			{
				TimeCnt = 0;
				//減る処理
				Sublife(1);
			}
		}
	}
	CObject2D::SetPos(pos);
}
//-----------------------------------------
//描画
//-----------------------------------------
void CTimer::Draw()
{
}
//加算処理
void CTimer::Addlife(int nGain)
{
	int aPosTexU[2];	//各桁の数字を格納

	m_Time += nGain;

	aPosTexU[0] = m_Time % 100 / 10;
	aPosTexU[1] = m_Time % 10 / 1;

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//テクスチャ設定
		pNumber[nCount]->ScoreVtx
		(0.1f * aPosTexU[nCount],
			0.0f,
			0.1f * aPosTexU[nCount] + 0.1f,
			1.0f);
	}
}
//減算処理
void CTimer::Sublife(int nDecrease)
{
	int aPosTexU[2];	//各桁の数字を格納

	m_Time -= nDecrease;


	if (m_Time <= 0)
	{//0以下だったら
		m_Time = 0;
		flg = false;

		CApplication::Getinstnce()->GetSound()->Stop(CSound::LABEL_GAME);

		if (m_pFadeTime->GetFade() == CFade::FADE_NONE)
		{
			// 遷移
			CFade::SetFade(CApplication::MODE_RANKING);
		}

		//移動出来ないようにする
		CApplication::Getinstnce()->GetpMode()->GetPlayer()->Setbredycheck(flg);
	}

	aPosTexU[0] = m_Time % 100 / 10;
	aPosTexU[1] = m_Time % 10 / 1;

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//テクスチャ設定
		pNumber[nCount]->ScoreVtx
		(0.1f * aPosTexU[nCount],
			0.0f,
			0.1f * aPosTexU[nCount] + 0.1f,
			1.0f);
	}
}
//スコア設定処理
void CTimer::Setlife(int nLife)
{
	int aPosTexU[2];	//各桁の数字を格納

	m_Time = nLife;

	aPosTexU[0] = m_Time % 100 / 10;
	aPosTexU[1] = m_Time % 10 / 1;

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//テクスチャ設定
		pNumber[nCount]->ScoreVtx
		(0.1f * aPosTexU[nCount],
			0.0f,
			0.1f * aPosTexU[nCount] + 0.1f,
			1.0f);
	}
}

CTimer * CTimer::Create(D3DXVECTOR3 pos, int nPriority)
{
	CTimer* pTime = nullptr;
	//動的確保
	pTime = new CTimer(nPriority);

	if (pTime != nullptr)
	{
		pTime->Init();

		//位置情報
		pTime->SetPos(pos);

	}
	else
	{//処理を止める
		assert(false);
	}

	return pTime;
}
