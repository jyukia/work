//=============================================================================
// インクルードファイル
//=============================================================================
#include "camera.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "game.h"
#include"DebugProc.h"
#include"SelectStage.h"
#include "goal.h"
#include "inputjoypad.h"

#include <math.h>

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
D3DXVECTOR3 CCamera::m_rot;
D3DXMATRIX	CCamera::m_mtxProjection;
D3DXMATRIX	CCamera::m_mtxView;
//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き

	{//プレイヤー
	 //視点・注視点・上方向を設定する（構造体の初期化）
		int mode = CApplication::Getinstnce()->GetMode();
		if (mode == CApplication::MODE_SELECT_STAGE)
		{
			m_posV = D3DXVECTOR3(0.0f, 100.0f, -400.0f);								//視点
		}
		else
		{
			m_posV = D3DXVECTOR3(0.0f, 100.0f, -200.0f);								//視点
		}
		m_posR = D3DXVECTOR3(0.0f, 20.0f, -1.0f);								//注視点
		m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);									//上方向ベクトル ←固定でOK!!

		m_CamPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_CamPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//{
		//	////ビューポート構成の保存
		//	//m_game_viewport.X = 0;
		//	//m_game_viewport.Y = 0;
		//	//m_game_viewport.Width = 1280;
		//	//m_game_viewport.Height = 720;
		//	//m_game_viewport.MaxZ = 1.0f;
		//	//m_game_viewport.MinZ = 0.0f;
		//}

	}

	float fLength1 = (m_posV.x - m_posR.x);									//視点から注視点のX軸の距離
	float fLength2 = (m_posV.z - m_posR.z);									//視点から注視点のZ軸の距離
	m_fDistance = sqrtf((fLength1 * fLength1) + (fLength2 * fLength2));		//視点から注視点までの距離

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CCamera::Update(void)
{
	//キーボードの情報取得
	CInput *pInputKeyboard = CApplication::Getinstnce()->GetInput();

	int mode = CApplication::Getinstnce()->GetMode();
	//ゴールして時のフラグ
	bool goalflg = CApplication::Getinstnce()->GetpMode()->GetGoal()->Getflg();

	if (goalflg)
	{
		m_rot.y += 0.005f;
	}
	else
	{
		if (mode == CApplication::MODE_GAME || mode == CApplication::MODE_GAME1)
		{
			//カメラの移動
			//if (pInputKeyboard->Press(DIK_DOWN))
			//{//上に移動
			//	m_posV.x -= sinf(m_rot.y) * CAMERA_SPEED;
			//	m_posV.z -= cosf(m_rot.y) * CAMERA_SPEED;
			//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
			//}
			//if (pInputKeyboard->Press(DIK_UP))
			//{//下に移動
			//	m_posV.x += sinf(m_rot.y) * CAMERA_SPEED;
			//	m_posV.z += cosf(m_rot.y) * CAMERA_SPEED;
			//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
			//}
			//if (pInputKeyboard->Press(DIK_RIGHT))
			//{//左に移動
			//	m_posV.x += sinf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
			//	m_posV.z += cosf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
			//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
			//}
			//if (pInputKeyboard->Press(DIK_LEFT))
			//{//右に移動
			//	m_posV.x -= sinf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
			//	m_posV.z -= cosf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
			//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
			//}

			//注視点の旋回
			//if (pInputKeyboard->Press(DIK_C))
			//{//左に旋回
			//	m_rot.y += 0.05f;
			//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
			//}
			//else if (pInputKeyboard->Press(DIK_Z))
			//{//右に旋回
			//	m_rot.y -= 0.05f;
			//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
			//}

			//コントローラー
			CInputJoyPad *pJoy = CApplication::GetJoy();
			//視点の旋回
			if (pInputKeyboard->Press(DIK_E)|| pJoy->GetPress(DirectJoypad::JOYPAD_R2, 0))
			{//左に旋回
				m_rot.y += 0.03f;
			}
			else if (pInputKeyboard->Press(DIK_Q) || pJoy->GetPress(DirectJoypad::JOYPAD_L2, 0))
			{//右に旋回
				m_rot.y -= 0.03f;
			}
		}
	}

	if (mode == CApplication::MODE_SELECT_STAGE)
	{
		//プレイヤー情報
		D3DXVECTOR3 pos1 = D3DXVECTOR3(700.0f, 10.0f, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

		int modecount = CSelectStage::GetModeCount();
		//計算用マトリックス
		D3DXMATRIX mtxRot, mtxTrans;

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxView);		//行列初期化関数(第一引数の行列を単位行列に初期化)

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z); //行列回転関数(第一引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
		D3DXMatrixMultiply(&m_mtxView, &m_mtxView, &mtxRot);				//行列掛け算関数(第2引数 * 第三引数を第一引数に格納)

		if (modecount == 1)
		{
			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, pos1.x, pos1.y, pos1.z);		//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
		}
		if (modecount == 2)
		{
			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);		//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
		}

		D3DXMatrixMultiply(&m_mtxView, &m_mtxView, &mtxTrans);

		D3DXVec3TransformCoord(&m_CamPosV, &m_posV, &m_mtxView);	//ワールド変換行列
		D3DXVec3TransformCoord(&m_CamPosR, &m_posR, &m_mtxView);	//ワールド変換行列
	}
	else if (mode == CApplication::MODE_GAME || mode == CApplication::MODE_GAME1 || mode == CApplication::MODE_TITLE || mode == CApplication::MODE_RANKING)
	{
		SetTarget();
	}

}
//=============================================================================
// 設定処理	(引数1 true 固定カメラ false フリーカメラ)(引数2 true 投影 false 並行投影)(引数3 true 画面複数生成 false 無効)
//=============================================================================
void CCamera::SetCamera(bool bfixed, bool btypecom)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//ビューマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxView);

	pDevice->SetViewport(&m_game_viewport);

	if (bfixed)	//固定カメラするかしないか
	{
		//ビューマトリックスの作成
		D3DXMatrixLookAtLH(&m_mtxView,
			&m_CamPosV,
			&m_CamPosR,
			&m_vecU);
	}
	else
	{
		//ビューマトリックスの作成
		D3DXMatrixLookAtLH(&m_mtxView,
			&m_posV,
			&m_posR,
			&m_vecU);
	}

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);
	if (btypecom)	//投影方法
	{
		//プロジェクションマトリックスの作成
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(90.0f),							//視野角
			(float)m_game_viewport.Width / (float)m_game_viewport.Height,		//アスペクト比
			10.0f,											//ニア（どこからどこまでカメラで表示するか設定）
			8000.0f);										//ファー
	}
	else
	{
		// プロジェクションマトリックスの作成(平行投影)
		D3DXMatrixOrthoLH(&m_mtxProjection,				// プロジェクションマトリックス
			(float)m_game_viewport.Width,				// 幅
			(float)m_game_viewport.Height,				// 高さ
			10.0f,													// ニア
			5000.0f);												// ファー
	}

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//=============================================================================
// 生成処理
//=============================================================================
CCamera * CCamera::Create()
{
	//ポインタ宣言
	CCamera *pCamera = nullptr;

	//インスタンス生成
	pCamera = new CCamera;

	if (pCamera != nullptr)
	{//ポインタが存在したら実行
		pCamera->Init();

	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pCamera;
}

void CCamera::SetTarget()
{
	//プレイヤー情報
	D3DXVECTOR3 pPlayerPos = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetPos();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	D3DXMATRIX mtxa;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxa);        //行列初期化関数(第一引数の行列を単位行列に初期化)

	 //向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);//行列回転関数(第一引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixMultiply(&mtxa, &mtxa, &mtxRot);//行列掛け算関数(第2引数 * 第三引数を第一引数に格納)

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pPlayerPos.x, pPlayerPos.y, pPlayerPos.z);//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
	D3DXMatrixMultiply(&mtxa, &mtxa, &mtxTrans);

	D3DXVec3TransformCoord(&m_CamPosV, &m_posV, &mtxa);//ワールド変換行列
	D3DXVec3TransformCoord(&m_CamPosR, &m_posR, &mtxa);//ワールド変換行列
}

void CCamera::SetSIz_Camera(D3DXVECTOR2 siz)
{
	m_game_viewport.Height = (DWORD)siz.y;
	m_game_viewport.Width = (DWORD)siz.x;

}

void CCamera::SetPos_Camera(D3DXVECTOR2 pos)
{
	m_game_viewport.X = (DWORD)pos.x;
	m_game_viewport.Y = (DWORD)pos.y;

}