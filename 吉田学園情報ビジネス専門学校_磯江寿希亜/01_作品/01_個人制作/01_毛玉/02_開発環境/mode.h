#ifndef _MODE_H_
#define _MODE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// 前方定義
//=============================================================================
class CTitle;
class CGame;
class CResult;
class CPlayer;
class CMeshLine;
class CMovelife;
class CSkyField;
class CLight;
class CTexture;
class CItem;
class Cpreparation;
class CGoal;
class CScore;
class CInputJoyPad;
class CTimer;
//=============================================================================
// クラスの定義
//=============================================================================
class CMode : public CObject
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	CMode();
	~CMode() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override { return S_OK; };		// 初期化処理
	void Uninit() override {};						// 終了処理
	void Update() override {};						// 更新処理
	void Draw() override {};						// 描画処理
	void VtxUpdate() override {};					// 頂点座標更新処理
	void SetPos(D3DXVECTOR3 pos) override { D3DXVECTOR3 i = pos; };		// 座標設定処理
	void SetSize(D3DXVECTOR3 size) override { D3DXVECTOR3 i = size; };		// サイズ設定処理
	void SetMove(D3DXVECTOR3 move) override { D3DXVECTOR3  i = move; };		// 移動量設定処理
	void SetCol(D3DXCOLOR col) override { D3DXCOLOR i = col; };			// 色設定処理
	void SetRot(D3DXVECTOR3 rot) override { D3DXVECTOR3 i = rot; };		// 向き設定処理
	D3DXVECTOR3 GetPos(void) override { return D3DXVECTOR3(); }			// 座標取得処理
	D3DXVECTOR3 GetSize(void) override { return D3DXVECTOR3(); }		// サイズ取得処理
	D3DXVECTOR3 GetMove(void) override { return D3DXVECTOR3(); }		// 移動量取得処理
	D3DXVECTOR3 GetRot(void) override { return D3DXVECTOR3(); }			// 向き取得処理
	D3DXCOLOR GetCol(void) override { return D3DXCOLOR(); }			// 色取得処理

	//プレイヤー
	static CPlayer *GetPlayer() { return m_pPlayer; }
	static void SetPlayer(CPlayer* player) { m_pPlayer = player; }

	//空
	static CSkyField *GetSkyField() { return m_SkyField; }
	static void SetSkyField(CSkyField* skyfield) { m_SkyField = skyfield; }

	//テクスチャ
	static CTexture *GetTexture() { return m_Texture; }
	static void SetTexture(CTexture* texture) { m_Texture = texture; }

	//プレイヤー移動量
	static CMeshLine *GetMeshLine() { return m_pMeshLine; }

	//プレイヤー移動量	ナンバー
	static CMovelife *GetMoveLife() {return m_MoveLife;}

	//アイテム
	static CItem* GetItem() { return m_Item; }

	//ゲーム開始のためのカウント
	static 	Cpreparation * GetPreparation() { return m_preparation; }

	//ゴール
	static 	CGoal* GetGoal() { return m_Goal; }

	//スコア
	static CScore* GetScore() { return m_GameScore; }
	static void SetScore(CScore* score) {  m_GameScore= score; }

	static CInputJoyPad* GetJoy() { return m_joypad; }
	static CInputJoyPad* GetInpuJoy() { return m_Inputjoypad; }

	static CTimer* GetTimer() {return m_Timer;}
private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------

	static CPlayer *m_pPlayer;				// プレイヤーのポインタ

	static CMeshLine *m_pMeshLine;

	static CMovelife *m_MoveLife;

	static CSkyField *m_SkyField;

	static CTexture *m_Texture;

	static 	CItem *m_Item;

	static 	Cpreparation *m_preparation;

	static 	CGoal *m_Goal;

	static CScore *m_GameScore;

	static CInputJoyPad* m_Inputjoypad;
	static CInputJoyPad* m_joypad;

	static CTimer* m_Timer;
};

#endif