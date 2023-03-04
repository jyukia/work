#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object.h"
#include <string>

//=============================================================================
// マクロ定義
//=============================================================================
// 頂点フォーマット
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//=============================================================================
// 構造体定義
//=============================================================================
// 頂点データ
struct VERTEX_2D
{
	D3DXVECTOR3 pos;		//頂点座標
	float rhw;				//座標変換用係数（1.0fで固定）
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
};

//=============================================================================
// クラスの定義
//=============================================================================
class CObject2D : public CObject
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CObject2D(int nPriority = PRIORITY_LEVEL4);
	~CObject2D() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override;									// 初期化処理
	void Uninit() override;										// 終了処理
	void Update() override;										// 更新処理
	void Draw() override;										// 描画処理
	void VtxUpdate() override;									// 頂点座標更新処理
	void SetPos(D3DXVECTOR3 pos) override;						// 座標設定処理
	void SetSize(D3DXVECTOR3 size) override;					// サイズ設定処理
	void SetMove(D3DXVECTOR3 move) override;					// 移動量設定処理
	void SetCol(D3DXCOLOR col) override;						// 色設定処理
	void SetRot(D3DXVECTOR3 rot) override;						// 向き設定処理
	void BindTexture(std::string inPath);						// 派生のテクスチャポインタを親のテクスチャポインタに代入する処理
	void SetUV(float x_1, float x_2, float y_1, float y_2);		// テクスチャ座標更新処理
	void SetPosUV(float x_1, float x_2, float y_1, float y_2, float x_width1, float x_width2);	// 座標更新処理

	
	void AnimVtx(int nummax/*アニメーション枚数*/, int PtternAnim/*進むスピード*/);	//アニメーション頂点の設定
	void SetRotate(bool set, int size) { m_bRotate = set, m_fSquareSize = (float)size; }
	D3DXVECTOR3 GetPos(void) override { return m_pos; }			// 座標取得処理
	D3DXVECTOR3 GetSize(void) override { return m_size; }		// サイズ取得処理
	D3DXVECTOR3 GetMove(void) override { return m_move; }		// 移動量取得処理
	D3DXVECTOR3 GetRot(void) override { return m_rot; }			// 向き取得処理
	D3DXCOLOR GetCol(void) override { return m_col; }			// 色取得処理
	static CObject2D *Create(const char *aFileName, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriority);	// 生成処理
	void CObject2D::ScoreVtx(float fstposX, float fstposY, float secdposX, float secdposY);

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファのポインタ
	D3DXVECTOR3 m_pos;						// 座標
	D3DXVECTOR3 m_move;						// 移動力
	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR3 m_size;						// サイズ
	D3DXCOLOR m_col;						// 色
	float m_fLength;						// 対角線の長さ
	float m_fAngle;							// 角度
	EObjType m_type;						// オブジェクトのタイプ
	bool m_bRotate;
	int m_nTime;
	float m_fSquareSize;
	float m_fRotZ = 0.0f;

	const D3DXVECTOR3 sVtx[4] =
	{
		D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
		D3DXVECTOR3(+1.0f, -1.0f, 0.0f),
		D3DXVECTOR3(-1.0f, +1.0f, 0.0f),
		D3DXVECTOR3(+1.0f, +1.0f, 0.0f),
	};
};

#endif