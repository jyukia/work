//#ifndef _MAP_CAMERA_H_
//#define _MAP_CAMERA_H_
//
//#include "main.h"
//
////=============================================================================
////マクロ定義
////=============================================================================
//#define CAMERA_SPEED	(10.0f)		//カメラの移動速度
//
////=============================================================================
//// クラスの定義
////=============================================================================
//class CMapcamera
//{
//public:
//	//-------------------------------------------------------------------------
//	// コンストラクタとデストラクタ
//	//-------------------------------------------------------------------------
//	explicit CMapcamera();
//	~CMapcamera();
//
//	//-------------------------------------------------------------------------
//	// メンバー関数
//	//-------------------------------------------------------------------------
//	HRESULT Init(void);					// 初期化処理
//	void Uninit(void);					// 終了処理
//	void Update(void);					// 更新処理
//
//	void SetCamera(bool bfixed, bool btypecom);				// 設定処理
//	void SetViewport();	//初期化の為
//
//	static CMapcamera *Create();		// 生成処理
//
//	void SetTarget();
//
//	void SetSIz_Camera(D3DXVECTOR2 siz);
//	void SetPos_Camera(D3DXVECTOR2 pos);
//	void SetPosV(D3DXVECTOR3 posv) { m_posV = posv; }
//	void SetPosR(D3DXVECTOR3 posr) { m_posR = posr; }
//
//
//	D3DXVECTOR3 GetRot() { return m_rot; }
//
//	D3DXMATRIX GetMtxView() { return m_mtxView; }
//	D3DXMATRIX GetProjection() { return m_mtxProjection; }
//
//	D3DVIEWPORT9 GetViewPort() {return m_game_viewport;}
//
//private:
//	//-------------------------------------------------------------------------
//	// メンバー変数
//	//-------------------------------------------------------------------------
//
//	D3DXVECTOR3	m_posV;				//[2]視点
//	D3DXVECTOR3	m_posR;				//[2]注視点
//	D3DXVECTOR3	m_vecU;				//[2]上方向ベクトル
//	D3DXVECTOR3	m_posVDest;			//目的の視点
//	D3DXVECTOR3	m_posRDest;			//目的の注視点
//	D3DXMATRIX	m_mtxProjection;	// [2]プロジェクションマトリックス
//	D3DXMATRIX	m_mtxView;			//[2] ビューマトリックス
//	float		m_fDistance;		//視点から注視点の距離
//	D3DXVECTOR3 m_rot;		//向き
//
//	D3DXVECTOR3 m_CamPosVm;	//[2]計算後
//	D3DXVECTOR3 m_CamPosRm;	//[2]
//
//	D3DXVECTOR2 m_Siz;		//画面サイズ
//
//	D3DVIEWPORT9 m_game_viewport;	//[2]画面分割
//
//protected:
//
//	CRenderer * m_prenderer;
//};
//#endif