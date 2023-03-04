#ifndef _GOAL_H_
#define _GOAL_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "objectX.h"

//=============================================================================
// 前方定義
//=============================================================================
class CShadow;
class CFade;
class CObject2D;
class CGoal : public CObjectX
{
public:
	
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CGoal(int nPriority = PRIORITY_LEVEL3);
	~CGoal() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override;			// 初期化処理
	void Update() override;				// 更新処理
	bool Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize, bool bQuaternion);

	static CGoal *Create(const D3DXVECTOR3 pos, int nPriority);    // 生成処理

	static bool GetGoalFlg(void) { return GoalFlg; }

	static bool Getflg(void) { return flg; }
	static void Setflg(bool goalflg) { flg = goalflg; }
private:
	CShadow *m_shadow;					// 影のポインタ
	CFade *m_pFade;

	static bool GoalFlg;

	int Cnt;
	static bool flg;

	CObject2D* Goal;
};


#endif