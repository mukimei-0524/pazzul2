#pragma once

#include "Graphics/Sprite.h"
#include "Scene.h"
#include "Audio/Audio.h"

//�^�C�g���V�[��
class SceneClear :public Scene 
{
public:
    SceneClear() {}
    ~SceneClear() override {}

    //������
    void Initialize() override;

    //�I����
    void Finalize() override;

    //�X�V����
    void Update(float elapsedTime) override;

    //�`�揈��
    void Render() override;

    void HandleClick(int x, int y);

private:
    Sprite* sprite = nullptr;
    Sprite* back = nullptr;

    std::unique_ptr<AudioSource> BGM_clear;
    std::unique_ptr<AudioSource> SE_button;
};
