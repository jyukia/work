//=============================================================================
// インクルードファイル
//=============================================================================
#include "mode.h"
#include "renderer.h"
#include "application.h"
#include "player.h"
#include "Meshline.h"
#include "movelife.h"

CPlayer *CMode::m_pPlayer = nullptr;
CMeshLine *CMode::m_pMeshLine = nullptr;
CMovelife *CMode::m_MoveLife = nullptr;
CGoal *CMode::m_Goal = nullptr;
CItem *CMode::m_Item = nullptr;
CScore *CMode::m_GameScore = nullptr;

CInputJoyPad* CMode::m_Inputjoypad = nullptr;
CInputJoyPad* CMode::m_joypad = nullptr;

CTimer* CMode::m_Timer = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CMode::CMode()
{
	//オブジェクトのタイプセット処理
	CObject::SetType(OBJTYPE_MODE);
}

//=============================================================================
// デストラクタ
//=============================================================================
CMode::~CMode()
{

}