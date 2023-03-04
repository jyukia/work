#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object.h"


//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 構造体定義
//=============================================================================
// 頂点データ
struct VERTEX_3D
{
	D3DXVECTOR3 pos;		//頂点座標
	D3DXVECTOR3 nor;		//法線ベクトル
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
};

//=============================================================================
// クラスの定義
//=============================================================================
class CObject3D : public CObject
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CObject3D(int nPriority = PRIORITY_LEVEL3);
	~CObject3D() override;

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
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);				// 派生のテクスチャポインタを親のテクスチャポインタに代入する処理
	void SetUV(float x_1, float x_2, float y_1, float y_2);		// テクスチャ座標更新処理
	D3DXVECTOR3 GetPos(void) override { return m_pos; }			// 座標取得処理
	D3DXVECTOR3 GetSize(void) override { return m_size; }		// サイズ取得処理
	D3DXVECTOR3 GetMove(void) override { return m_move; }		// 移動量取得処理
	D3DXVECTOR3 GetRot(void) override { return m_rot; }			// 向き取得処理
	D3DXCOLOR GetCol(void) override { return m_col; }			// 色取得処理
	void SetBillboard(bool bBillboard) { m_bBillboard = bBillboard; }				// ビルボードの設定
	bool GetBillboard() { return m_bBillboard; }									// ビルボードの取得

	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }

	static CObject3D *Create(D3DXVECTOR3 pos, int nPriority);	// 生成処理
	static CObject3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size,int nPriority);	// 生成処理

	void LoadTexture(const char *aFileName);					// テクスチャの読み込み

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
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	bool	m_bBillboard;		// ビルボードかどうか

};

#endif