#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
//#include"stage_imgui.h"
//=============================================================================
// クラスの前方定義
//=============================================================================
class CInput;
class CCamera;
class CMapcamera;
class CLight;
class CObjectX;
class CMeshfield;
class CTime;
class CTexture;
class CObjectXGroup;
class CSound;
class CDebugProc;
class CStageImgui;
class CMode;
class CMeshLine;
class CItem;
class Cpreparation;
class CTimer;
class CInputJoyPad;

//=============================================================================
// クラスの定義
//=============================================================================
class CApplication
{
private:
	CApplication();

	static CApplication *m_pApplication;
public:
	//シングルトンでのインスタンスの取得
	static CApplication* Getinstnce() {return m_pApplication != nullptr ? m_pApplication : m_pApplication = new CApplication;}

	//===============================
	//計算のため追加
	//===============================
	struct VALUE_INT
	{
		// 変数宣言
		int   x, y;

		constexpr VALUE_INT() : x(0), y(0) { }
		constexpr VALUE_INT(int _x, int _y) : x(_x), y(_y) { }

		// 加算
		VALUE_INT operator +(const VALUE_INT &texPattern) {
			VALUE_INT value;
			value.x = x + texPattern.x;
			value.y = y + texPattern.y;
			return value;
		}

		// 加算(+=)
		VALUE_INT &operator +=(const VALUE_INT &texPattern) {
			x += texPattern.x;
			y += texPattern.y;
			return *this;
		}

		// 減算
		VALUE_INT operator -(const VALUE_INT &texPattern) {
			VALUE_INT value;
			value.x = x - texPattern.x;
			value.y = y - texPattern.y;
			return value;
		}

		// 減算(-=)
		VALUE_INT &operator -=(const VALUE_INT &texPattern) {
			x -= texPattern.x;
			y -= texPattern.y;
			return *this;
		}

		// 乗算
		VALUE_INT operator *(const VALUE_INT &texPattern) {
			VALUE_INT value;
			value.x = x * texPattern.x;
			value.y = y * texPattern.y;
			return value;
		}

		// 乗算(*=)
		VALUE_INT &operator *=(const VALUE_INT &texPattern) {
			x *= texPattern.x;
			y *= texPattern.y;
			return *this;
		}

		// 代入
		VALUE_INT &operator =(const VALUE_INT &texPattern) {
			x = texPattern.x;
			y = texPattern.y;
			return *this;
		}
	};


	//=============================================================================
	// 列挙型
	//=============================================================================
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_GAME1,
		MODE_SELECT_STAGE,
		MODE_RESULT,
		MODE_RANKING,
		MODE_TUTORIAL,
		MODE_MAX
	};

	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	~CApplication();
	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetMode(MODE mode);
	MODE GetMode();
	CRenderer *GetRenderer();
	CInput *GetInput();

	CCamera *GetCamera() { return m_pCamera; }
	CMapcamera*GetMapCamera() { return m_pMapCamera; }

	CTexture *GetTexture() { return m_pTexture; }
	CObjectXGroup *GetObjectXGroup() { return m_pObjectXGroup; }
	CSound *GetSound() { return m_pSound; }
	//CStageImgui *GetImgui() { return m_Imgui; }
	CMode *GetpMode() { return m_pMode; }
	CItem* GetItem() { return m_Item; }

	CLight *GetLight() { return m_Light; }

	Cpreparation * GetPreparation() { return m_preparation; }

	HWND GetHWnd() { return Hwnd; }

	CTimer *GetTimer() {return m_Timer;}
	
	static CInputJoyPad *GetJoy() { return m_pJoy; }											// ジョイパッドのゲッター

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	static CInputJoyPad *m_pJoy;


	HWND Hwnd;

	CRenderer *m_pRenderer;
	CInput *m_pInput;
	MODE m_mode;
	VALUE_INT m_calculation;
	CMode *m_pMode;
	CCamera *m_pCamera;
	CMapcamera *m_pMapCamera;

	CTexture *m_pTexture;
	CObjectXGroup *m_pObjectXGroup;
	CSound *m_pSound;
	CDebugProc *m_pDebugProc;			// デバック表示

	//CStageImgui *m_Imgui;
	CLight *m_Light;
	CItem *m_Item;
	Cpreparation *m_preparation;
	CTimer * m_Timer;
};//


//--------------------------------------------------
// Author : Hamada Ryuuga
// Author : Yuda Kaito
// 引数1  : float X        // 時間	0.0f ～ 1.0fの間
// 返値  : float / 計算結果
//--------------------------------------------------
namespace ease
{
	// 正弦で算出
	float InSine(float x);
	float OutSine(float x);
	float InOutSine(float x);

	// 2の累乗で算出
	float InQuad(float x);
	float OutQuad(float x);
	float InOutQuad(float x);

	// 3の累乗で算出
	float InCubic(float x);
	float OutCubic(float x);
	float InOutCubic(float x);

	// 4の累乗で算出
	float InQuart(float x);
	//float OutQuart(float x);
	//float InOutQuart(float x);

	// 5の累乗で算出
	float InQuint(float x);
	//float OutQuint(float x);
	//float InOutQuint(float x);

	// 指数関数で算出
	float InExpo(float x);
	//float OutExpo(float x);
	//float InOutExpo(float x);

	float InCirc(float x);
	//float OutCirc(float x);
	//float InOutCirc(float x);

	float InBack(float x, float s = 1.70158f);
	//float OutBack(float x);
	//float InOutBack(float x);

	float InElastic(float x, float c = (2.f * D3DX_PI) / 3.f);
	float OutElastic(float x, float c = (2.f * D3DX_PI) / 3.f);
	float InOutElastic(float x, float c = (2.f * D3DX_PI) / 4.5f);

	float OutBounce(float x, float n = 7.5625f, float d = 2.75f);
	float InBounce(float x, float n = 7.5625f, float d = 2.75f);
	float InOutBounce(float x, float n = 7.5625f, float d = 2.75f);

	float SinCurve(int nTime, float fCycle);
	float CosCurve(int nTime, float fCycle);
}


#endif