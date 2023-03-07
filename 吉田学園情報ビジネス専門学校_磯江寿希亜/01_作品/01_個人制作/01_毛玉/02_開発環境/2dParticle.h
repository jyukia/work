//
//ファイルヘッダーコメント
//
#ifndef _PARTICLE_2d_H_
#define _PARTICLE_2d_H_

#include "object2D.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************


//*****************************************************************************
//マクロ定義
//*****************************************************************************

class CParticle2D : public CObject2D
{
private:
	float Particle_Size = 10.0f;
	//移動速さ
	const float m_fmaxmove = 20.0f;
	//ライフ
	int m_nLife = 8;
	//サイズ
	float size = Particle_Size;

public:
	//コンストラクタ
	explicit CParticle2D(int nPriority);

	//デストラクタ
	~CParticle2D();

	//初期化
	HRESULT Init() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;

	static CParticle2D* Create(const char *aFileName, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriority);

private:

};

#endif