#ifndef _GAME_1_H_
#define _GAME_1_H_

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
class Cpreparation;
class CParticle2D;
class CObject3D;
//=============================================================================
// クラスの定義
//=============================================================================
class CGame1 : public CMode
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	CGame1();
	~CGame1() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理
	static CGame1 *Create();			// 生成処理

	static CPlayer *GetPlayer() { return m_pPlayer; }
	static CMeshfield *GetMeshfield() { return m_pMeshField; }
private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	CObject2D *m_pObject2D;					// オブジェクト2Dのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャのポインタ
	static CPlayer *m_pPlayer;				// プレイヤーのポインタ
	static CLight *m_pLight;				// ライトのポインタ
	static CMeshfield *m_pMeshField;		// メッシュフィールドのポインタ	
	static CGoal *m_pGoal;				//ゴールポインタ

	Cpreparation *m_pPreparation;	//ゲーム開始の合図ポインタ

	CFade *m_pFade;
	CCamera *m_pCamera;

	CObject2D* m_pCompass;
	D3DXVECTOR3 m_rot;

	CObject3D* goalui;
	CObject2D* m_pTimeUi;
	CObject2D* m_pTime_Lope_Ui;
	CTimer *m_Timer;

	static CItem *m_pItem;

	static CItem *m_pItemTimeUp;

	//スコア
	static CScore* GetScore() { return pScore; }
	static CScore* pScore;

	//移動可能距離
	static CMovelife* GetMovelife() { return pMovelife; }
	static CMovelife* pMovelife;

	//メッシュライン
	CMeshLine *m_pMeshLine;

	CParticle2D* m_particle2d;

	float Xslide;

	bool returnflg;

	bool Goalflg;

};
#endif