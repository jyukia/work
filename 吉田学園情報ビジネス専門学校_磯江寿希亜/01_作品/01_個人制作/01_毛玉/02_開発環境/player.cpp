//=============================================================================
// インクルードファイル
//=============================================================================
#include <assert.h>
#include "application.h"
#include "camera.h"
#include "input.h"
#include "main.h"
#include "objectX.h"
#include "player.h"
#include "shadow.h"
#include "renderer.h"
#include "meshfield.h"
#include "game.h"
#include"DebugProc.h"
#include"meshorbit.h"
#include "title.h"
#include "Meshline.h"
#include "movelife.h"
#include"Item.h"
#include "Preparation.h"
#include "goal.h"
#include "inputjoypad.h"
//=============================================================================
// 定数定義
//=============================================================================
const float CPlayer::SPEED_POWER = 4.0f;
const float CPlayer::JUMP_POWER = 12.0f;
const float CPlayer::GRAVITY_POWER = 0.775f;

int CPlayer::keyCnt = 1;


//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) :
	m_nSpeed(0.0f),
	m_bJumpFlag(false),
	m_bIsLanding(false),
	m_bIsLandingUp(false),
	m_inertia(0.0f),
	bScale(false),
	bMoveFlg(true),
	redycheckflg(false),
	moverot(false)
{
	//オブジェクトのタイプセット処理
	CObject::SetType(OBJTYPE_PLAYER);
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init()
{
	{//初期化 
		redycheckflg = false;

		moverot = false;

		m_inertia = 0.5f;	//慣性

		m_nSpeed = 5.0f;	//移動スピード
	}
	//objectxのposとrot
	D3DXVECTOR3 pos = CObjectX::GetPos();

	D3DXVECTOR3 size = CObjectX::GetSize();

	D3DXVECTOR3 rot = CObjectX::GetRot();

	//オブジェクトの初期化
	CObjectX::Init();

	//クォータニオンの使用
	SetbQuaternion(true);

	//目的の角度の初期化
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//影の生成
	CShadow::Create(pos, size, CObject::PRIORITY_LEVEL3);

	//メッシュエフェクト
	//m_MeshEffect = CMeshOrbit::Create(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f));
	//m_MeshEffect->SetMtxParent(GetMtxWorld());


	if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_TITLE)
	{
		//毛糸線
		m_pMeshLine = CMeshLine::Create(D3DXVECTOR3(pos.x, pos.y - 48, pos.z), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(50.0f, 0.0f, 0.0f));
		m_pMeshLine->SetMtxParent(GetMtxTransPos());
	}
	else
	{
		//毛糸線
		m_pMeshLine = CMeshLine::Create(D3DXVECTOR3(pos.x, pos.y-10, pos.z), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(50.0f, 0.0f, 0.0f));
		m_pMeshLine->SetMtxParent(GetMtxTransPos());
	}

	SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_GAME);


	return S_OK;
}
//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update()
{
	//入力数カウント
	keyCnt = 1;

	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::Getinstnce()->GetInput();
	//コントローラー
	CInputJoyPad *pJoy = CApplication::GetJoy();

	// 向き取得
	D3DXVECTOR3 rot = GetRot();
	// 移動力取得
	D3DXVECTOR3 move = GetMove();

	//スケール対応したサイズを計算		当たり判定使用
	D3DXVECTOR3 Scale = CObjectX::GetScale();
	D3DXVECTOR3 Size = CObjectX::GetSize();
	// 座標取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 posOld = GetPosOld();

	//メッシュエフェクト
	//D3DXVECTOR3 ofsetpos = m_MeshEffect->GetOfSetPos();
	//ofsetpos.x = 0.0f;
	//ofsetpos.y = 100.0f;
	//ofsetpos.z = 0.0f;
	//m_MeshEffect->SetOfSetPos(ofsetpos);

	//クォータニオン取得
	D3DXQUATERNION fst = CObjectX::GetQuaternionFst();
	{// デバック表示
#ifdef _DEBUG
	// //プレイヤー 座標
	//	CDebugProc::Print("プレイヤーの位置       (pos)       | X : %.2f | Y : %.2f | Z : %.2f |\n", pos.x, pos.y, pos.z);
	//	//回転
	//	CDebugProc::Print("プレイヤーの回転       (rot)       | X : %.2f | Y : %.2f | Z : %.2f |\n", rot.x, rot.y, rot.z);
	//	//移動
	//	CDebugProc::Print("プレイヤーの移動       (move)      | X : %.2f | Y : %.2f | Z : %.2f |\n", move.x, move.y, move.z);
	//	//目的の角度
	//	CDebugProc::Print("プレイヤーの目的の角度 (m_rotDest) | X : %.2f | Y : %.2f | Z : %.2f |\n", m_rotDest.x, m_rotDest.y, m_rotDest.z);
	//	//クォータニオン
	//	CDebugProc::Print("プレイヤー[クォータニオン] (fst) | %f |\n", fst);
	//	//プレイヤージャンプ判定
	//	if (m_bJumpFlag)
	//	{//ジャンプ
	//		CDebugProc::Print("プレイヤーのジャンプ判定 (m_bJumpFlag) ジャンプ \n", m_bJumpFlag);
	//	}
	//	else
	//	{//着地
	//		CDebugProc::Print("プレイヤーのジャンプ判定 (m_bJumpFlag) 着地 \n", m_bJumpFlag);
	//	}
#endif // _DEBUG
	}
	SetPosOld(pos);

	// 前回の位置を保存
	posOld = pos;

	// カメラの情報取得
	D3DXVECTOR3 pCameraRot = CCamera::GetRot();
	//CDebugProc::Print("カメラの情報       (pCameraRot)       | X : %.2f | Y : %.2f | Z : %.2f |\n", pCameraRot.x, pCameraRot.y, pCameraRot.z);

	//bool flg = CMode::GetMeshLine()->GetMoveFlg();	//移動制限のフラグ

	switch (eScaleType)
	{
	case CPlayer::TypeScaleNone:
		break;
	case CPlayer::TypeScaleUp:
		Scale.x += 0.001f;
		Scale.y += 0.001f;
		Scale.z += 0.001f;
		break;
	case CPlayer::TypeScaleDown:
		Scale.x -= 0.001f;
		Scale.y -= 0.001f;
		Scale.z -= 0.001f;
		break;
	default:
		break;
	}
	if (pos == posOld)	//動いていないとき
	{
		eScaleType = TypeScaleNone;
	}

	//ゴールして時のフラグ
	bool goalflg = CApplication::Getinstnce()->GetpMode()->GetGoal()->Getflg();
	//一定サイズまで行くと変更しないよう
	if (Scale.x <= 0.6f || Scale.y <= 0.6f || Scale.z <= 0.6f)
	{
		Scale.x = 0.6f;
		Scale.y = 0.6f;
		Scale.z = 0.6f;
		//CMode::GetMeshLine()->SetMoveFlg(flg);
	}
	else
	{
		moverot = false;	//クォータニオンフラグ
	}
	if (Scale.x >= 1.1f || Scale.y >= 1.1f || Scale.z >= 1.1f)
	{
		Scale.x = 1.1f;
		Scale.y = 1.1f;
		Scale.z = 1.1f;
		//CMode::GetMeshLine()->SetMoveFlg(flg);
	}
	if (goalflg)	//ゴールしたとき
	{
		redycheckflg = false;	//移動できないように
	}
	else	//ゴールしてないとき
	{
		if (redycheckflg)	//よーいドンで開始のためのフラグ
		{
			//メッシュ回収の為戻る処理
			if (pInputKeyboard->Press(DIK_R) || pJoy->GetPress(DirectJoypad::JOYPAD_B, 0))	//戻る処理
			{
					m_pMeshLine->AddVtxCount(-2);//戻る

					eScaleType = TypeScaleUp;

					D3DXVECTOR3 Center = m_pMeshLine->GetCenterVtx(); //中心点

					pos = Center;
			}
			else 	//メッシュを配置しているとき
			{
				//移動全般
				if (pInputKeyboard->Press(DIK_W) || pInputKeyboard->Press(DIK_A) || pInputKeyboard->Press(DIK_S) || pInputKeyboard->Press(DIK_D))
				{
					eScaleType = TypeScaleDown;
				}
				if (pInputKeyboard->Press(DIK_W))
				{// 上に移動
					if (pInputKeyboard->Press(DIK_A))
					{
						keyCnt++;

						move.x += sinf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;
						move.z += cosf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;

						m_rotDest.y = pCameraRot.y + D3DX_PI * 0.75f;
					}
					else if (pInputKeyboard->Press(DIK_D))
					{
						keyCnt++;

						move.x += sinf(D3DX_PI * 0.25f + pCameraRot.y) * m_nSpeed;
						move.z += cosf(D3DX_PI * 0.25f + pCameraRot.y) * m_nSpeed;

						m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.75f;
					}
					else
					{
						keyCnt++;

						move.x += sinf(pCameraRot.y) * m_nSpeed;
						move.z += cosf(pCameraRot.y) * m_nSpeed;
						m_rotDest.y = pCameraRot.y + D3DX_PI;
					}
				}
				if (pInputKeyboard->Press(DIK_S))
				{// 下に移動
					if (pInputKeyboard->Press(DIK_A))
					{
						keyCnt++;

						move.x += sinf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;
						move.z += cosf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;

						m_rotDest.y = pCameraRot.y + D3DX_PI * 0.25f;
					}
					else if (pInputKeyboard->Press(DIK_D))
					{
						keyCnt++;

						move.x += sinf(D3DX_PI * 0.75f + pCameraRot.y) * m_nSpeed;
						move.z += cosf(D3DX_PI * 0.75f + pCameraRot.y) * m_nSpeed;

						m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.25f;
					}
					else
					{
						keyCnt++;

						move.x -= sinf(pCameraRot.y) * m_nSpeed;
						move.z -= cosf(pCameraRot.y) * m_nSpeed;
						m_rotDest.y = pCameraRot.y + 0.0f;
					}
				}
				else if (pInputKeyboard->Press(DIK_A))
				{// 左に移動
					keyCnt++;

					move.x -= sinf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
					move.z -= cosf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
					m_rotDest.y = pCameraRot.y + D3DX_PI * 0.5f;
				}
				else if (pInputKeyboard->Press(DIK_D))
				{// 右に移動
					keyCnt++;

					move.x += sinf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
					move.z += cosf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
					m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.5f;
				}

				if (pJoy->GetPress(DirectJoypad::JOYPAD_UP, 0)		//w
					|| pJoy->GetPress(DirectJoypad::JOYPAD_LEFT, 0)	//a
					|| pJoy->GetPress(DirectJoypad::JOYPAD_RIGHT, 0)	//s 
					|| pJoy->GetPress(DirectJoypad::JOYPAD_DOWN, 0))	//d 
				{// 移動キーが押された

					eScaleType = TypeScaleDown;

					if (pJoy->GetPress(DirectJoypad::JOYPAD_UP, 0))
					{// [W]キーが押された時
						if (pJoy->GetPress(DirectJoypad::JOYPAD_LEFT, 0))
						{// [A]キーが押された時
						 // 移動方向の更新
							keyCnt++;
							move.x += sinf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;
							move.z += cosf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;

							m_rotDest.y = pCameraRot.y + D3DX_PI * 0.75f;
						}
						else if (pJoy->GetPress(DirectJoypad::JOYPAD_RIGHT, 0))
						{// [D]キーが押された時
						 // 移動方向の更新
							keyCnt++;

							move.x += sinf(D3DX_PI * 0.25f + pCameraRot.y) * m_nSpeed;
							move.z += cosf(D3DX_PI * 0.25f + pCameraRot.y) * m_nSpeed;

							m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.75f;
						}
						else
						{// 移動方向の更新
							keyCnt++;

							move.x += sinf(pCameraRot.y) * m_nSpeed;
							move.z += cosf(pCameraRot.y) * m_nSpeed;
							m_rotDest.y = pCameraRot.y + D3DX_PI;
						}
					}
					else if (pJoy->GetPress(DirectJoypad::JOYPAD_DOWN, 0))
					{// [S]キーが押された時
						if (pJoy->GetPress(DirectJoypad::JOYPAD_LEFT, 0))
						{// [A]キーが押された時
						 // 移動方向の更新
							keyCnt++;

							move.x += sinf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;
							move.z += cosf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;

							m_rotDest.y = pCameraRot.y + D3DX_PI * 0.25f;
						}
						else if (pJoy->GetPress(DirectJoypad::JOYPAD_RIGHT, 0))
						{// [D]キーが押された時
						 // 移動方向の更新
							keyCnt++;

							move.x += sinf(D3DX_PI * 0.75f + pCameraRot.y) * m_nSpeed;
							move.z += cosf(D3DX_PI * 0.75f + pCameraRot.y) * m_nSpeed;

							m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.25f;
						}
						else
						{// 移動方向の更新
							keyCnt++;

							move.x -= sinf(pCameraRot.y) * m_nSpeed;
							move.z -= cosf(pCameraRot.y) * m_nSpeed;
							m_rotDest.y = pCameraRot.y + 0.0f;
						}
					}
					else if (pJoy->GetPress(DirectJoypad::JOYPAD_LEFT, 0))
					{// [A]キーが押された時
					 // 移動方向の更新
						keyCnt++;

						move.x -= sinf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
						move.z -= cosf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
						m_rotDest.y = pCameraRot.y + D3DX_PI * 0.5f;
					}
					else if (pJoy->GetPress(DirectJoypad::JOYPAD_RIGHT, 0))
					{// [D]キーが押された時
					 // 移動方向の更新
						keyCnt++;

						move.x += sinf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
						move.z += cosf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
						m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.5f;
					}
				}
			}
		}
	}

	//角度の正規化(目的の角度)
	if (m_rotDest.y - rot.y > D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y - D3DX_PI * 2;
	}
	else if (m_rotDest.y - rot.y < -D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y + D3DX_PI * 2;
	}

	// 目的の値に近づける
	rot.y += (m_rotDest.y - rot.y) * PurposeRot;
	if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_TITLE)
	{
		pos.y = 30;
	}
	else if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_RANKING || CApplication::Getinstnce()->GetMode() == CApplication::MODE_GAME)
	{
		pos.y = 600;
	}
	else if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_GAME1)
	{
		pos.y = 0;
	}
	else
	{
		// 重力設定
		move.y -= GRAVITY_POWER;
	}

	//// ジャンプ処理
	//if (pInputKeyboard->Trigger(DIK_SPACE))
	//{
	//	m_bJumpFlag = true;
	//	move.y = 0.0f;
	//	move.y += 14.0f;
	//}

	// 角度の正規化(現在の角度)
	if (rot.y > D3DX_PI)
	{
		rot.y = rot.y - D3DX_PI * 2;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y = rot.y + D3DX_PI * 2;
	}

	//移動フラグ
	if (bMoveFlg)	//移動当たり判定, 回収時
	{
		pos += move;

	}
	//else 	//移動できないとき
	//{
	//	D3DXVECTOR3 nextPos = pos;
	//	nextPos += move;
	//	bool breturnflg_nextPos = m_pMeshLine->CollisionReturn(&nextPos);
	//	if (breturnflg_nextPos)
	//	{
	//		pos += move;
	//	}
	//	CObjectX::SetPos(pos);
	//	CObjectX::SetMove(nextPos);
	//}

	CDebugProc::Print("プレイヤー移動の情報       (move)       | X : %.2f | Y : %.2f | Z : %.2f |\n", move.x, move.y, move.z);

	if (!moverot)
	{
		//クォータニオン計算
		//move.x += (0.0f - move.x)* m_inertia;
		//move.y += (0.0f - move.y)* m_inertia;
		//move.z += (0.0f - move.z)* m_inertia;
		QuaternionCalculation(*Scale, &move, &fst);
		SetQuaternion(fst);
	}
	move.x *= 0.0f;
	move.z *= 0.0f;

	// ポインタ宣言
	CObject *pObject = CObject::GetTop(PRIORITY_LEVEL3);
	// 地面にいるかどうか
	m_bIsLandingUp = false;

	// プレイヤーとモデルの当たり判定
	while (pObject != nullptr)
	{
		if (pObject == this)
		{
			pObject = pObject->GetNext();
			continue;
		}

		//変数宣言
		CObject::EObjType objType;

		//オブジェクトのタイプを取得
		objType = pObject->GetObjType();

		if (objType == OBJTYPE_MODEL)
		{
			CObjectX *pObjectX = (CObjectX*)pObject;	//ダウンキャスト

			m_bIsLanding = pObjectX->Collision(&pos, &posOld, &Size, true);
			m_bIsLandingUp = pObjectX->UpCollision(&pos, &posOld, &Size, &move, true);
		}
		//ポインタを次に進める
		pObject = pObject->GetNext();
	}

	// メッシュフィールドのポインタを取得
	//CMeshfield *pMeshField = CGame::GetMeshfield();
	//// プレイヤーのposとrotの設定
	//if (pos.y < pMeshField->GetAnswer())
	//{
	//	m_bJumpFlag = false;
	//}
	//// メッシュフィールドとの当たり判定
	//if (m_bJumpFlag == false)
	//{
	//	m_bIsLandingMesh = pMeshField->Collision(&pos, &Size, true);
	//}
	// y軸が移動してなかった場合
	if (pos.y == posOld.y)
	{
		move.y = 0.0f;
	}

	if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_GAME || CApplication::Getinstnce()->GetMode() == CApplication::MODE_RANKING)
	{
		OutSide(pos);
	}
	if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_GAME1)
	{
		OutSide1(pos);
	}

	CObjectX::SetScale(Scale);
	// プレイヤーのposとrotとmoveの設定
	CObjectX::SetPos(pos);
	CObjectX::SetRot(rot);
	CObjectX::SetMove(move);

	// CObjectXの更新処理
	CObjectX::Update();
}

