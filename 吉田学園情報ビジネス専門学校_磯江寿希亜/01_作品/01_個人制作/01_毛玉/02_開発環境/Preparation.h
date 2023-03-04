//
//ファイルヘッダーコメント
//
#ifndef _Preparation_H_
#define _Preparation_H_

#include"object2D.h"
#include "renderer.h"
#include"application.h"

//前方宣言


class Cpreparation : public CObject2D
{
public:
	//コンストラクタ
	Cpreparation(int nPriority);
	//デストラクタ
	~Cpreparation() override;

	//初期化
	HRESULT Init() override;
	//更新
	void Update() override;

	static Cpreparation* Create(const char *aFileName, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nPriority);


private:

	int ChangeCount;
	int count;
};

#endif