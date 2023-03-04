#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CMeshfield : CObject
{
	//-------------------------------------------------------------------------
	// マクロ定義
	//-------------------------------------------------------------------------
	#define POLYGON_DEPTH	(200.0f)			//ポリゴンの奥行き
	#define POLYGON_HEIGHT	(200.0f)			//ポリゴンの高さ
	#define POLYGON_WIDTH	(200.0f)			//ポリゴンの幅
	#define MESHFIELD_X_BLOCK	(30)			//X方向のブロック数
	#define MESHFIELD_Z_BLOCK	(30)			//Z方向のブロック数
	#define MESHFIELD_VERTEX_NUM	((MESHFIELD_X_BLOCK + 1) * (MESHFIELD_Z_BLOCK + 1))									//頂点数
	#define MESHFIELD_INDEXNUM		((MESHFIELD_X_BLOCK + 1) * 2 * MESHFIELD_Z_BLOCK + (MESHFIELD_Z_BLOCK - 1) * 2)		//インデックス数
	#define	MESHFIELD_PRIMITIVE_NUM	(MESHFIELD_X_BLOCK * (MESHFIELD_Z_BLOCK * 2) + (MESHFIELD_Z_BLOCK - 1) * 4)			//ポリゴン数	

public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CMeshfield(int nPriority = PRIORITY_LEVEL3);
	~CMeshfield() override;

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
	void LoadTexture(const char *aFileName);					// テクスチャの読み込み

	static CMeshfield *Create(const D3DXVECTOR3 pos, int nPriority);    // 生成処理
	bool Collision(D3DXVECTOR3 *PlayerPos, D3DXVECTOR3 *PlayerSize, bool bQuaternion);		// 当たり判定
	float GetAnswer(void) { return m_AnswerKeep; }						// 内積の計算結果取得

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		// インデックスバッファのポインタ
	D3DXVECTOR3 m_pos;						// 座標
	D3DXVECTOR3 m_move;						// 移動力
	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR3 m_size;						// サイズ
	D3DXCOLOR m_col;						// 色
	float m_fLength;						// 対角線の長さ
	float m_fAngle;							// 角度
	float m_RandHeight;						// ランダムな高さ格納用変数
	float m_fRotMove;						// sin波
	float m_fRot;							// sin波の角度
	float m_AnswerKeep;						// 内積の計算結果保存
	EObjType m_type;						// オブジェクトのタイプ
	D3DXMATRIX m_mtxWorldMeshField;			// メッシュフィールドの頂点情報
};

#endif