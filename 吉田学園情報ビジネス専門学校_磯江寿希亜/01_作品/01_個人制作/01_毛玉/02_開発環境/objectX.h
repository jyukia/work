#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object.h"
#include <string>
#include <vector>

#define MAX_MATERIAL_TEXTURE_NUM (100)

//=============================================================================
// 前方定義
//=============================================================================
class CLine;

//=============================================================================
// クラスの定義
//=============================================================================
class CObjectX : public CObject
{
public:
	//=========================================
	// モデルのマテリアル情報
	//=========================================
	struct MODEL_MATERIAL
	{
		LPD3DXMESH		pMesh;				// メッシュ情報へのポインタ
		LPD3DXBUFFER	pBuffer;			// マテリアル情報へのポインタ
		DWORD			nNumMat;			// マテリアル情報の数
		D3DXVECTOR3		size;				// モデルの大きさ
		int				*pNumTex;			// テクスチャタイプ
		char			aFileName[0xff];	// Xファイルのパス
		LPDIRECT3DTEXTURE9 pTexture[MAX_MATERIAL_TEXTURE_NUM];		// テクスチャ
	};

	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CObjectX(int nPriority = PRIORITY_LEVEL3);
	~CObjectX() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override;								// 初期化処理
	void Uninit() override;									// 終了処理
	void Update() override;									// 更新処理
	void Draw() override;									// 描画処理
	void Draw(D3DXMATRIX mtxParent);						// 描画処理
	void VtxUpdate() override {};							// 頂点座標更新処理

	void CalculationVtx();									// 頂点最大小値の計算処理

	// Setter
	//クォータニオン
	void SetbQuaternion(bool useflg) { bQuaternion = useflg; }	//クォータニオンのセット
	void SetQuaternion(D3DXQUATERNION quaternion) { m_quaternion = quaternion; }
	void SetPos(D3DXVECTOR3 pos) override;					// 座標設定処理
	void SetPosOld(D3DXVECTOR3 posold) { m_posold  = posold;}					// 座標設定処理 1フレーム前

