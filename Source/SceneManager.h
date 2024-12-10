#pragma once

#include "Scene.h"
#include "SceneFind.h"

class SceneManager
{
private:
	SceneManager() {};
	~SceneManager() {};

public:
	//�B��̃C���X�^���X�擾
	static SceneManager&Instance()
	{
		static SceneManager instance;
		return instance;
	}

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render();

	//�V�[���N���A
	void Clear();

	//�V�[���؂�ւ�
	void ChangeScene(Scene* scene);

	// ���Ԑݒ�
	void SetTimer(int time) { this->timer = time; }

	// ���Ԏ擾
	int GetTimer() { return timer; }

private:
	Scene* currentScene = nullptr;
	Scene* nextScene = nullptr;

	float timer = 0.0f;
};

//currentScene�F���݂̃V�[��