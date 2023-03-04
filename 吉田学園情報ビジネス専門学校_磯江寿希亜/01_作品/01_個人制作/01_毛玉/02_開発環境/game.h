#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object2D.h"
#include "mode.h"

//=============================================================================
// 前方定義
//=============================================================================
class CPlayer;
class CCamera;
class CMeshfield;
class CFade;
class CLight;
class CScore;
class CMovelife;
class CMeshLine;
class CGoal;
class CItem;
class Cpreparation;
class CBillboard;
class CTimer;
class CParticle2D;
class CSound;
class CPause;
class CObject3D;
//=============================================================================
// クラスの定義
//=============================================================================
class CGame : public CMode
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	CGame();
	~CGame() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理
	static CGame *Create();			// 生成処理

	static CMeshfield *GetMeshfield() { return m_pMeshField; }
	static CPause* GetPause() { return pPause; }

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	CObject2D *m_pObject2D;					// オブジェクト2Dのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャのポインタ
	static CLight *m_pLight;				// ライトのポインタ
	static CMeshfield *m_pMeshField;		// メッシュフィールドのポインタ	
	static CGoal *m_pGoal;				//ゴールポインタ
	
	static CPause* pPause;

	//移動力アップ
	static CItem *m_pItem;

	static CItem *m_pItemTimeUp;
	static CItem *m_pItemTimeUp1;

	CTimer *m_Timer;

	Cpreparation *m_pPreparation;	//ゲーム開始の合図ポインタ

	CFade *m_pFade;
	CCamera *m_pCamera;

	CObject2D* m_pCompass;

	CObject2D* m_pTimeUi;
	CObject2D* m_pTime_Lope_Ui;
	CObject3D* goalui;
	CMovelife* m_Movelife;

	D3DXVECTOR3 m_rot;

	//移動可能距離
	static CMovelife* GetMovelife() { return pMovelife; }
	static CMovelife* pMovelife;

	float Xslide;

	int CntTime;
	//メッシュライン
	CMeshLine *m_pMeshLine;

	CParticle2D* m_particle2d;

	CBillboard* m_Billboard;

	bool returnflg;

	bool Goalflg;

	int GoalCnt;
};
#endif