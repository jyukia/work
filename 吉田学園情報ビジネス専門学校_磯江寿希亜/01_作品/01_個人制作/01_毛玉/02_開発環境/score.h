//
//ファイルヘッダーコメント
//
#ifndef _Score_H_
#define _Score_H_

#include"Number.h"
#include "renderer.h"
#include"application.h"

//前方宣言
class CNumber;

class CScore : public CObject2D
{
public:
	//コンストラクタ
	explicit CScore(int nPriority);
	//デストラクタ
	~CScore() override;
	
	//初期化
	HRESULT Init() override;
	//終了
	void Uninit() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;

	void AddScore(int nValue);

	void SubScore(int nscore);

	void SetScore(int nScore);

	static CScore* Create(D3DXVECTOR3 pos);

	static int GetScore() {return m_Score;}

private:

	CNumber* pNumber[10];
	static int m_Score;	//情報保存
	int m_Remaining;	//情報保存

};

#endif