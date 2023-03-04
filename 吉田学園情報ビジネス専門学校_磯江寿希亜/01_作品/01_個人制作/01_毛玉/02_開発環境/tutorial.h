#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "object2D.h"
#include "mode.h"

//=============================================================================
// 前方定義
//=============================================================================
class CPlayer;
class CCamera;
class CMeshfield;
class CTime;
class CFade;
class CObstacle;

//=============================================================================
// クラスの定義
//=============================================================================
class CTutorial : public CMode
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	CTutorial();
	~CTutorial() override;

	//-------------------------------------------------------------------------
	// メンバ関数
	//-------------------------------------------------------------------------
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理
	static CTutorial *Create();			// 生成処理

	static CPlayer *GetPlayer1P() { return m_pPlayer; }
	static CCamera *GetCamera() { return m_pCamera; }
	static CMeshfield *GetMeshfield() { return m_pMeshField; }
	static CObstacle *GetObstacle1P() { return m_pObstacle; }

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	CObject2D *m_pObject2D;					// オブジェクト2Dのポインタ
	CFade *m_pFade;							// フェードのポインタ

	//-------------------------------------------------------------------------
	// 静的メンバ変数
	//-------------------------------------------------------------------------
	static CPlayer *m_pPlayer;			// 1Pプレイヤーのポインタ
	static CCamera *m_pCamera;				// カメラのポインタ
	static CLight *m_pLight;				// ライトのポインタ
	static CMeshfield *m_pMeshField;		// メッシュフィールドのポインタ	
	static CTime *m_pTime;					// タイムのポインタ
	static CObstacle *m_pObstacle;		// 1P障害物のポインタ
};

#endif