#ifndef _LINE_H_
#define _LINE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CLine : public CObject
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CLine(int nPriority = PRIORITY_LEVEL3);
	~CLine() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override;									// 初期化処理
	void Uninit() override;										// 終了処理						
	void Update() override;										// 更新処理
	void Draw() override;										// 描画処理
	void VtxUpdate() override {};								// 頂点座標更新処理
	void SetPos(D3DXVECTOR3 pos) override;						// 座標設定処理
	void SetSize(D3DXVECTOR3 size) override;					// サイズ設定処理
	void SetMove(D3DXVECTOR3 move) override;					// 移動量設定処理
	void SetCol(D3DXCOLOR col) override;						// 色設定処理
	void SetRot(D3DXVECTOR3 rot) override;						// 向き設定処理
	D3DXVECTOR3 GetPos(void) override { return m_pos; }			// 座標取得処理
	D3DXVECTOR3 GetSize(void) override { return m_size; }		// サイズ取得処理
	D3DXVECTOR3 GetMove(void) override { return m_move; }		// 移動量取得処理
	D3DXVECTOR3 GetRot(void) override { return m_rot; }			// 向き取得処理
	D3DXCOLOR GetCol(void) override { return m_col; }			// 色取得処理
	void SetLine();												// セットライン処理

	static CLine *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 goal, D3DXCOLOR col, int nPriority);		// 生成処理

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	D3DXVECTOR3 m_pos;						// 座標
	D3DXVECTOR3 m_move;						// 移動力
	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR3 m_size;						// サイズ
	D3DXVECTOR3 m_start;					// 始点
	D3DXVECTOR3 m_goal;						// 終点
	D3DXCOLOR m_col;						// 色
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
};

#endif