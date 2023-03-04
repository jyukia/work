#ifndef _SKYFIELD_H_
#define _SKYFIELD_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object3D.h"
#include "renderer.h"
#include "application.h"
#include "texture.h"
#include "mode.h"

//**************************************************
// �O���O��
//**************************************************

//**************************************************
// �N���X
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
	// ���[���h�}�g���b�N�X
	D3DXMATRIX m_mtxWorld;
	// �e�N�X�`���̗񋓌^
	LPDIRECT3DTEXTURE9 m_texture;
	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	// �~���̒��_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffCone;
	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;
	// �ʒu
	D3DXVECTOR3 m_pos;
	// �ړ���
	D3DXVECTOR3 m_move;
	// ��]
	D3DXVECTOR3 m_rot;
	// �T�C�Y
	D3DXVECTOR3 m_size;
	int	m_nHorizontal;		// ��
	int	m_nVertical;			// �c
	int	m_nVtx;				// ���_��
	int	m_nIdx;				// �C���f�b�N�X��
	int	m_nPolygon;			// �|���S����

};

#endif	// _SKYFIELD_H_
