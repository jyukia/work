//
//ファイルヘッダーコメント
//
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "renderer.h"
#include "object3D.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************


//*****************************************************************************
//マクロ定義
//*****************************************************************************

class CParticle : public CObject3D
{
private:
	float Particle_Size = 10.0f;
	//移動速さ
	const float m_fmaxmove = 20.0f;
	//ライフ
	int m_nLife = 15;
	//サイズ
	float size = Particle_Size;

public:
	//コンストラクタ
	CParticle(const int list);

	//デストラクタ
	~CParticle() override;

	//初期化
	HRESULT Init() override;

	void Uninit() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;

	static CParticle* Create(const char *aFileName,D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriority);

private:
	void move();
	D3DXVECTOR3 m_Move;

};

#endif