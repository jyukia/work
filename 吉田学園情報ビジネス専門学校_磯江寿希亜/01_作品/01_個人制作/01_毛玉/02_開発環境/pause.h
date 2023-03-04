//
//ファイルヘッダーコメント

#ifndef _CPause_H_
#define _CPause_H_

#include "renderer.h"
#include"application.h"
#include"object2d.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CFade;
//*****************************************************************************
//マクロ定義
//*****************************************************************************

class CPause : public CObject2D
{
public:
	const int m_modeMax = 2;	//画面遷移の最大数	//モード数によって変更
	const int m_modeMin = 1;	//画面遷移の最小数	//変更不要

public:
	//コンストラクタ	
	CPause(int nPriority);
	//デストラクタ
	~CPause() override;

	//初期化
	HRESULT Init() override;
	//終了
	void Uninit() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;

	void SetObject(D3DXVECTOR3 Pos);

	static CPause* Create(const char *aFileName, D3DXVECTOR3 size, D3DXVECTOR3 pos, int nPriority);

	//Texの読み込み　1つ１つ実体が作られているのでそれを一括で管理し軽くする	Unloadも同様
	static HRESULT Load();
	//テクスチャの破棄
	static void Unload();

	static bool GetPauseFlg() { return PauseFlg; }

private:
	//=============================================================================
	// 情報 
	//=============================================================================
	//テクスチャ数のポインタ 
	static LPDIRECT3DTEXTURE9 m_pTexture;

	CObject2D* m_pGame;
	CObject2D* m_pRanking;

	CFade *m_pFade;							// フェードのポインタ

	int m_modecount;
	static bool PauseFlg;
};
#endif