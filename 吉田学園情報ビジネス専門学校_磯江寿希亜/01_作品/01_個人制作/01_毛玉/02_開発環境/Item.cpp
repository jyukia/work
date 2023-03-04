//============================
//
// アイテム設定
// Author:磯江寿希亜
//
//============================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "Item.h"
#include "shadow.h"
#include "application.h"
#include "player.h"
#include "mode.h"
#include "particle.h"
#include "Meshline.h"
#include"DebugProc.h"
#include "score.h"
#include "sound.h"
#include"Timer.h"

bool CItem::MoveLifeUpflg = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CItem::CItem(int nPriority):HitFlg(false), MoveSpeedUp(false)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CItem::~CItem()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CItem::Init()
{
	{
		HitFlg = false;
		MoveSpeedUp = false;	//使用なし
		MoveLifeUpflg = false;
	}
	D3DXVECTOR3 pos = CObjectX::GetPos();

	D3DXVECTOR3 size = CObjectX::GetSize();

	D3DXVECTOR3 rot = CObjectX::GetRot();

	//オブジェクトの初期化
	CObjectX::Init();

	//影の生成
	CShadow::Create(pos, size, CObject::PRIORITY_LEVEL3);


	return S_OK;
}

//=============================================================================
// 更新
//=============================================================================
void CItem::Update()
{
	if (CApplication::Getinstnce()->GetpMode()->GetPlayer() != nullptr)
	{
		D3DXVECTOR3 pPlayerPos = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetPos();
		D3DXVECTOR3 pPlayerPosOld = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetPosOld();
		D3DXVECTOR3 pSize = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetSize();
		
		D3DXVECTOR3 rot = GetRot();

		// 座標取得
		D3DXVECTOR3 pos = GetPos();

		//CObject3D* particle = CParticle::Create(D3DXVECTOR3(pos.x, pos.y +50, pos.z), D3DXVECTOR3(20, 20, 20));

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

				D3DXVECTOR3 size = D3DXVECTOR3(150, 150, 150);
				HitFlg = Collision(&pPlayerPos, &pPlayerPosOld, &size, true);
			}

			//ポインタを次に進める
			pObject = pObject->GetNext();
		}
		if (HitFlg)	//ゴールとプレイヤーが触れたら
		{
			float Speed = CApplication::Getinstnce()->GetpMode()->GetPlayer()->Getnspeed();

			switch (typeItem)
			{
			case CItem::ITEM_MOVE_SPEED_UP:

			Speed = 7;
			CApplication::Getinstnce()->GetpMode()->GetPlayer()->Setspeed(Speed);
			CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_WIND);	//風きる音

			MoveSpeedUp = true;
				break;
			case CItem::ITEM_GAMETIME_UP:

			CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_CLOCK);	//コイン音
			MoveLifeUpflg = true;
				break;
			case CItem::ITEM_SCORE_UP:

			CApplication::Getinstnce()->GetpMode() ->GetScore()->AddScore(100);

			CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_COIN);	//コイン音

			ScoreUpflg = true;
				break;
			default:
				break;
			}
		}
		else
		{
			//更新 アイテム管理
			switch (typeItem)
			{
			case CItem::ITEM_MOVE_SPEED_UP:
				Cnt++;
				pos.y += (float)(sinf(D3DXToRadian(Cnt * 3)) * 1.5f);
				break;
			case CItem::ITEM_GAMETIME_UP:
				Cnt++;
				pos.y += (float)(sinf(D3DXToRadian(Cnt * 3)) * 1.5f);
				break;
			case CItem::ITEM_SCORE_UP:
				rot.y += 0.1f;	//コインの回転
				break;
			default:
				break;
			}
			rot.y += 0.1f;	//コインの回転
		}
		SetPos(pos);
		SetRot(rot);
	}
}
void CItem::Uninit()
{
	CObjectX::Uninit();
}
//=============================================================================
// 当たり判定 (左右,奥,手前)
//=============================================================================
bool CItem::Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize, bool bQuaternion)
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
			Uninit();

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
			Uninit();

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
			Uninit();

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
			Uninit();

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
			Uninit();


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
			Uninit();


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
			Uninit();
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
			Uninit();
		}
	}

	// 値を返す
	return bIsLanding;
}
//=============================================================================
// 生成処理
//=============================================================================
CItem * CItem::Create(const D3DXVECTOR3 pos, int nPriority, TypeItem item)
{
	CItem *pItem = new CItem(nPriority);

	if (pItem != nullptr)
	{
		pItem->Init();
		pItem->SetPos(pos);
		pItem->SetType(item);
		pItem->m_shadow = CShadow::Create(D3DXVECTOR3(pos.x, 0.5f, pos.z), D3DXVECTOR3(10.0f, 0.0f, 10.0f), CObject::PRIORITY_LEVEL3);
	
	}
	else
	{
		assert(false);
	}

	return pItem;
}
