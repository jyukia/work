//
//ファイルヘッダーコメント
//
#ifndef _movelife_H_
#define _movelife_H_

#include"Number.h"
#include "renderer.h"
#include"application.h"
#include"mode.h"
//前方宣言
class CNumber;
class CMeshLine;

class CMovelife : public CObject2D
{
public:

	enum MOVETYPE
	{
		MOVE_NONE = 0,	//移動なし

		MOVE,	//移動あり
		RETURN,	//戻り

		MOVE_MAX
	};


	//コンストラクタ
	explicit CMovelife(int nPriority);
	//デストラクタ
	~CMovelife() override;

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

	static CMovelife* Create(D3DXVECTOR3 pos,int nPriority);

private:

	CMeshLine *m_meshline;

	CNumber* pNumber[5];
	int m_Life;	//情報保存

	bool m_bmoveflg;

	MOVETYPE type;
	int a = 0;
};

#endif