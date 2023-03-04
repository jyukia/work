//
//ファイルヘッダーコメント
//
#ifndef _Number_H_
#define _Number_H_

#include "renderer.h"
#include"application.h"
#include"object2D.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************


//*****************************************************************************
//マクロ定義
//*****************************************************************************

class CNumber : public CObject2D
{
public:
	//コンストラクタ
	explicit CNumber(int nPriority);

	//デストラクタ
	~CNumber() override;

	//初期化
	HRESULT Init() override;

	static CNumber* Create(const char *aFileName, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nPriority);

private:

};
#endif