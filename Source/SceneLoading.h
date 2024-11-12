#pragma once

#include "Graphics/Sprite.h"
#include "Scene.h"
#include <thread>

//���[�f�B���O�V�[��
class SceneLoading :public Scene
{
public:
	SceneLoading() {};
	~SceneLoading() override {};

	//������
	void Initialize() override;

	//�I����
	void Finalize() override;

	//�X�V����
	void Update(float elapsedTime) override;

	//�`�揈��
	void Render() override;

	SceneLoading(Scene* nextScene) :nextScene(nextScene) {};

private:
	Sprite* sprite = nullptr;
	float angle = 0.0f;

	//���[�f�B���O�X���b�h
	static void LoadingThread(SceneLoading* scene);

	Scene* nextScene = nullptr;
	std::thread* thread = nullptr;
};