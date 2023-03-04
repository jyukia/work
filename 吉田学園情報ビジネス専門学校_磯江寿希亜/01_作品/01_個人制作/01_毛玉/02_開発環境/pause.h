//
//�t�@�C���w�b�_�[�R�����g

#ifndef _CPause_H_
#define _CPause_H_

#include "renderer.h"
#include"application.h"
#include"object2d.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CFade;
//*****************************************************************************
//�}�N����`
//*****************************************************************************

class CPause : public CObject2D
{
public:
	const int m_modeMax = 2;	//��ʑJ�ڂ̍ő吔	//���[�h���ɂ���ĕύX
	const int m_modeMin = 1;	//��ʑJ�ڂ̍ŏ���	//�ύX�s�v

public:
	//�R���X�g���N�^	
	CPause(int nPriority);
	//�f�X�g���N�^
	~CPause() override;

	//������
	HRESULT Init() override;
	//�I��
	void Uninit() override;
	//�X�V
	void Update() override;
	//�`��
	void Draw() override;

	void SetObject(D3DXVECTOR3 Pos);

	static CPause* Create(const char *aFileName, D3DXVECTOR3 size, D3DXVECTOR3 pos, int nPriority);

	//Tex�̓ǂݍ��݁@1�P���̂�����Ă���̂ł�����ꊇ�ŊǗ����y������	Unload�����l
	static HRESULT Load();
	//�e�N�X�`���̔j��
	static void Unload();

	static bool GetPauseFlg() { return PauseFlg; }

private:
	//=============================================================================
	// ��� 
	//=============================================================================
	//�e�N�X�`�����̃|�C���^ 
	static LPDIRECT3DTEXTURE9 m_pTexture;

	CObject2D* m_pGame;
	CObject2D* m_pRanking;

	CFade *m_pFade;							// �t�F�[�h�̃|�C���^

	int m_modecount;
	static bool PauseFlg;
};
#endif