//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "application.h"
#include"DebugProc.h"
#include "camera.h"
//#include"stage_imgui.h"
#include"Mapcamera.h"
#include"game.h"
#include"game1.h"
#include"pause.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define WIREFRAME ( 0 )	//0使用なし　1使用

//=============================================================================
// コンストラクタ
//=============================================================================
CRenderer::CRenderer()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CRenderer::~CRenderer()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;										// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;							// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;										// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル

	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if ((FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// 上記の設定が失敗したら
		// 描画と頂点処理をCPUで行なう
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))))
	{
		// 生成失敗
		return E_FAIL;
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


#if WIREFRAME
	//ワイヤーフレームの設定
	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
#else
#endif

	// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
#endif

	//フォグの設定
	//SetFog(true, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f));

	//カメラの生成
	for (int Cnt = 0; Cnt < 2; Cnt++)
	{
		m_pCamera[Cnt] = CCamera::Create();	//プレイヤーカメラ
	}

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CRenderer::Uninit()
{
#ifdef _DEBUG
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif // _DEBUG

	for (int Cnt = 0; Cnt < 2; Cnt++)
	{
		//カメラの解放・削除
		if (m_pCamera[Cnt] != nullptr)
		{
			m_pCamera[Cnt]->Uninit();
			delete m_pCamera[Cnt];
			m_pCamera[Cnt] = nullptr;
		}
	}

	// デバイスの破棄
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}
	// Direct3Dオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//=============================================================================
// 更新
//=============================================================================
void CRenderer::Update()
{
	//ポーズの処理
	CPause* pPause = CGame::GetPause();

	if (pPause == nullptr)
	{
		for (int Cnt = 0; Cnt < 2; Cnt++)
		{
			//カメラの更新処理
			if (m_pCamera[Cnt] != nullptr)
			{
				m_pCamera[Cnt]->Update();
			}
		}
		//全てのオブジェクトの更新処理
		CObject::UpdateAll();
	}
	else
	{
		if (pPause->GetPauseFlg())
		{
			pPause->Update();
		}
		else
		{
			for (int Cnt = 0; Cnt < 2; Cnt++)
			{
				//カメラの更新処理
				if (m_pCamera[Cnt] != nullptr)
				{
					m_pCamera[Cnt]->Update();
				}
			}
			//全てのオブジェクトの更新処理
			CObject::UpdateAll();
		}
	}

}

//=============================================================================
// 描画
//=============================================================================
void CRenderer::Draw()
{
	for (int Cnt = 0; Cnt < 2; Cnt++)
	{
		if (m_pCamera[Cnt] != nullptr)		//プレイヤーカメラ
		{
			if (Cnt == 0)//メインカメラ
			{
				if (m_pCamera[0] != nullptr)
				{
					m_pCamera[0]->SetCamera(true, true);		//引数1 カメラ移動(true 固定,false フリー) 引数2 投影方法(true 通常投影,false 並行投影)
				}
				D3DVIEWPORT9 gameview = m_pCamera[0]->GetViewPort();	//ビューポートの設定

				//ビューポート構成の保存
				gameview.X = 0;
				gameview.Y = 0;
				gameview.Width = 1280;
				gameview.Height = 720;
				gameview.MaxZ = 1.0f;
				gameview.MinZ = 0.0f;
				m_pCamera[0]->SetViewPort(gameview);

				int mode = CApplication::Getinstnce()->GetMode();
				if (mode == CApplication::MODE_RANKING)
				{
					D3DXVECTOR3 CamV = m_pCamera[0]->GetPosV();
					CamV = D3DXVECTOR3(0.0f, 100.0f, -100.0f);	//マップ上から見下ろすため高めに設定
					m_pCamera[0]->SetPosV(CamV);

					D3DXVECTOR3 Rot = m_pCamera[0]->GetRot();
					Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					m_pCamera[0]->SetRot(Rot);
				}
				else
				{
					m_pCamera[0]->SetPosV(D3DXVECTOR3(0.0f, 100.0f, -200.0f));	//元の値を入れる
				}
			}

			if (Cnt == 1)//マップカメラ
			{
				if (m_pCamera[1] != nullptr)
				{
					m_pCamera[1]->SetCamera(true, true);		//引数1 カメラ移動(true 固定,false フリー) 引数2 投影方法(true 通常投影,false 並行投影)
				}
				D3DVIEWPORT9 mapview = m_pCamera[1]->GetViewPort();		//ビューポートの設定

				if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_GAME || CApplication::Getinstnce()->GetMode() == CApplication::MODE_GAME1)
				{
					//ビューポート構成の保存
					mapview.X = 1020;
					mapview.Y = 25;
					mapview.Width = 240;
					mapview.Height = 200;
					mapview.MaxZ = 1.0f;
					mapview.MinZ = 0.0f;
					m_pCamera[1]->SetViewPort(mapview);

					D3DXVECTOR3 MapCamV = m_pCamera[1]->GetPosV();
					MapCamV = D3DXVECTOR3(0.0f, 500.0f, -10.0f);	//マップ上から見下ろすため高めに設定
					m_pCamera[1]->SetPosV(MapCamV);
				}
				else
				{
					//ビューポート構成の保存
					mapview.X = 1020;
					mapview.Y = 25;
					mapview.Width = 0;
					mapview.Height = 0;
					mapview.MaxZ = 1.0f;
					mapview.MinZ = 0.0f;
					m_pCamera[1]->SetViewPort(mapview);
				}
			}

		// バックバッファ＆Ｚバッファのクリア
		m_pD3DDevice->Clear(0, NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

		// Direct3Dによる描画の開始
		if (SUCCEEDED(m_pD3DDevice->BeginScene()))
		{
				//全てのオブジェクトの描画処理
				CObject::DrawAll();
#ifdef _DEBUG
				// FPS表示
				DrawFPS();

				// デバック表示
				CDebugProc::Draw();
#endif // _DEBUG

			}
			//CApplication::Getinstnce()->GetImgui()->Draw();

			// Direct3Dによる描画の終了
			m_pD3DDevice->EndScene();
		}
	}
	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// フォグ設定処理
//=============================================================================
void CRenderer::SetFog(bool bFlag, D3DXCOLOR col)
{
	// フォグの有効設定
	m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, bFlag);

	// フォグカラーの設定
	m_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, col);

	// フォグモード 第二引数(範囲指定 : D3DFOG_LINEAR, 密度指定 : D3DFOG_EXP)
	m_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);

	// 範囲指定(※LINEAR時に指定)
	float fFogStartPos = 100;
	float fFogEndPos = 1000; 
	m_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fFogStartPos));
	m_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fFogEndPos));

	// 密度指定(※EXP時に指定)
	float fFogDensity = 0.001f;

	m_pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&fFogDensity));
}

//=============================================================================
// デバイスを取得
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}

#ifdef _DEBUG
//=============================================================================
// FPS表示
//=============================================================================
void CRenderer::DrawFPS()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}
#endif // _DEBUG