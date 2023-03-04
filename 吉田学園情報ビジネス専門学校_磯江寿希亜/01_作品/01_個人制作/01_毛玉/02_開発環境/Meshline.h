#ifndef _MESHLINE_H_
#define _MESHLINE_H_

//前方宣言
class CTexture;
class CMovelife;
//=============================================================================
// インクルードファイル
//=============================================================================
#include "objectX.h"
#include "object.h"
 
class CMeshLine : public CObject
{
public:
	//生成ライン回数
	const int MaxLine = 10000;
	//生成ライン回数	title
	const int MaxLineTitle = 9000;

public:

	explicit CMeshLine(int nPriority = PRIORITY_LEVEL3);
	~CMeshLine() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init()override;							// 初期化処理
	void Uninit() override;							// 終了処理
	void Update() override;							// 更新処理
	void Draw()   override;							// 描画処理

	void LoadTexture(const char * aFileName);

	//セッター
	void SetMtxParent(D3DXMATRIX *pMtx);
	void SetOfSetPos(D3DXVECTOR3 ofsetpos);

	void SetPos(D3DXVECTOR3 pos);			// 座標設定処理
	void SetCol(D3DXCOLOR col);				// 色設定処理
	void SetRot(D3DXVECTOR3 rot);			// 向き設定処理

	//ゲッター
	D3DXVECTOR3 GetOfSetPos(void) { return OfSetPos; }			//サイズ変更
	D3DXVECTOR3 GetRot(void) { return m_rot; }		// 向き取得処理
	D3DXCOLOR GetCol(void) { return m_col; }			// 色取得処理

	bool GetbIsLanding() { return bIsLanding; }
	
	void SetVtxCount(int vtxcount) { m_pVtxMax = vtxcount; }

	bool GetbUseflg() { return bUseflg; }

	static CMeshLine *Create(D3DXVECTOR3 pos ,D3DXCOLOR col, D3DXVECTOR3 distancepos);		// 生成処理
	bool Collision(D3DXVECTOR3 *PlayerPos, D3DXVECTOR3 *PlayerSize);	//当たり判定

	bool CollisionReturn(D3DXVECTOR3 * PlayerPos);

	int GetVtxcount() {return m_Vtxcount;}
	void AddVtxCount(int count) {	//頂点の増加
		m_Vtxcount += count;

		if (m_Vtxcount < 2)
		{
			m_Vtxcount = 2;
		}
	}


	void SetVtx(int vtx) {m_Vtxcount = vtx;}

	D3DXVECTOR3 GetCenterVtx();

	float Vec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2);
	float Vec2Dot(D3DXVECTOR3* v1, D3DXVECTOR3* v2);
private:
	D3DXMATRIX *m_pMtxParent;	//軌跡の親モデルのマトリックス

	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファのポインタ
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス

	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_pos;
	D3DXCOLOR m_col;
	D3DXVECTOR3 OfSetPos;	//	縦座標の変換 サイズ変更可能

	D3DXVECTOR3 m_returnpos;

	D3DXVECTOR3 m_buckpos;

	CMovelife *m_movelife;

	int m_pVtxMax;	//最大数

	bool bUseflg;

	int m_Vtxcount;

	static bool bIsLanding;	//増やす変数

	int m_Game_PlayerMove;
};

#endif