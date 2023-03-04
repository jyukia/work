#ifndef _SELECT_STAGE_H_
#define _SELECT_STAGE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object2D.h"
#include "mode.h"
#include "objectX.h"

//=============================================================================
// 前方定義
//=============================================================================
class CFade;

class CCamera;
class CLight;
//=============================================================================
// クラスの定義
//=============================================================================
class CSelectStage : public CMode
{
public:

	enum SELECTMODE
	{
		MODE_NONE = 0,
		MODE_MAP,
		MODE_MAP1,
		SELECTMODEMAX
	};

	float m_Angle = 10.0f;

	const int m_modeMax = 2;	//画面遷移の最大数	//モード数によって変更
	const int m_modeMin = 1;	//画面遷移の最小数	//変更不要
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	CSelectStage();
	~CSelectStage() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理
	static CSelectStage *Create();		// 生成処理

	static int GetModeCount(void) {return m_modeSelectcount;}

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャのポインタ
	CObject2D *m_pObject2D;					// オブジェクト2Dのポインタ
	static bool m_bSelectEnter;				// Enterを押したかのフラグ

	CObject2D* m_pTex;

	CObjectX* pStage;		//ステージモデル
	CObjectX* pStage1;		//ステージモデル

	CObject2D* stagename;		//ステージ名前
	CObject2D* stagename1;		//ステージ名前１つ目

	static CLight *m_pLight;				// ライトのポインタ
	CFade *m_pFade;							// フェードのポインタ

	bool m_bmodeflg;

	static int m_modeSelectcount;			//画面遷移のためのカウント

	float radius;
	float add_x;
	float add_z;
};

#endif