//============================
//
// アクションゲーム雛形
// Author:Teruto Sato
//
//============================

//------------------------
// インクルード
//------------------------
#include <stdio.h>
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "texture.h"
#include "ranking.h"
#include"score.h"
#include "gameover.h"
#include "tutorial.h"

//------------------------
// マクロ定義
//------------------------
#define CLASS_NAME	"WindowClass"	//ウインドウクラスの名前
#define	WINDOW_NAME	"ハッカソン"	//ウインドウの名前(キャプションに表示)
#define MAX_NAME (5)

//------------------------
// プロトタイプ宣言
//------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//------------------------
// グローバル変数
//------------------------
LPDIRECT3D9					g_pD3D = NULL;				//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9			g_pD3DDevice = NULL;		//Direct3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE;	//現在のモード

//========================
// メイン関数
//========================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInsetancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,							//ウインドウのスタイル
		WindowProc,							//ウインドウプロシージャ
		0,									//0にする(通常は使用しない)
		0,									//0にする(通常は使用しない)
		hInstance,							//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),		//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),			//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			//クライアント領域の背景色
		NULL,								//メニューバー
		CLASS_NAME,							//ウインドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)		//ファイルのアイコン
	};

	HWND hWnd;		//ウインドウハンドル(識別子)
	MSG msg;		//メッセージを格納する変数

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//画面サイズの構造体

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウインドウを生成
	hWnd = CreateWindowEx(0,						//拡張ウインドウスタイル
						  CLASS_NAME,				//ウインドウクラスの名前
						  WINDOW_NAME,				//ウインドウの名前
						  WS_OVERLAPPEDWINDOW,		//ウインドウスタイル
						  CW_USEDEFAULT,			//ウインドウの左上X座標
						  CW_USEDEFAULT,			//ウインドウの左上Y座標
						  SCREEN_WIDTH,				//ウインドウの幅
						  SCREEN_HEIGHT,			//ウインドウの高さ
						  NULL,						//親ウインドウのハンドル
						  NULL,						//メニューハンドルまたは子ウインドウID
						  hInstance,				//インスタンスハンドル
						  NULL);					//ウインドウ作成データ

	DWORD dwCurrentTime;	//現在時刻
	DWORD dwExecLastTime;	//現在に処理した時刻

	//初期化処理

	if (FAILED(Init(hInstance, hWnd, FALSE)))	//画面サイズ
	{//初期化処理が失敗した場合
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;					//初期化する
	dwExecLastTime = timeGetTime();		//現在時刻を取得

	//ウインドウの表示
	ShowWindow(hWnd, nCmdShow);		//ウインドウの表示状態を設定
	UpdateWindow(hWnd);				//クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);		//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);		//ウインドウプロシージャへメッセージを送出
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();		//現在時刻を取得

			if ((dwCurrentTime - dwExecLastTime) >= (100 / 60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;		//処理開始の時刻[現在時刻]を保存

				//更新処理
				Update();

				//描画処理
				Draw();
			}
		}
	}

	//終了処理
	//分解能を戻す
	timeEndPeriod(1);
	Uninit();

	//ウインドウクラスの登録解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//========================
// 初期化処理
//========================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	//プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));	//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;		//ゲーム画面(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;		//バックバッファの形式
	d3dpp.BackBufferCount = 1;					//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;		//デプスバッファとステンシバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;					//ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//リフレッシュシート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//インターバル

	//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行う)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3Dデバイスの生成(描画処理はハードウェア、頂点処理はCPUで行う)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// 入力処理の初期化
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//サウンドの初期化処理
	InitSound(hWnd);

	//テクスチャの読み込み
	LoadTexture();

	//モードの設定
	SetMode(g_mode);

	//フェードの設定
	InitFade(g_mode);

	return S_OK;
}