	void SetSize(D3DXVECTOR3 size) override;				// サイズ設定処理
	void SetMove(D3DXVECTOR3 move) override;				// 移動量設定処理
	void SetCol(D3DXCOLOR col) override;					// 色設定処理
	void SetRot(D3DXVECTOR3 rot) override;					// 向き設定処理
	void SetMaxVtx(D3DXVECTOR3 Maxvtx);						// 頂点最大値設定処理
	void SetMinVtx(D3DXVECTOR3 Minvtx);						// 頂点最小値設定処理
	void SetParent(CObjectX* inParent) { m_pParent = inParent; }			// 親モデルの情報
	void SetCollisionFlag(bool inFlag) { m_isCollision = inFlag; }

	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; };				// スケール

	void SetMtxTransPos(D3DXMATRIX TransPos) { mtxTransPos = TransPos; };				// スケール

	static void SetAxis(D3DXVECTOR3 axis) { m_axis = axis; };	//プレイヤーの進行ベクトル
	
	// Getter
	D3DXVECTOR3 GetPos(void) override { return m_pos; }		// 座標取得処理
	D3DXVECTOR3 GetPosOld(void) { return m_posold; }		// 座標取得処理	1フレーム前の取得

	D3DXVECTOR3 GetSize(void) override { return m_size; }	// サイズ取得処理
	D3DXVECTOR3 GetMove(void) override { return m_move; }	// 移動量取得処理
	D3DXVECTOR3 GetRot(void) override { return m_rot; }		// 向き取得処理
	D3DXCOLOR GetCol(void) override { return m_col; }		// 色取得処理
	D3DXVECTOR3 GetMaxVtx(void) { return m_MaxVtx; }		// 頂点最大値取得処理
	D3DXVECTOR3 GetMinVtx(void) { return m_MinVtx; }		// 頂点最小値取得処理
	CObjectX* GetParent(void) { return m_pParent; }			// 親モデルの情報
	D3DXMATRIX *GetMtxWorld(void) { return &m_mtxWorld; }
	D3DXVECTOR3 GetScale(void) { return m_scale; }	// スケール
	D3DXMATRIX *GetMtxTransPos(void) { return &mtxTransPos; }
	static D3DXVECTOR3 GetAxis(void) {return m_axis; }			//プレイヤーの進行ベクトル

	bool GetQuaternion() { return bQuaternion; }		//クォータニオンフラグ

	bool IsCollision() { return m_isCollision; }

	//クォータニオン	
	D3DXQUATERNION GetQuaternionFst(void) { return m_quaternion; }

	//シェーダー
	void DrawMaterial();													// マテリアル描画
	static MODEL_MATERIAL *GetMaterial() { return m_material; }				// マテリアル情報の取得
	//MODEL_MATERIAL GetMyMaterial() { return m_material[m_nModelID]; }		// マテリアル情報の取得

	static CObjectX *Create(const char *aFileName, D3DXVECTOR3 pos, int nPriority);	// 生成処理
	static CObjectX *Create(D3DXVECTOR3 pos, int nPriority);	// 生成処理
	static CObjectX *Create(const char *aFileName, D3DXVECTOR3 rot,D3DXVECTOR3 pos, int nPriority);	// 生成処理

	void LoadModel(const char *aFileName);						// モデルの読み込み処理
	void BindTexture(std::string inPath);						// 派生のテクスチャポインタを親のテクスチャポインタに代入する処理
	void Projection(void);										// 平行投影処理
	void SetLine(const D3DXVECTOR3 pos);						// ラインセット処理

	// Collision
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pSize, bool bQuaternion);							// 当たり判定 (左右, 奥, 手前)
	bool UpCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pSize, D3DXVECTOR3 *pMove, bool bQuaternion);	// 当たり判定 (上側)

	//クォータニオン
	void QuaternionCalculation(float ModelDiameter/*モデルの直径*/, D3DXVECTOR3 *move, D3DXQUATERNION *FstQuaternion);

	//モデル配置のため
	std::string Getstring(void) { return m_ObjeX; }		// 頂点最小値取得処理
	void Setstring(const std::string objex) { m_ObjeX = objex; }						// ラインセット処理

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	D3DXVECTOR3 m_pos;					// 座標
	D3DXVECTOR3 m_posold;				// 座標 1フレーム前の取得

	D3DXVECTOR3 m_rot;					// 角度
	D3DXVECTOR3 m_size;					// 座標
	D3DXVECTOR3 m_move;					// 角度
	D3DXVECTOR3 m_MinVtx;				// モデルの頂点最小値
	D3DXVECTOR3 m_MaxVtx;				// モデルの頂点最大値
	D3DXCOLOR m_col;					// 色
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス

	std::vector<LPDIRECT3DTEXTURE9> m_pTexture;		// テクスチャのポインタ
	D3DXMATRIX mtxTransPos;		//回転削除

	D3DXVECTOR3 m_scale;	

	LPD3DXMESH m_pMesh;					// メッシュ情報へのポインタ
	LPD3DXBUFFER m_pBuffMat;			// マテリアル情報へのポインタ
	DWORD m_NumMat;						// マテリアル情報の数

	CLine *m_pLine[12];					// ラインのポインタ
	CObjectX *m_pParent;				// 親モデルの情報
	bool m_isCollision;					// 当たり判定が必要か

	std::string m_ObjeX;

	//-------------------------------------------------------------------------
	//クォータニオン
	D3DXQUATERNION m_quaternion;
	static D3DXVECTOR3 m_axis;    // 回転軸
	bool bQuaternion;	//クォータニオンフラグ

	//=========================================
	LPD3DXEFFECT		pEffect;					// シェーダー
	IDirect3DTexture9	*pTex0 = NULL;				// テクスチャ保存用
	//=========================================
	//ハンドル一覧
	//=========================================
	D3DXHANDLE			m_hmWVP;					// ワールド	射影行列
	D3DXHANDLE			m_hmWIT;					// ローカル - ワールド変換行列
	D3DXHANDLE			m_hvLightDir;				// ライトの方向
	D3DXHANDLE			m_hvCol;					// 頂点色
	D3DXHANDLE			m_hvEyePos;					// 視点の位置
	D3DXHANDLE			m_hTechnique;				// テクニック
	D3DXHANDLE			m_hTexture;					// テクスチャ
	D3DXHANDLE			m_hBool;					// テクスチャの中身があるかないかをみる

	static MODEL_MATERIAL	*m_material;		// マテリアル情報
	static int				m_nMaxModel;		// モデル数			

};
#endif