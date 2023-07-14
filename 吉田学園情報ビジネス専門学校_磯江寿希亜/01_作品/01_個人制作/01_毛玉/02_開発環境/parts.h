#ifndef _PARTS_H_			// このマクロ定義がされてなかったら
#define _PARTS_H_			// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "objectX.h"
#include "main.h"

//=============================================================================
// パーツクラス
// Author : 唐�ｱ結斗
// 概要 : パーツ生成を行うクラス
//=============================================================================
class CParts : public CObjectX
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CParts *Create();			// パーツの生成

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CParts();
	~CParts();

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	void SetPosOrigin(const D3DXVECTOR3 &posOrigin) { m_posOrigin = posOrigin; }		// 元の位置のセッター
	void SetRotOrigin(const D3DXVECTOR3 &rotOrigin) { m_rotOrigin = rotOrigin; }		// 元の向きのセッター
	void SetPosDest(const D3DXVECTOR3 &posDest) { m_posDest = posDest; }				// 目的位置のセッター
	void SetRotDest(const D3DXVECTOR3 &rotDest) { m_rotDest = rotDest; }				// 目的向きのセッター
	D3DXVECTOR3 GetPosOrigin() { return m_posOrigin; }									// 元の位置のゲッター
	D3DXVECTOR3 GetRotOrigin() { return m_rotOrigin; }									// 元の向きのゲッター
	D3DXVECTOR3 GetPosDest() { return m_posDest; }										// 目的位置のゲッター
	D3DXVECTOR3 GetRotDest() { return m_rotDest; }										// 目的向きのゲッター

private:
	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	D3DXVECTOR3 m_posOrigin;		// 元の位置
	D3DXVECTOR3 m_rotOrigin;		// 元の向き
	D3DXVECTOR3 m_posDest;			// 目的の位置
	D3DXVECTOR3 m_rotDest;			// 目的の向き
};

#endif
