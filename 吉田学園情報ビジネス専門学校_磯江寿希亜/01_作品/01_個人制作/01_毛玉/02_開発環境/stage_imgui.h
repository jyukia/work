////**************************************************
//// 
//// particle_imgui.h
//// Author  : katsuki mizuki
//// Author  : Yuda Kaito
//// 
////**************************************************
//#ifndef _STAGE_IMGUI_H_	// ���̃}�N������`����ĂȂ�������
//#define _STAGE_IMGUI_H_	// 2�d�C���N���[�h�h�~�̃}�N����`
//
////==================================================
//// �C���N���[�h
////==================================================
//#include "imgui_property.h"
//
////--------------------------------------------------
//// �p�[�e�B�N���p��Imgui�\���N���X
////--------------------------------------------------
//class CStageImgui : public CImguiProperty
//{
//public:
//
//
//	CStageImgui();
//	~CStageImgui();
//
//	HWND Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice) override;
//	void Uninit(HWND hWnd, WNDCLASSEX wcex) override;
//	bool Update() override;
//	void Draw() override;
//
//	int GetMesh() const { return sliderIntmesh; }
//	int GetModel() const { return sliderIntmodel; }
//
//	void SetMeshPos(float x, float y, float z);
//
//	void funcFileLoad(HWND hWnd);
//
//private: // �v���C�x�[�g�֐�
//	void TaskBarUpdate();
//
//private: // �����o�[�ϐ�
//
//	const int MeshMax = 100;
//	static const int	MAX_TEXT = 1024;		// �e�L�X�g�̍ő啶����
//	const char*	WINDOW_NAME = "test";	// �E�C���h�E�̖��O (�L���v�V�����ɕ\��)
//
//	D3DXVECTOR3 sliderRot;			// mesh�̉�]��肽������
//
//	bool m_Gura = false;			// �d��
//	bool m_MoveIron = false;		// �S���������Ȃ��ݒ�i�X�N���[���o�[�j
//
//	int sliderIntmodel;
//	int indexBuilding = 0;			// �ҏW���������f���̕\��ID�i�R���{�{�b�N�X�j
//	std::string NowModelName;		// �ݒu�������f���̕\�����i�R���{�{�b�N�X�j
//	float sliderPos3[3];			// ��]����^�}�̍��W�i�󂯎�锠�j	
//	float sliderRot3[3];			// ��]����^�}�̉�]�i�󂯎�锠�j	
//	float sliderNowRot3[3];			// ��]����^�}�̉�]�i�󂯎�锠�j	
//
//	int sliderIntmesh;						// mesh��Type�I���i�X�N���[���o�[�j
//	unsigned int indexModel = 0;					// �ҏW���������f���̕\��ID�i�R���{�{�b�N�X�j
//	unsigned int indexTex = 0;				// �ҏW�������e�N�X�`���̕\��ID�i�R���{�{�b�N�X�j
//	unsigned int indexmeshAnimation = 0;	// �ҏW���������b�V���̃A�j���[�V�����ԍ��\��ID�i�R���{�{�b�N�X�j
//	unsigned int indexmeshNumber = 0;		// �ҏW���������b�V���̔ԍ��̕\��ID�i�R���{�{�b�N�X�j
//	unsigned int indexCamera = 0;			// �ҏW�������J����Animation�̔ԍ��̕\��ID�i�R���{�{�b�N�X�j
//	unsigned int indexCameraAnimation = 0;	// �ҏW�������J����Animation�̒��̍��W�ԍ��̕\��ID�i�R���{�{�b�N�X�j
//	std::string NowMeshName;				// �ҏW������mesh�̕\�����i�R���{�{�b�N�X�j
//	std::string NowMeshNumberName;			// �ҏW�������A�j���[�V����Number�̕\�����i�R���{�{�b�N�X�j
//	std::string NowCameraNumberName;		// �ҏW������CameraNumber�̕\�����i�R���{�{�b�N�X�j
//	std::string NowCameraAnimationNumberName;		// �ҏW������Camera�A�j���[�V����Number�̕\�����i�R���{�{�b�N�X�j
//	bool Animation = false;					// �A�j���[�V�������邩���Ȃ���
//
//	float m_PosVSet[3];			// ���R�̎����W�ݒ肷��悤	
//	float m_PosRSet[3];			// ���R�̎����W�ݒ肷��悤	
//	int m_KeySet;
//
//	// ���b�V����pos
//	float m_fMeshPos[3];
//
//};
//
//#endif // !_IMGUI_PROPERTY_H_