void CPlayer::OutSide(D3DXVECTOR3 &Playerpos)
{
	//場外に行かないため処理
	if (Playerpos.z >= -530.0f)
	{
		Playerpos.z = -530.0f;
	}
	if (Playerpos.z <= -2480.0f)
	{
		Playerpos.z = -2480.0f;
	}
	if (Playerpos.x >= 2000.0f)
	{
		Playerpos.x = 2000.0f;
	}
	if (Playerpos.x <= 1.0f)
	{
		Playerpos.x = 1.0f;
	}
}

void CPlayer::OutSide1(D3DXVECTOR3 & Playerpos)
{
	//場外に行かないため処理
	if (Playerpos.y <= 20.0f)
	{
		Playerpos.y = 20.0f;
	}
	if (Playerpos.z >= -350.0f)
	{
		Playerpos.z = -350.0f;
	}
	if (Playerpos.z <= -3500.0f)
	{
		Playerpos.z = -3500.0f;
	}
	if (Playerpos.x <= 500.0f)
	{
		Playerpos.x = 500.0f;
	}
	if (Playerpos.x >= 3000.0f)
	{
		Playerpos.x = 3000.0f;
	}
}


//=============================================================================
// 生成処理
//=============================================================================
CPlayer * CPlayer::Create(const D3DXVECTOR3 pos, int nPriority)
{
	CPlayer *pPlayer = new CPlayer(nPriority);

	if (pPlayer != nullptr)
	{
		pPlayer->Init();
		pPlayer->SetPos(pos);
		pPlayer->m_shadow = CShadow::Create(D3DXVECTOR3(pos.x, 0.5f, pos.z), D3DXVECTOR3(10.0f, 0.0f, 10.0f), CObject::PRIORITY_LEVEL3);
		//pPlayer->SetLine(pos);

	}
	else
	{
		assert(false);
	}

	return pPlayer;
}

