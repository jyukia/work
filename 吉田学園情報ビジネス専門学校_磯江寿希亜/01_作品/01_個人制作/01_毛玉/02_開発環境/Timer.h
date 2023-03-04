//
//ファイルヘッダーコメント
//
#ifndef _Timer_H_
#define _Timer_H_

#include"Number.h"
#include "renderer.h"
#include"application.h"
#include"mode.h"
#include"player.h"
//前方宣言
class CNumber;
class CFade;

class CTimer : public CObject2D
{
public:
	//コンストラクタ
	explicit CTimer(int nPriority);
	//デストラクタ
	~CTimer() override;

	//初期化
	HRESULT Init() override;
	//終了
	void Uninit() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;

	void Addlife(int nValue);

	void Sublife(int nDecrease);

	void Setlife(int nLife);

	static CTimer* Create(D3DXVECTOR3 pos, int nPriority);

private:
	CFade *m_pFadeTime;

	CMeshLine *m_meshline;

	CNumber* pNumber[2];
	int m_Time;	//情報保存

	bool flg = CApplication::Getinstnce()->GetpMode()->GetPlayer()->Getbredycheck();

	int TimeCnt;	//時間取得
	bool returnflg;
	int cnt;

};

#endif