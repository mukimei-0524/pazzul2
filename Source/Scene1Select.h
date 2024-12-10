#pragma once

#include "Input/Input.h"
#include "Graphics/Sprite.h"
#include "Scene.h"

//�^�C�g���V�[��
class Scene1Select :public Scene
{
public:
	Scene1Select() {};
	~Scene1Select() override {};

	//������
	void Initialize() override;

	//�I����
	void Finalize() override;

	//�X�V����
	void Update(float elapsedTime) override;

	//�`�揈��
	void Render() override;

private:

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
	//Model* currentModel = nullptr;
	Sprite* stage_1 = nullptr;		//���O�ς���
	Sprite* stage_2 = nullptr;		//���O�ς���
	Sprite* stage_3 = nullptr;		//���O�ς���
	Sprite* back = nullptr;
	Sprite* spr_back = nullptr;
};