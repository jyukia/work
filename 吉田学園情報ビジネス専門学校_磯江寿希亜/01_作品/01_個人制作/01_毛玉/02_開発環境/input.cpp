//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "input.h"
#include "DirectInput.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"

//-----------------------------------------------------------------------------
//静的メンバ変数宣言
//-----------------------------------------------------------------------------
CInput *CInput::m_pInput = nullptr;//このクラスの情報

//*************************************************************************************
//コンストラクタ
//*************************************************************************************
CInput::CInput()
{
	m_pKeyboard = nullptr;		//キーボードの情報
	m_pJoyPad = nullptr;		//ジョイパッドの情報
}

//*************************************************************************************
//デストラクタ
//*************************************************************************************
CInput::~CInput()
{
}

//*************************************************************************************
//初期化
//*************************************************************************************
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(CDirectInput::Create(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//キーボードの生成
	m_pKeyboard = new CInputKeyboard;

	//キーボードの初期化処理
	if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//ジョイパッドの生成
	m_pJoyPad = new CInputJoyPad;

	//ジョイパッドの初期化処理
	if (FAILED(m_pJoyPad->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//*************************************************************************************
//終了処理
//*************************************************************************************
void CInput::Uninit()
{
	//キーボードの破棄
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	//ジョイパッドの破棄
	if (m_pJoyPad != nullptr)
	{
		m_pJoyPad->Uninit();
		delete m_pJoyPad;
		m_pJoyPad = nullptr;
	}

	//DirectInputオブジェクトの破棄
	CDirectInput::Break();
}

//*************************************************************************************
//更新処理
//*************************************************************************************
void CInput::Update()
{
	//キーボードの更新
	m_pKeyboard->Update();
	//ジョイパッドの更新
	m_pJoyPad->Update();
}

//*************************************************************************************
//インプットの生成
//*************************************************************************************
CInput *CInput::Create()
{
	//Inputの自己生成
	m_pInput = new CInput;
	return m_pInput;
}

//*************************************************************************************
//プレス処理(総合)
//*************************************************************************************
bool CInput::Press(STAN_DART_INPUT_KEY key)
{
	switch (key)
	{
	case KEY_UP:
		return Press(DIK_W) || Press(DIK_UP) || PressAll(JOYPAD_UP);
		break;
	case KEY_DOWN:
			return Press(DIK_S) || Press(DIK_DOWN) || PressAll(JOYPAD_DOWN);
		break;
	case KEY_LEFT:
			return Press(DIK_A) || Press(DIK_LEFT) || PressAll(JOYPAD_LEFT);
		break;
	case KEY_RIGHT:
			return Press(DIK_D) || Press(DIK_RIGHT) || PressAll(JOYPAD_RIGHT);
		break;
	case KEY_JUMP:
			return Press(DIK_SPACE) || PressAll(JOYPAD_A);
		break;
	case KEY_DECISION:
			return Press(DIK_RETURN) || PressAll(JOYPAD_B);
		break;
	case KEY_LEFT_ACTION:
			return Press(DIK_Z) || PressAll(JOYPAD_L1);
		break;
	case KEY_RIGHT_ACTION:
		return Press(DIK_C) || PressAll(JOYPAD_R1);
		break;
	case KEY_SPACE_ACTION:
			return Press(DIK_SPACE) || PressAll(JOYPAD_A);
		break;
	case KEY_UP_BUTTON:
			return Press(DIK_N) || PressAll(JOYPAD_Y);
		break;
	case KEY_DOWN_BUTTON:
			return Press(DIK_B) || PressAll(JOYPAD_A);
		break;
	case KEY_LEFT_BUTTON:
			return Press(DIK_V) || PressAll(JOYPAD_X);
		break;
	case KEY_RIGHT_BUTTON:
			return Press(DIK_M) || PressAll(JOYPAD_B);
		break;
	case KEY_BACK:
			return Press(DIK_BACKSPACE) || Press(DIK_B) || PressAll(JOYPAD_BACK) || PressAll(JOYPAD_A);
		break;
	case KEY_SHIFT:
			return Press(DIK_RSHIFT) || Press(DIK_LSHIFT) || PressAll(JOYPAD_L1);
		break;
	case KEY_MOVE:
			return Press(KEY_UP) || Press(KEY_DOWN) || Press(KEY_LEFT) || Press(KEY_RIGHT);
		break;
	case KEY_PAUSE:
			return Press(DIK_P) || PressAll(JOYPAD_START);
		break;
	default:
		break;
	}

	return false;
}

//*************************************************************************************
//トリガー処理(総合)
//*************************************************************************************
bool CInput::Trigger(STAN_DART_INPUT_KEY key)
{
	switch (key)
	{
	case KEY_UP:
		return Trigger(DIK_W) || Trigger(DIK_UP) || TriggerAll(JOYPAD_UP);
		break;
	case KEY_DOWN:
		return Trigger(DIK_S) || Trigger(DIK_DOWN) || TriggerAll(JOYPAD_DOWN);
		break;
	case KEY_LEFT:
		return Trigger(DIK_A) || Trigger(DIK_LEFT) || TriggerAll(JOYPAD_LEFT);
		break;
	case KEY_RIGHT:
		return Trigger(DIK_D) || Trigger(DIK_RIGHT) || TriggerAll(JOYPAD_RIGHT);
		break;
	case KEY_JUMP:
		return Trigger(DIK_SPACE) || TriggerAll(JOYPAD_A);
		break;
	case KEY_DECISION:
		return Trigger(DIK_RETURN) || TriggerAll(JOYPAD_B);
		break;
	case KEY_LEFT_ACTION:
		return Trigger(DIK_Z) || TriggerAll(JOYPAD_L1);
		break;
	case KEY_RIGHT_ACTION:
		return Trigger(DIK_C) || TriggerAll(JOYPAD_R1);
		break;
	case KEY_SPACE_ACTION:
		return Trigger(DIK_SPACE) || TriggerAll(JOYPAD_A);
		break;
	case KEY_UP_BUTTON:
		return Trigger(DIK_N) || TriggerAll(JOYPAD_Y);
		break;
	case KEY_DOWN_BUTTON:
		return Trigger(DIK_B) || TriggerAll(JOYPAD_A);
		break;
	case KEY_LEFT_BUTTON:
		return Trigger(DIK_V) || TriggerAll(JOYPAD_X);
		break;
	case KEY_RIGHT_BUTTON:
		return Trigger(DIK_M) || TriggerAll(JOYPAD_B);
		break;
	case KEY_BACK:
		return Trigger(DIK_BACKSPACE) || Trigger(DIK_B) || TriggerAll(JOYPAD_BACK) || TriggerAll(JOYPAD_A);
		break;
	case KEY_SHIFT:
		return Trigger(DIK_RSHIFT) || Trigger(DIK_LSHIFT) || TriggerAll(JOYPAD_L1);
		break;
	case KEY_MOVE:
		return Trigger(KEY_UP) || Trigger(KEY_DOWN) || Trigger(KEY_LEFT) || Trigger(KEY_RIGHT);
		break;
	case KEY_PAUSE:
		return Trigger(DIK_P) || TriggerAll(JOYPAD_START);
		break;
	default:
		break;
	}
	return false;
}

//*************************************************************************************
//リリース処理(総合)
//*************************************************************************************
bool CInput::Release(STAN_DART_INPUT_KEY key)
{
	switch (key)
	{
	case KEY_UP:
		return Release(DIK_W) || Release(DIK_UP) || ReleaseAll(JOYPAD_UP);
		break;
	case KEY_DOWN:
		return Release(DIK_S) || Release(DIK_DOWN) || ReleaseAll(JOYPAD_DOWN);
		break;
	case KEY_LEFT:
		return Release(DIK_A) || Release(DIK_LEFT) || ReleaseAll(JOYPAD_LEFT);
		break;
	case KEY_RIGHT:
		return Release(DIK_D) || Release(DIK_RIGHT) || ReleaseAll(JOYPAD_RIGHT);
		break;
	case KEY_JUMP:
		return Release(DIK_SPACE) || ReleaseAll(JOYPAD_A);
		break;
	case KEY_DECISION:
		return Release(DIK_RETURN) || ReleaseAll(JOYPAD_B);
		break;
	case KEY_LEFT_ACTION:
		return Release(DIK_Z) || ReleaseAll(JOYPAD_L1);
		break;
	case KEY_RIGHT_ACTION:
		return Release(DIK_C) || ReleaseAll(JOYPAD_R1);
		break;
	case KEY_SPACE_ACTION:
		return Release(DIK_SPACE) || ReleaseAll(JOYPAD_A);
		break;
	case KEY_UP_BUTTON:
		return Release(DIK_N) || ReleaseAll(JOYPAD_Y);
		break;
	case KEY_DOWN_BUTTON:
		return Release(DIK_B) || ReleaseAll(JOYPAD_A);
		break;
	case KEY_LEFT_BUTTON:
		return Release(DIK_V) || ReleaseAll(JOYPAD_X);
		break;
	case KEY_RIGHT_BUTTON:
		return Release(DIK_M) || ReleaseAll(JOYPAD_B);
		break;
	case KEY_BACK:
		return Release(DIK_BACKSPACE) || Release(DIK_B) || ReleaseAll(JOYPAD_BACK) || ReleaseAll(JOYPAD_A);
		break;
	case KEY_SHIFT:
		return Release(DIK_RSHIFT) || Release(DIK_LSHIFT) || ReleaseAll(JOYPAD_L1);
		break;
	case KEY_MOVE:
		return Release(KEY_UP) || Release(KEY_DOWN) || Release(KEY_LEFT) || Release(KEY_RIGHT);
		break;
	case KEY_PAUSE:
		return Release(DIK_P) || ReleaseAll(JOYPAD_START);
		break;
	default:
		break;
	}

	return false;
}

//*************************************************************************************
//プレス処理(コントローラー指定)
//*************************************************************************************
bool CInput::Press(STAN_DART_INPUT_KEY key, int nNum)
{
	switch (key)
	{
	case KEY_UP:
		return nNum == -1 ? Press(DIK_W) || Press(DIK_UP) : Press(JOYPAD_UP, nNum);
		break;
	case KEY_DOWN:
		return nNum == -1 ? Press(DIK_S) || Press(DIK_DOWN) : Press(JOYPAD_DOWN, nNum);
		break;
	case KEY_LEFT:
		return nNum == -1 ? Press(DIK_A) || Press(DIK_LEFT) : Press(JOYPAD_LEFT, nNum);
		break;
	case KEY_RIGHT:
		return nNum == -1 ? Press(DIK_D) || Press(DIK_RIGHT) : Press(JOYPAD_RIGHT, nNum);
		break;
	case KEY_JUMP:
		return nNum == -1 ? Press(DIK_SPACE) : Press(JOYPAD_A, nNum);
		break;
	case KEY_DECISION:
		return nNum == -1 ? Press(DIK_RETURN) : Press(JOYPAD_B, nNum);
		break;
	case KEY_LEFT_ACTION:
		return nNum == -1 ? Press(DIK_Z) : Press(JOYPAD_L1, nNum);
		break;
	case KEY_RIGHT_ACTION:
		return nNum == -1 ? Press(DIK_C) : Press(JOYPAD_R1, nNum);
		break;
	case KEY_SPACE_ACTION:
		return nNum == -1 ? Press(DIK_SPACE) : Press(JOYPAD_A, nNum);
		break;
	case KEY_UP_BUTTON:
		return nNum == -1 ? Press(DIK_N) : Press(JOYPAD_Y, nNum);
		break;
	case KEY_DOWN_BUTTON:
		return nNum == -1 ? Press(DIK_B) : Press(JOYPAD_A, nNum);
		break;
	case KEY_LEFT_BUTTON:
		return nNum == -1 ? Press(DIK_V) : Press(JOYPAD_X, nNum);
		break;
	case KEY_RIGHT_BUTTON:
		return nNum == -1 ? Press(DIK_M) : Press(JOYPAD_B, nNum);
		break;
	case KEY_BACK:
		return Press(DIK_BACKSPACE) || Press(DIK_B) || Press(JOYPAD_BACK, nNum) || Press(JOYPAD_A, nNum);
		break;
	case KEY_SHIFT:
		return Press(DIK_RSHIFT) || Press(DIK_LSHIFT) || Press(JOYPAD_L1, nNum);
		break;
	case KEY_MOVE:
		return Press(KEY_UP, nNum) || Press(KEY_DOWN, nNum) || Press(KEY_LEFT, nNum) || Press(KEY_RIGHT, nNum);
		break;
	case KEY_PAUSE:
		return Press(DIK_P) || Press(JOYPAD_START, nNum);
		break;
	default:
		break;
	}

	return false;
}

//*************************************************************************************
//トリガー処理(コントローラー指定)
//*************************************************************************************
bool CInput::Trigger(STAN_DART_INPUT_KEY key, int nNum)
{
	switch (key)
	{
	case KEY_UP:
		return nNum == -1 ? Trigger(DIK_W) || Trigger(DIK_UP) : Trigger(JOYPAD_UP, nNum);
		break;
	case KEY_DOWN:
		return nNum == -1 ? Trigger(DIK_S) || Trigger(DIK_DOWN) : Trigger(JOYPAD_DOWN, nNum);
		break;
	case KEY_LEFT:
		return nNum == -1 ? Trigger(DIK_A) || Trigger(DIK_LEFT) : Trigger(JOYPAD_LEFT, nNum);
		break;
	case KEY_RIGHT:
		return nNum == -1 ? Trigger(DIK_D) || Trigger(DIK_RIGHT) : Trigger(JOYPAD_RIGHT, nNum);
		break;
	case KEY_JUMP:
		return nNum == -1 ? Trigger(DIK_SPACE) : Trigger(JOYPAD_A, nNum);
		break;
	case KEY_DECISION:
		return nNum == -1 ? Trigger(DIK_RETURN) : Trigger(JOYPAD_B, nNum);
		break;
	case KEY_LEFT_ACTION:
		return nNum == -1 ? Trigger(DIK_Z) : Trigger(JOYPAD_L1, nNum);
		break;
	case KEY_RIGHT_ACTION:
		return nNum == -1 ? Trigger(DIK_C) : Trigger(JOYPAD_R1, nNum);
		break;
	case KEY_SPACE_ACTION:
		return nNum == -1 ? Trigger(DIK_SPACE) : Trigger(JOYPAD_A, nNum);
		break;
	case KEY_UP_BUTTON:
		return nNum == -1 ? Trigger(DIK_N) : Trigger(JOYPAD_Y, nNum);
		break;
	case KEY_DOWN_BUTTON:
		return nNum == -1 ? Trigger(DIK_B) : Trigger(JOYPAD_A, nNum);
		break;
	case KEY_LEFT_BUTTON:
		return nNum == -1 ? Trigger(DIK_V) : Trigger(JOYPAD_X, nNum);
		break;
	case KEY_RIGHT_BUTTON:
		return nNum == -1 ? Trigger(DIK_M) : Trigger(JOYPAD_B, nNum);
		break;
	case KEY_BACK:
		return Trigger(DIK_BACKSPACE) || Trigger(DIK_B) || Trigger(JOYPAD_BACK, nNum) || Trigger(JOYPAD_A, nNum);
		break;
	case KEY_SHIFT:
		return Trigger(DIK_RSHIFT) || Trigger(DIK_LSHIFT) || Trigger(JOYPAD_L1, nNum);
		break;
	case KEY_MOVE:
		return Trigger(KEY_UP, nNum) || Trigger(KEY_DOWN, nNum) || Trigger(KEY_LEFT, nNum) || Trigger(KEY_RIGHT, nNum);
		break;
	case KEY_PAUSE:
		return Trigger(DIK_P) || Trigger(JOYPAD_START, nNum);
		break;
	default:
		break;
	}

	return false;
}

//*************************************************************************************
//リリース処理(コントローラー指定)
//*************************************************************************************
bool CInput::Release(STAN_DART_INPUT_KEY key, int nNum)
{
	switch (key)
	{
	case KEY_UP:
		return nNum == -1 ? Release(DIK_W) || Release(DIK_UP) : Release(JOYPAD_UP, nNum);
		break;
	case KEY_DOWN:
		return nNum == -1 ? Release(DIK_S) || Release(DIK_DOWN) : Release(JOYPAD_DOWN, nNum);
		break;
	case KEY_LEFT:
		return nNum == -1 ? Release(DIK_A) || Release(DIK_LEFT) : Release(JOYPAD_LEFT, nNum);
		break;
	case KEY_RIGHT:
		return nNum == -1 ? Release(DIK_D) || Release(DIK_RIGHT) : Release(JOYPAD_RIGHT, nNum);
		break;
	case KEY_JUMP:
		return nNum == -1 ? Release(DIK_SPACE) : Release(JOYPAD_A, nNum);
		break;
	case KEY_DECISION:
		return nNum == -1 ? Release(DIK_RETURN) : Release(JOYPAD_B, nNum);
		break;
	case KEY_LEFT_ACTION:
		return nNum == -1 ? Release(DIK_Z) : Release(JOYPAD_L1, nNum);
		break;
	case KEY_RIGHT_ACTION:
		return nNum == -1 ? Release(DIK_C) : Release(JOYPAD_R1, nNum);
		break;
	case KEY_SPACE_ACTION:
		return nNum == -1 ? Release(DIK_SPACE) : Release(JOYPAD_A, nNum);
		break;
	case KEY_UP_BUTTON:
		return nNum == -1 ? Release(DIK_N) : Release(JOYPAD_Y, nNum);
		break;
	case KEY_DOWN_BUTTON:
		return nNum == -1 ? Release(DIK_B) : Release(JOYPAD_A, nNum);
		break;
	case KEY_LEFT_BUTTON:
		return nNum == -1 ? Release(DIK_V) : Release(JOYPAD_X, nNum);
		break;
	case KEY_RIGHT_BUTTON:
		return nNum == -1 ? Release(DIK_M) : Release(JOYPAD_B, nNum);
		break;
	case KEY_BACK:
		return Release(DIK_BACKSPACE) || Release(DIK_B) || Release(JOYPAD_BACK, nNum) || Release(JOYPAD_A, nNum);
		break;
	case KEY_SHIFT:
		return Release(DIK_RSHIFT) || Release(DIK_LSHIFT) || Release(JOYPAD_L1, nNum);
		break;
	case KEY_MOVE:
		return Release(KEY_UP, nNum) || Release(KEY_DOWN, nNum) || Release(KEY_LEFT, nNum) || Release(KEY_RIGHT, nNum);
		break;
	case KEY_PAUSE:
		return Release(DIK_P) || Release(JOYPAD_START, nNum);
		break;
	default:
		break;
	}

	return false;
}

//*************************************************************************************
//プレス処理(キーボード)
//*************************************************************************************
bool CInput::Press(int nKey)
{
	return m_pKeyboard->GetKeyboardPress(nKey);
}

//*************************************************************************************
//トリガー処理(キーボード)
//*************************************************************************************
bool CInput::Trigger(int nkey)
{
	return m_pKeyboard->GetKeyboardTrigger(nkey);
}

//*************************************************************************************
//リリース処理(キーボード)
//*************************************************************************************
bool CInput::Release(int nkey)
{
	return m_pKeyboard->GetKeyboardRelease(nkey);
}

//*************************************************************************************
//プレス処理(ジョイパッド)
//*************************************************************************************
bool CInput::Press(DirectJoypad key, int nNum)
{
	return m_pJoyPad->GetPress(key, nNum);
}

//*************************************************************************************
//トリガー処理(ジョイパッド)
//*************************************************************************************
bool CInput::Trigger(DirectJoypad key, int nNum)
{
	return m_pJoyPad->GetTrigger(key, nNum);
}

//*************************************************************************************
//リリース処理(ジョイパッド)
//*************************************************************************************
bool CInput::Release(DirectJoypad key, int nNum)
{
	return m_pJoyPad->GetRelease(key, nNum);
}

//*************************************************************************************
//プレス処理(ジョイパッド)
//*************************************************************************************
bool CInput::PressAll(DirectJoypad key)
{
	return m_pJoyPad->GetPressAll(key);
}

//*************************************************************************************
//トリガー処理(ジョイパッド)
//*************************************************************************************
bool CInput::TriggerAll(DirectJoypad key)
{
	return m_pJoyPad->GetTriggerAll(key);
}

//*************************************************************************************
//リリース処理(ジョイパッド)
//*************************************************************************************
bool CInput::ReleaseAll(DirectJoypad key)
{
	return m_pJoyPad->GetReleaseAll(key);
}

//*************************************************************************************
// 入力したデバイスの番号を取得 (Press)
//*************************************************************************************
std::vector<int> CInput::PressDevice(STAN_DART_INPUT_KEY key)
{
	std::vector<int> inputedDeviceIndex;

	// キーボード入力の調査
	if (Release(key, -1))
	{
		inputedDeviceIndex.push_back(-1);
	}

	// JoyPad入力の調査
	for (int i = 0; i < m_pJoyPad->GetJoyPadNumMax(); i++)
	{
		if (Release(key, i))
		{
			inputedDeviceIndex.push_back(i);
		}
	}

	return inputedDeviceIndex;
}

//*************************************************************************************
// 入力したデバイスの番号を取得 (Trigger)
//*************************************************************************************
std::vector<int> CInput::TriggerDevice(STAN_DART_INPUT_KEY key)
{
	std::vector<int> inputedDeviceIndex;

	// キーボード入力の調査
	if (Trigger(key, -1))
	{
		inputedDeviceIndex.push_back(-1);
	}

	// JoyPad入力の調査
	for (int i = 0; i < m_pJoyPad->GetJoyPadNumMax(); i++)
	{
		if (Trigger(key, i))
		{
			inputedDeviceIndex.push_back(i);
		}
	}

	return inputedDeviceIndex;
}

//*************************************************************************************
// 入力したデバイスの番号を取得 (Release)
//*************************************************************************************
std::vector<int> CInput::ReleaseDevice(STAN_DART_INPUT_KEY key)
{
	std::vector<int> inputedDeviceIndex;

	// キーボード入力の調査
	if (Release(key, -1))
	{
		inputedDeviceIndex.push_back(-1);
	}

	// JoyPad入力の調査
	for (int i = 0; i < m_pJoyPad->GetJoyPadNumMax(); i++)
	{
		if (Release(key, i))
		{
			inputedDeviceIndex.push_back(i);
		}
	}

	return inputedDeviceIndex;
}

//*************************************************************************************
//十字キーのベクトル
//*************************************************************************************
D3DXVECTOR3 CInput::VectorMoveKey()
{
	D3DXVECTOR3 VectorMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (m_pJoyPad->GetJoyPadNumMax() == 0)
	{
		return VectorMove;
	}
	int nCheck = m_pJoyPad->GetCross();

	if (nCheck > 360 || nCheck < 0)
	{//十字キーの角度が指定外だったら０を返す
		return VectorMove;
	}

	float fRot = D3DXToRadian(nCheck);

	VectorMove.x = sinf(fRot);
	VectorMove.y = -cosf(fRot);

	//長さ１のベクトル変換
	D3DXVec3Normalize(&VectorMove, &VectorMove);

	return VectorMove;
}

//*************************************************************************************
//ジョイスティックのベクトル
//*************************************************************************************
D3DXVECTOR3 CInput::VectorMoveJoyStick(int nNum, bool bleftandright)
{
	D3DXVECTOR3 VectorMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (m_pJoyPad->GetJoyPadNumMax() == 0)
	{
		return VectorMove;
	}

	VectorMove = m_pJoyPad->GetJoyStickData(nNum, bleftandright);
	//長さ１のベクトル変換
	D3DXVec3Normalize(&VectorMove, &VectorMove);
	return VectorMove;
}

int CInput::GetAcceptJoyPadCount()
{
	return m_pJoyPad->GetJoyPadNumMax();
}
