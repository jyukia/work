#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "objectX.h"

//=============================================================================
// 前方定義
//=============================================================================
class CShadow;
class CMeshOrbit;
class CMeshLine;
//=============================================================================
// クラスの定義
//=============================================================================
class CPlayer : public CObjectX
{
public:
	enum ScaleType
	{
	TypeScaleNone = 0,
	TypeScaleUp,
	TypeScaleDown,

	TypeScaleMax
	};

	const D3DXVECTOR3 m_PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	static const float SPEED_POWER;
	static const float JUMP_POWER;
	static const float GRAVITY_POWER;

	//プレイヤーの振りむき速さ
	const float PurposeRot = 0.08f;
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CPlayer(int nPriority = PRIORITY_LEVEL3);
	~CPlayer() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override;			// 初期化処理
	void Update() override;				// 更新処理

	//ステージ1使用場外に行かなくするための処理
	void OutSide(D3DXVECTOR3 &Playerpos);
	//ステージ2使用場外に行かなくするための処理
	void OutSide1(D3DXVECTOR3 &Playerpos);


	static CPlayer *Create(const D3DXVECTOR3 pos, int nPriority);    // 生成処理

	static int GetKeyCnt(void) { return keyCnt; }		// カウント取得処理
	void SetKeyCnt(int keycnt) { keyCnt = keycnt; }

	void SetJumpFlag(bool fFlag) { m_bJumpFlag = fFlag; }

	void SetScaleType(ScaleType scaletype) { eScaleType = scaletype; }
	ScaleType GetscaleType() { return eScaleType; }

	bool GetMoveFlg() { return bMoveFlg; }
	void SetbMoveFlg(bool bmoveflg) { bMoveFlg = bmoveflg; }

	//プレイヤー角度
	D3DXVECTOR3 GetrotDest() { return m_rotDest; }

	//プレイヤーのスピード
	float Getnspeed() { return m_nSpeed; }
	void Setspeed(float Speed) { m_nSpeed = Speed; }

	//よーいドンまではプレイヤーを動かさないフラグ
	void Setbredycheck(bool bredycheckflg) { redycheckflg = bredycheckflg; }
	bool Getbredycheck() { return redycheckflg; }
private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	ScaleType eScaleType;
	
	CShadow *m_shadow;					// 影のポインタ
	CMeshOrbit *m_MeshEffect;	//メッシュエフェクト

	D3DXVECTOR3 m_rotDest;				// 目的の角度
	D3DXVECTOR3 m_posOld;				// 前回の位置
	float m_nSpeed;						// スピード
	float m_inertia;					//慣性
	bool m_bIsLandingUp;				// 上側当たり判定フラグ
	bool m_bIsLanding;					// 当たり判定フラグ
	bool m_bJumpFlag;					// ジャンプしたかどうかのフラグ
	bool m_bIsLandingMesh;				// メッシュ当たり判定フラグ
	bool bScale;
	bool bMoveFlg;

	CMeshLine *m_pMeshLine;

	//クォータニオン計算式使用
	static int keyCnt;
	//クォータニオン使用のフラグ取得
	bool Quaternionflg;

	//よーいドンまではプレイヤーを動かさないフラグ
	bool redycheckflg;

	//移動時のクォータニオン制御
	bool moverot;

	std::vector<D3DXVECTOR3> m_logPos;

};
#endif