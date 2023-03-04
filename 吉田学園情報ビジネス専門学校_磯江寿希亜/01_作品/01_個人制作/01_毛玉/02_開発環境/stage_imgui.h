////**************************************************
//// 
//// particle_imgui.h
//// Author  : katsuki mizuki
//// Author  : Yuda Kaito
//// 
////**************************************************
//#ifndef _STAGE_IMGUI_H_	// このマクロが定義されてなかったら
//#define _STAGE_IMGUI_H_	// 2重インクルード防止のマクロ定義
//
////==================================================
//// インクルード
////==================================================
//#include "imgui_property.h"
//
////--------------------------------------------------
//// パーティクル用のImgui表示クラス
////--------------------------------------------------
//class CStageImgui : public CImguiProperty
//{
//public:
//
//
//	CStageImgui();
//	~CStageImgui();
//
//	HWND Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice) override;
//	void Uninit(HWND hWnd, WNDCLASSEX wcex) override;
//	bool Update() override;
//	void Draw() override;
//
//	int GetMesh() const { return sliderIntmesh; }
//	int GetModel() const { return sliderIntmodel; }
//
//	void SetMeshPos(float x, float y, float z);
//
//	void funcFileLoad(HWND hWnd);
//
//private: // プライベート関数
//	void TaskBarUpdate();
//
//private: // メンバー変数
//
//	const int MeshMax = 100;
//	static const int	MAX_TEXT = 1024;		// テキストの最大文字数
//	const char*	WINDOW_NAME = "test";	// ウインドウの名前 (キャプションに表示)
//
//	D3DXVECTOR3 sliderRot;			// meshの回転やりたかった
//
//	bool m_Gura = false;			// 重力
//	bool m_MoveIron = false;		// 鉄球動かさない設定（スクロールバー）
//
//	int sliderIntmodel;
//	int indexBuilding = 0;			// 編集したいモデルの表示ID（コンボボックス）
//	std::string NowModelName;		// 設置したモデルの表示名（コンボボックス）
//	float sliderPos3[3];			// 回転するタマの座標（受け取る箱）	
//	float sliderRot3[3];			// 回転するタマの回転（受け取る箱）	
//	float sliderNowRot3[3];			// 回転するタマの回転（受け取る箱）	
//
//	int sliderIntmesh;						// meshのType選択（スクロールバー）
//	unsigned int indexModel = 0;					// 編集したいモデルの表示ID（コンボボックス）
//	unsigned int indexTex = 0;				// 編集したいテクスチャの表示ID（コンボボックス）
//	unsigned int indexmeshAnimation = 0;	// 編集したいメッシュのアニメーション番号表示ID（コンボボックス）
//	unsigned int indexmeshNumber = 0;		// 編集したいメッシュの番号の表示ID（コンボボックス）
//	unsigned int indexCamera = 0;			// 編集したいカメラAnimationの番号の表示ID（コンボボックス）
//	unsigned int indexCameraAnimation = 0;	// 編集したいカメラAnimationの中の座標番号の表示ID（コンボボックス）
//	std::string NowMeshName;				// 編集したいmeshの表示名（コンボボックス）
//	std::string NowMeshNumberName;			// 編集したいアニメーションNumberの表示名（コンボボックス）
//	std::string NowCameraNumberName;		// 編集したいCameraNumberの表示名（コンボボックス）
//	std::string NowCameraAnimationNumberName;		// 編集したいCameraアニメーションNumberの表示名（コンボボックス）
//	bool Animation = false;					// アニメーションするかしないか
//
//	float m_PosVSet[3];			// 自由の時座標設定するよう	
//	float m_PosRSet[3];			// 自由の時座標設定するよう	
//	int m_KeySet;
//
//	// メッシュのpos
//	float m_fMeshPos[3];
//
//};
//
//#endif // !_IMGUI_PROPERTY_H_