////=============================================================================
//// セットモーション処理
////=============================================================================
//void CPlayer::SetMotionType(EMotion inMotion)
//{
//	// 同じモーションには遷移しない。
//	if (m_moutionType == inMotion)
//	{
//		return;
//	}
//
//	m_moutionType = inMotion;
//	GetMotion()->SetNumMotion(m_moutionType);
//}
////=============================================================================
//// セットライン処理
////=============================================================================
//void CPlayer::SetLine(const D3DXVECTOR3 pos)
//{
//	D3DXVECTOR3 size = D3DXVECTOR3(25.0f, 67.0f, 17.0f);
//
//	D3DXVECTOR3 rot = GetRot();
//
//	D3DXVECTOR3 VtxPos[8] = {};
//	VtxPos[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
//	VtxPos[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
//	VtxPos[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
//	VtxPos[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);
//	VtxPos[4] = D3DXVECTOR3(-size.x, size.y, size.z);
//	VtxPos[5] = D3DXVECTOR3(size.x, size.y, size.z);
//	VtxPos[6] = D3DXVECTOR3(size.x, size.y, -size.z);
//	VtxPos[7] = D3DXVECTOR3(-size.x, size.y, -size.z);
//
//	m_Line[0] = CLine::Create(pos, rot, VtxPos[0], VtxPos[1], D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), CObject::PRIORITY_LEVEL5);
//	m_Line[1] = CLine::Create(pos, rot, VtxPos[1], VtxPos[2], D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), CObject::PRIORITY_LEVEL5);
//	m_Line[2] = CLine::Create(pos, rot, VtxPos[2], VtxPos[3], D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), CObject::PRIORITY_LEVEL5);
//	m_Line[3] = CLine::Create(pos, rot, VtxPos[3], VtxPos[0], D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), CObject::PRIORITY_LEVEL5);
//
//	m_Line[4] = CLine::Create(pos, rot, VtxPos[0], VtxPos[4], D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), CObject::PRIORITY_LEVEL5);
//	m_Line[5] = CLine::Create(pos, rot, VtxPos[1], VtxPos[5], D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), CObject::PRIORITY_LEVEL5);
//	m_Line[6] = CLine::Create(pos, rot, VtxPos[2], VtxPos[6], D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), CObject::PRIORITY_LEVEL5);
//	m_Line[7] = CLine::Create(pos, rot, VtxPos[3], VtxPos[7], D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), CObject::PRIORITY_LEVEL5);
//
//	m_Line[8] = CLine::Create(pos, rot, VtxPos[4], VtxPos[5], D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), CObject::PRIORITY_LEVEL5);
//	m_Line[9] = CLine::Create(pos, rot, VtxPos[5], VtxPos[6], D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), CObject::PRIORITY_LEVEL5);
//	m_Line[10] = CLine::Create(pos, rot, VtxPos[6], VtxPos[7], D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), CObject::PRIORITY_LEVEL5);
//	m_Line[11] = CLine::Create(pos, rot, VtxPos[7], VtxPos[4], D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), CObject::PRIORITY_LEVEL5);
//}