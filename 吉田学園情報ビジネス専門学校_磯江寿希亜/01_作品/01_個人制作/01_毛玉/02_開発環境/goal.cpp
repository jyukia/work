#include <assert.h>
#include "application.h"
#include "goal.h"
#include "shadow.h"
#include "game.h"
#include"DebugProc.h"
#include "player.h"
#include "fade.h"
#include "Particle.h"

bool CGoal::GoalFlg;
bool CGoal::flg;

CFade *m_pFade;

CGoal::CGoal(int nPriority)
{

}

CGoal::~CGoal()
{
}

HRESULT CGoal::Init()
{	
	{
		Cnt = 0;
		flg = false;
	}
	//objectxのposとrot
	D3DXVECTOR3 pos = CObjectX::GetPos();

	D3DXVECTOR3 size = CObjectX::GetSize();

	D3DXVECTOR3 rot = CObjectX::GetRot();

	//オブジェクトの初期化
	CObjectX::Init();

	//影の生成
	CShadow::Create(pos, size, CObject::PRIORITY_LEVEL3);

	Goal = CObject2D::Create("GOALUI", D3DXVECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), PRIORITY_LEVEL4);
	Goal->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	return S_OK;
}

void CGoal::Update()
{
	if (CApplication::Getinstnce()->GetpMode()->GetPlayer() != nullptr)
	{
		//プレイヤー情報
		D3DXVECTOR3 pPlayerPos = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetPos();
		D3DXVECTOR3 pPlayerPosOld = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetPosOld();
		D3DXVECTOR3 pSize = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetSize();
		// 座標取得
		D3DXVECTOR3 pos = GetPos();

		//ゴール表示の為のパーティクル
		//CParticle* particle = CParticle::Create("Data/TEXTURE/effect000.jpg", D3DXVECTOR3(pos), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CObject::PRIORITY_LEVEL3);
		//particle->SetBillboard(true);

		// ポインタ宣言
		CObject *pObject = CObject::GetTop(PRIORITY_LEVEL3);
		// プレイヤーとモデルの当たり判定
		while (pObject != nullptr)
		{
			if (pObject == this)
			{
				pObject = pObject->GetNext();
				continue;
			}
			//変数宣言
			CObject::EObjType objType;

			//オブジェクトのタイプを取得
			objType = pObject->GetObjType();

			if (objType == OBJTYPE_PLAYER)	//接触がプレイヤーの時
			{
				CObjectX *pObjectX = (CObjectX*)pObject;

				D3DXVECTOR3 size = 	D3DXVECTOR3(200,100,200);
				GoalFlg = Collision(&pPlayerPos, &pPlayerPosOld, &size, false);
			}
			//ポインタを次に進める
			pObject = pObject->GetNext();
		}
		//ゴールとプレイヤーが触れたら
		if (GoalFlg)
		{
			flg = true;
		}
	}
	if (flg)	//ゴールとプレイヤーが触れたら
	{
		Goal->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		Cnt++;
		if (Cnt >= 480)
		{
			if (m_pFade->GetFade() == CFade::FADE_NONE)
			{
				// 遷移
				CFade::SetFade(CApplication::MODE_RANKING);
			}
		}
		if (Cnt >= 720)
		{
			flg = false;
		}

		CDebugProc::Print("\n GOAL %d", Cnt);
	}
}
//=============================================================================
// 当たり判定 (左右,奥,手前)
//=============================================================================
bool CGoal::Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize, bool bQuaternion)
{
	// 変数宣言
	bool bIsLanding = false;

	// 座標取得
	D3DXVECTOR3 pos = GetPos();

	D3DXVECTOR3 Min = GetMinVtx();
	
	D3DXVECTOR3 Max = GetMaxVtx();

	if (bQuaternion)
	{
		// モデルの左側当たり判定(クォータニオンVer)
		if ((pPos->z - pSize->z / 2.0f < pos.z + Max.z) &&
			(pPos->z + pSize->z / 2.0f > pos.z + Min.z) &&
			(pPosOld->x + pSize->x / 2.0f <= pos.x + Min.x) &&
			(pPos->x + pSize->x / 2.0f > pos.x + Min.x) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->x = pos.x + Min.x - (pSize->x / 2.0f);
		}
		// モデルの右側当たり判定(クォータニオンVer)
		if ((pPos->z - pSize->z / 2.0f < pos.z + Max.z) &&
			(pPos->z + pSize->z / 2.0f > pos.z + Min.z) &&
			(pPosOld->x - pSize->x / 2.0f >= pos.x + Max.x) &&
			(pPos->x - pSize->x / 2.0f < pos.x + Max.x) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->x = pos.x + Max.x + (pSize->x / 2.0f);
		}
		// モデルの奥側当たり判定(クォータニオンVer)
		if ((pPos->x - pSize->x / 2.0f < pos.x + Max.x) &&
			(pPos->x + pSize->x / 2.0f > pos.x + Min.x) &&
			(pPosOld->z - pSize->z / 2.0f >= pos.z + Max.z) &&
			(pPos->z - pSize->z / 2.0f < pos.z + Max.z) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->z = pos.z + Max.z + (pSize->z / 2.0f);
		}
		// モデルの手前側当たり判定(クォータニオンVer)
		if ((pPos->x - pSize->x / 2.0f < pos.x + Max.x) &&
			(pPos->x + pSize->x / 2.0f > pos.x + Min.x) &&
			(pPosOld->z + pSize->z / 2.0f <= pos.z + Min.z) &&
			(pPos->z + pSize->z / 2.0f > pos.z + Min.z) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->z = pos.z + Min.z - (pSize->z / 2.0f);
		}
	}
	else
	{
		// モデルの左側当たり判定
		if ((pPos->z - pSize->z / 2.0f < pos.z + Max.z) &&
			(pPos->z + pSize->z / 2.0f > pos.z + Min.z) &&
			(pPosOld->x + pSize->x / 2.0f <= pos.x + Min.x / 2.0f) &&
			(pPos->x + pSize->x / 2.0f > pos.x + Min.x / 2.0f) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->x = pos.x + Min.x / 2.0f - pSize->x / 2.0f;
		}
		// モデルの右側当たり判定
		if ((pPos->z - pSize->z / 2.0f < pos.z + Max.z) &&
			(pPos->z + pSize->z / 2.0f > pos.z + Min.z) &&
			(pPosOld->x - pSize->x / 2.0f >= pos.x + Max.x / 2.0f) &&
			(pPos->x - pSize->x / 2.0f < pos.x + Max.x / 2.0f) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->x = pos.x + Max.x / 2.0f + pSize->x / 2.0f;
		}
		// モデルの奥側当たり判定
		if ((pPos->x - pSize->x / 2.0f < pos.x + Max.x) &&
			(pPos->x + pSize->x / 2.0f > pos.x + Min.x) &&
			(pPosOld->z - pSize->z / 2.0f >= pos.z + Max.z / 2.0f) &&
			(pPos->z - pSize->z / 2.0f < pos.z + Max.z / 2.0f) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->z = pos.z + Max.z / 2.0f + pSize->z / 2.0f;
		}
		// モデルの手前側当たり判定
		if ((pPos->x - pSize->x / 2.0f < pos.x + Max.x) &&
			(pPos->x + pSize->x / 2.0f > pos.x + Min.x) &&
			(pPosOld->z + pSize->z / 2.0f <= pos.z + Min.z / 2.0f) &&
			(pPos->z + pSize->z / 2.0f > pos.z + Min.z / 2.0f) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->z = pos.z + Min.z / 2.0f - pSize->z / 2.0f;
		}
	}

	// 値を返す
	return bIsLanding;
}
//=============================================================================
// 生成処理
//=============================================================================
CGoal * CGoal::Create(const D3DXVECTOR3 pos, int nPriority)
{
	CGoal *pGoal = new CGoal(nPriority);

	if (pGoal != nullptr)
	{
		pGoal->Init();
		pGoal->SetPos(pos);
		pGoal->m_shadow = CShadow::Create(D3DXVECTOR3(pos.x, 0.5f, pos.z), D3DXVECTOR3(10.0f, 0.0f, 10.0f), CObject::PRIORITY_LEVEL3);
		//pGoal->SetLine(pos);
	}
	else
	{
		assert(false);
	}

	return pGoal;
}
