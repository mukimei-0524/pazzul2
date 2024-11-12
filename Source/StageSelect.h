#pragma once

#include "Input/Input.h"
#include "Graphics/Sprite.h"
#include "Scene.h"

//�^�C�g���V�[��
class StageSelect :public Scene
{
public:
	StageSelect() {};
	~StageSelect() override {};

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
		Stage1,
		Stage2,
		Stage3,
		Stage4,
		Stage5,
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


private:
	Sprite* sprite = nullptr;		//���O�ς���
	Model* currentModel = nullptr;

};