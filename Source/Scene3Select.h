#pragma once

#include "Input/Input.h"
#include "Graphics/Sprite.h"
#include "Scene.h"

//�^�C�g���V�[��
class Scene3Select :public Scene
{
public:
	Scene3Select() {};
	~Scene3Select() override {};

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
	Stage stage = Stage1;
	//Model* currentModel = nullptr;
	Sprite* stage1 = nullptr;		//���O�ς���
	Sprite* stage2 = nullptr;		//���O�ς���
	Sprite* stage3 = nullptr;		//���O�ς���
	Sprite* start = nullptr;
	Sprite* back = nullptr;
};