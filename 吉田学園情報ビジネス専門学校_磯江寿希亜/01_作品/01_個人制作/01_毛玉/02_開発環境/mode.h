#ifndef _MODE_H_
#define _MODE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// �O����`
//=============================================================================
class CTitle;
class CGame;
class CResult;
class CPlayer;
class CMeshLine;
class CMovelife;
class CSkyField;
class CLight;
class CTexture;
class CItem;
class Cpreparation;
class CGoal;
class CScore;
class CInputJoyPad;
class CTimer;
//=============================================================================
// �N���X�̒�`
//=============================================================================
class CMode : public CObject
{
public:
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	CMode();
	~CMode() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init() override { return S_OK; };		// ����������
	void Uninit() override {};						// �I������
	void Update() override {};						// �X�V����
	void Draw() override {};						// �`�揈��
	void VtxUpdate() override {};					// ���_���W�X�V����
	void SetPos(D3DXVECTOR3 pos) override { D3DXVECTOR3 i = pos; };		// ���W�ݒ菈��
	void SetSize(D3DXVECTOR3 size) override { D3DXVECTOR3 i = size; };		// �T�C�Y�ݒ菈��
	void SetMove(D3DXVECTOR3 move) override { D3DXVECTOR3  i = move; };		// �ړ��ʐݒ菈��
	void SetCol(D3DXCOLOR col) override { D3DXCOLOR i = col; };			// �F�ݒ菈��
	void SetRot(D3DXVECTOR3 rot) override { D3DXVECTOR3 i = rot; };		// �����ݒ菈��
	D3DXVECTOR3 GetPos(void) override { return D3DXVECTOR3(); }			// ���W�擾����
	D3DXVECTOR3 GetSize(void) override { return D3DXVECTOR3(); }		// �T�C�Y�擾����
	D3DXVECTOR3 GetMove(void) override { return D3DXVECTOR3(); }		// �ړ��ʎ擾����
	D3DXVECTOR3 GetRot(void) override { return D3DXVECTOR3(); }			// �����擾����
	D3DXCOLOR GetCol(void) override { return D3DXCOLOR(); }			// �F�擾����

	//�v���C���[
	static CPlayer *GetPlayer() { return m_pPlayer; }
	static void SetPlayer(CPlayer* player) { m_pPlayer = player; }

	//��
	static CSkyField *GetSkyField() { return m_SkyField; }
	static void SetSkyField(CSkyField* skyfield) { m_SkyField = skyfield; }

	//�e�N�X�`��
	static CTexture *GetTexture() { return m_Texture; }
	static void SetTexture(CTexture* texture) { m_Texture = texture; }

	//�v���C���[�ړ���
	static CMeshLine *GetMeshLine() { return m_pMeshLine; }

	//�v���C���[�ړ���	�i���o�[
	static CMovelife *GetMoveLife() {return m_MoveLife;}

	//�A�C�e��
	static CItem* GetItem() { return m_Item; }

	//�Q�[���J�n�̂��߂̃J�E���g
	static 	Cpreparation * GetPreparation() { return m_preparation; }

	//�S�[��
	static 	CGoal* GetGoal() { return m_Goal; }

	//�X�R�A
	static CScore* GetScore() { return m_GameScore; }
	static void SetScore(CScore* score) {  m_GameScore= score; }

	static CInputJoyPad* GetJoy() { return m_joypad; }
	static CInputJoyPad* GetInpuJoy() { return m_Inputjoypad; }

	static CTimer* GetTimer() {return m_Timer;}
private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------

	static CPlayer *m_pPlayer;				// �v���C���[�̃|�C���^

	static CMeshLine *m_pMeshLine;

	static CMovelife *m_MoveLife;

	static CSkyField *m_SkyField;

	static CTexture *m_Texture;

	static 	CItem *m_Item;

	static 	Cpreparation *m_preparation;

	static 	CGoal *m_Goal;

	static CScore *m_GameScore;

	static CInputJoyPad* m_Inputjoypad;
	static CInputJoyPad* m_joypad;

	static CTimer* m_Timer;
};

#endif