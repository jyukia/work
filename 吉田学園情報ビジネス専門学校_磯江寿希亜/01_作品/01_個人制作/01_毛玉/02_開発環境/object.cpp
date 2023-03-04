//=============================================================================
// インクルードファイル
//=============================================================================
#include <assert.h>
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
int CObject::m_nNumAll = 0;
CObject *CObject::m_pTop[PRIORITY_LEVELMAX] = {};
CObject *CObject::m_pCurrent[PRIORITY_LEVELMAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CObject::CObject(int nPriority /* = PRIORITY_LEVEL0 */) :
	m_pNext(nullptr),
	m_pPrev(nullptr),
	m_bDeath(false),
	m_canPoseUpdate(false)
{
	//プライオリティの保存
	m_nPriority = nPriority;

	//オブジェクト(自分自身)を、リストに追加
	if (m_pTop[nPriority] == nullptr)
	{
		m_pTop[nPriority] = this;
	}
	else if (m_pTop[nPriority] != nullptr)
	{
		m_pCurrent[nPriority]->m_pNext = this;
		this->m_pPrev = m_pCurrent[nPriority];
	}

	m_pCurrent[nPriority] = this;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject::~CObject()
{

}

//=============================================================================
// 全てのインスタンスの終了処理
//=============================================================================
void CObject::UninitAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITY_LEVELMAX; nPriority++)
	{
		CObject *pObject = m_pTop[nPriority];

		while (pObject)
		{
			//pNextの保存
			CObject *pObjectNext = pObject->m_pNext;	//Update()で削除されると、pNextも消えるので事前に保存しておく

			pObject->Release();		// 死亡状態にする

									//pObjectにpObjectのpNextを代入
			pObject = pObjectNext;
		}

		pObject = m_pTop[nPriority];

		static int a = 0;
		while (pObject != nullptr)
		{
			a++;
			//pNextの保存
			CObject *pObjectNext = pObject->m_pNext;	//Update()で削除されると、pNextも消えるので事前に保存しておく

			if (pObject->m_bDeath == true)
			{
				pObject->Death();
			}

			//pObjectにpObjectのpNextを代入
			pObject = pObjectNext;
		}
		a = 0;
	}
}

//
template<typename Func>
inline void CObject::AllProcess(Func func)
{
	for (int nPriority = 0; nPriority < PRIORITY_LEVELMAX; nPriority++)
	{
		CObject *pObject = m_pTop[nPriority];

		while (pObject != nullptr)
		{
			//pNextの保存
			CObject *pObjectNext = pObject->m_pNext;

			func(pObject);

			//pObjectにpObjectのpNextを代入
			pObject = pObjectNext;
		}
	}
}
//=============================================================================
// 全てのインスタンスの更新処理
//=============================================================================
void CObject::UpdateAll(void)
{
	auto update = [](CObject* pObject)
	{
		bool isPause = false;
		if (pObject->m_bDeath == false)
		{
			if (pObject->GetObjType() == OBJTYPE_PAUSE)
			{
				isPause = true;
			}
			if (isPause)
			{
				if (pObject->m_canPoseUpdate)
				{
					pObject->Update();
				}
			}
			else
			{
				pObject->Update();
			}
		}
	};

	AllProcess(update);

	auto Death = [](CObject* pObject)
	{
		if (pObject->m_bDeath == true)
		{
			pObject->Death();
		}
	};

	AllProcess(Death);
}

//=============================================================================
// 全てのインスタンスの描画処理
//=============================================================================
void CObject::DrawAll(void)
{
	auto Death = [](CObject* pObject)
	{
		if (pObject->m_bDeath == false)
		{
			//描画処理の関数呼び出し
			pObject->Draw();
		}
	};

		AllProcess(Death);
}

//=============================================================================
// オブジェクト破棄処理
//=============================================================================
void CObject::Death(void)
{
	//オブジェクトの次に情報が入っているとき
	if (m_pNext != nullptr)
	{
		//オブジェクトの前に情報が入っているとき
		if (m_pPrev != nullptr)
		{
			//自分自身のm_pNextを前のオブジェクトのm_pNextに代入
			m_pPrev->m_pNext = this->m_pNext;

			//自分自身のm_pPrevを後ろのm_pPrevに代入
			m_pNext->m_pPrev = this->m_pPrev;
		}

		//オブジェクトの前に情報が入っていないとき
		else
		{
			//自分自身のm_pNextを先頭に代入
			m_pTop[m_nPriority] = this->m_pNext;

			//自分自身のm_pPrevを次のオブジェクトのm_pPrevに代入
			m_pNext->m_pPrev = this->m_pPrev;
		}
	}

	//オブジェクトの次に情報が入っていないとき
	else
	{
		//オブジェクトの前に情報が入っているとき
		if (m_pPrev != nullptr)
		{
			//後ろのm_pPrevにnullptrを代入
			m_pCurrent[m_nPriority] = this->m_pPrev;

			//後ろのm_pNextを前のオブジェクトのm_pNextに代入
			m_pPrev->m_pNext = this->m_pNext;
		}

		//オブジェクトの前に情報が入っていないとき
		else
		{
			//先頭のオブジェクトにnullptrを代入
			m_pTop[m_nPriority] = nullptr;

			//後ろのオブジェクトにnullptrを代入
			m_pCurrent[m_nPriority] = nullptr;
		}
	}

	//オブジェクト(自分自身)を、破棄
	this->Uninit();		// 終了処理
	delete this;
}

//=============================================================================
// インスタンスの解放処理
//=============================================================================
void CObject::Release()
{
	m_bDeath = true;
}

//=============================================================================
// モード以外だったら破棄処理
//=============================================================================
void CObject::ModeRelease()
{
	auto Release = [](CObject* pObject)
	{
		if (pObject->GetObjType() != OBJTYPE_MODE)
		{
			//終了処理の関数呼び出し
			pObject->Release();
		}
		else
		{
			int a = 0;
		}
	};
	
	AllProcess(Release);

	auto Death = [](CObject* pObject)
	{
		if (pObject->GetObjType() != OBJTYPE_MODE)
		{
			pObject->Death();
		}
	};

	AllProcess(Death);
}

//=============================================================================
// オブジェクトの種類
//=============================================================================
void CObject::SetType(const EObjType type)
{
	m_objType = type;
}

//=============================================================================
// オブジェクトのタイプを返す処理
//=============================================================================
CObject::EObjType CObject::GetObjType(void)
{
	return m_objType;
}