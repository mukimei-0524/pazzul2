#pragma once

#include "Input/Input.h"
#include "Graphics/Sprite.h"
#include "Scene.h"

//�^�C�g���V�[��
class SceneSelect :public Scene
{
public:
	SceneSelect() {};
	~SceneSelect() override {};

	//������
	void Initialize() override;

	//�I����
	void Finalize() override;

	//�X�V����
	void Update(float elapsedTime) override;

	//�`�揈��
	void Render() override;

private:
	enum Stage
	{
		Tutorial,
		Stage1,
		Stage2,
		Stage3,
	};

	DirectX::XMFLOAT3     position = { 0,-1,0 };
	DirectX::XMFLOAT3     angle = { 0,135,0 };
	DirectX::XMFLOAT3     scale = { 1,1,1 };

	DirectX::XMFLOAT4X4   transform =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	void HandleClick(int x, int y);
private:
	Stage stage = Tutorial;
	Model* currentModel = nullptr;
	Sprite* tutorial = nullptr;		//���O�ς���
	Sprite* stage1 = nullptr;		//���O�ς���
	Sprite* stage2 = nullptr;		//���O�ς���
	Sprite* stage3 = nullptr;		//���O�ς���
	Sprite* start = nullptr;
	Sprite* right = nullptr;  // �l�p�̃X�v���C�g
	Sprite* left = nullptr;  // �l�p�̃X�v���C�g
	Sprite* back = nullptr;  
	RECT leftRect;
	RECT rightRect;

};