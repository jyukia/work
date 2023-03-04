#ifndef _SKYFIELD_H_
#define _SKYFIELD_H_

//**************************************************
// インクルード
//**************************************************
#include "object3D.h"
#include "renderer.h"
#include "application.h"
#include "texture.h"
#include "mode.h"

//**************************************************
// 前方前言
//**************************************************

//**************************************************
// クラス
//**************************************************
class CSkyField : public CObject
{
public:
	explicit CSkyField(int nPriority = 3);
	~CSkyField() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetSize(const D3DXVECTOR3& size) { m_size = size; }

	const D3DXVECTOR3& GetPos() const { return m_pos; }
	const D3DXVECTOR3& GetSize() const { return m_size; }

	void CSkyField::LoadTexture(const char * aFileName);

	static CSkyField *Create();

private:
	// ワールドマトリックス
	D3DXMATRIX m_mtxWorld;
	// テクスチャの列挙型
	LPDIRECT3DTEXTURE9 m_texture;
	// 頂点バッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	// 円錐の頂点バッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffCone;
	// インデックスバッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;
	// 位置
	D3DXVECTOR3 m_pos;
	// 移動量
	D3DXVECTOR3 m_move;
	// 回転
	D3DXVECTOR3 m_rot;
	// サイズ
	D3DXVECTOR3 m_size;
	int	m_nHorizontal;		// 横
	int	m_nVertical;			// 縦
	int	m_nVtx;				// 頂点数
	int	m_nIdx;				// インデックス数
	int	m_nPolygon;			// ポリゴン数

};

#endif	// _SKYFIELD_H_
