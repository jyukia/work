#ifndef _ITEM_H_
#define _ITEM_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "objectX.h"

//=============================================================================
// 前方定義
//=============================================================================
class CShadow;
class CItem : public CObjectX
{
public:
	enum TypeItem
	{
		ITEM_NONE = 0,

		ITEM_MOVE_SPEED_UP,
		ITEM_GAMETIME_UP,
		ITEM_SCORE_UP,

		ITEM_MAX
	};


	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CItem(int nPriority = PRIORITY_LEVEL3);
	~CItem() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override;			// 初期化処理
	void Update() override;				// 更新処理

	void Uninit() override;				// 終了処理
	bool Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize, bool bQuaternion);

	void SetType(TypeItem type) { typeItem = type; }

	static CItem *Create(const D3DXVECTOR3 pos, int nPriority, TypeItem type);    // 生成処理

	 bool GetHitFlg(void) { return HitFlg; }

	 bool GetMoveSpeedUpflg(void) { return MoveSpeedUp; }
	 static bool GetSizdownflg(void) { return MoveLifeUpflg; }
	static void SetSizdownflg(bool flg) { MoveLifeUpflg = flg; }

	 bool GetScoreUpflg(void) { return ScoreUpflg; }

private:
	CShadow *m_shadow;					// 影のポインタ

	TypeItem typeItem;

	int Cnt;

	 bool HitFlg;

	 bool MoveSpeedUp;
	static bool MoveLifeUpflg;
	 bool ScoreUpflg;
};


#endif