//========================
// 終了処理
//========================
void Uninit(void)
{
	//タイトル画面の終了
	UninitTitle();

	//ゲーム画面の終了
	UninitGame();

	//リザルト画面の終了
	UninitResult();

	//サウンドの終了処理
	UninitSound();

	//テクスチャの終了
	UninitTexture();

	// 入力処理の終了
	UninitInput();

	UninitTutorial();

	UninitGameOver();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//========================
// 更新処理
//========================
void Update(void)
{
	// 入力処理の更新
	UpdateInput();

	switch (g_mode)
	{
	case MODE_TITLE:
		//タイトルの更新
		UpdateTitle();
		break;
	case MODE_GAME:
		//ゲームの更新
		UpdateGame();
		break;
	case MODE_RESULT:
		//リザルトの更新
		UpdateResult();
		break;
	case MODE_RANKING:
		UpdateRanking();
		break;
	case MODE_GAMEOVER:
		UpdateGameOver();
		break;
	case MODE_TUTORIAL:
		UpdateTutorial();
		break;
	}

	//フェードの更新処理
	UpdateFade();
}

//========================
// 描画処理
//========================
void Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスの取得

	//画面クリア(バックバッファ&Zバッファのクリア)
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合
		switch (g_mode)
		{
		case MODE_TITLE:
			//タイトルの描画
			DrawTitle();
			break;
		case MODE_GAME:
			//ゲームの描画
			DrawGame();
			break;
		case MODE_RESULT:
			//リザルトの描画
			DrawResult();
			break;
		case MODE_RANKING:
			DrawRanking();
			break;
		case MODE_GAMEOVER:
			DrawGameOver();
			break;
		case MODE_TUTORIAL:
			DrawTutorial();
			break;
		}

		//フェードの描画処理
		DrawFade();
		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとZバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//========================
// モードの設定
//========================
void SetMode(MODE mode)
{
	//現在の画面の終了処理
	switch (g_mode)
	{
	case MODE_TITLE:
		//タイトルの終了
		UninitTitle();
		break;
	case MODE_GAME:
		//ゲームの終了処理
		UninitGame();
		break;
	case MODE_RESULT:
		//リザルトの終了処理
		UninitResult();
		break;
	case MODE_RANKING:
		UninitRanking();
		break;
	case MODE_GAMEOVER:
		UninitGameOver();
		break;
	case MODE_TUTORIAL:
		UninitTutorial();
		break;
	}

	//新しいモードの初期化
	switch (mode)
	{
	case MODE_TITLE:
		//タイトルの初期化処理
		InitTitle();
		break;
	case MODE_GAME:
		//ゲームの初期化処理
		InitGame();
		break;
	case MODE_RESULT:
		//リザルトの初期化処理
		InitResult();
		break;
	case MODE_RANKING:
		InitRanking();
		int pScore;
		pScore = GetScore();
		SetRanking(pScore);
		break;
	case MODE_GAMEOVER:
		InitGameOver();
		break;
	case MODE_TUTORIAL:
		InitTutorial();
		break;
	}

	g_mode = mode;	//現在の画面(モード)を切り替える*/
}

//========================
// モードを取得
//========================
MODE GetMode(void)
{
	return g_mode;
}

//========================
// ウインドウプロシージャ
//========================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//int nID;

	switch (uMsg)
	{
	case WM_DESTROY:		//ウインドウ破棄のメッセージ
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:		//キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:		//ESSキーが押された
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);		//既定の処理を返す
}

//========================
// デバイスの取得
//========================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//---------------------------------------
//セットテクスチャ(2d)
//---------------------------------------
void Settex(VERTEX_2D *pVtx, float left, float right, float top, float down)
{
	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(left, top);
	pVtx[1].tex = D3DXVECTOR2(right, top);
	pVtx[2].tex = D3DXVECTOR2(left, down);
	pVtx[3].tex = D3DXVECTOR2(right, down);

}
//---------------------------------------
//セットポス(2d)
//---------------------------------------
void SetNormalpos(VERTEX_2D *pVtx, float XUP, float XDW, float YUP, float YDW)
{
	pVtx[0].pos = D3DXVECTOR3(XUP, YUP, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(XDW, YUP, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(XUP, YDW, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(XDW, YDW, 0.0f);
}

