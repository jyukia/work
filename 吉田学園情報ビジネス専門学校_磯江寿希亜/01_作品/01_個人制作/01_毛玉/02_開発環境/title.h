#ifndef _TITLE_H_
#define _TITLE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object2D.h"
#include "mode.h"

//=============================================================================
// 前方定義
//=============================================================================
class CTitleRogo;
class CFade;

class CPlayer;
class CCamera;
class CMeshfield;
class CLight;
class CMeshLine;
class CSkyField;
//=============================================================================
// クラスの定義
//=============================================================================
class CTitle : public CMode
{
public:
	const int m_modeMax = 3;	//画面遷移の最大数	//モード数によって変更
	const int m_modeMin = 1;	//画面遷移の最小数	//変更不要
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	CTitle();
	~CTitle() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理
	static CTitle *Create();		// 生成処理

	static CPlayer *GetPlayer() { return m_pPlayer; }
	static CMeshfield *GetMeshfield() { return m_pMeshField; }

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャのポインタ
	CObject2D *m_pObject2D;					// オブジェクト2Dのポインタ
	static bool m_bTitleEnter;				// Enterを押したかのフラグ

	CObject2D* m_pTitle;

	CObject2D* m_pGame;
	CObject2D* m_pRanking;
	CObject2D* m_ptutelial;


	static CPlayer *m_pPlayer;				// プレイヤーのポインタ
	static CLight *m_pLight;				// ライトのポインタ
	static CMeshfield *m_pMeshField;		// メッシュフィールドのポインタ
	static CMeshLine *m_pMeshLine;			//	メッシュライン
	
	CFade *m_pFade;							// フェードのポインタ

	bool m_bmodeflg;
	bool m_modebool;
	int cnt;

	int m_modecount;			//画面遷移のためのカウント

};

#endif