#pragma once

#include "Graphics/Sprite.h"
#include "Scene.h"
#include "Audio/Audio.h"

//�^�C�g���V�[��
class SceneOver :public Scene 
{
public:
    SceneOver() {}
    ~SceneOver() override {}

    //������
    void Initialize() override;

    //�I����
    void Finalize() override;

    //�X�V����
    void Update(float elapsedTime) override;

    //�`�揈��
    void Render() override;

private:
    Sprite* sprite = nullptr;
    Sprite* back = nullptr;

    std::unique_ptr<AudioSource>BGM_over;
    std::unique_ptr<AudioSource>SE_button;
};
