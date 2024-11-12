#pragma once

#include "Graphics/Model.h"
#include "Stage.h"


//�X�e�[�W
class StageMain :public Stage
{
public:
	StageMain();
	~StageMain() override;

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader) override;

	//���C�L���X�g
	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit) override;

	//�C���X�^���X�擾	�ʏ�v���C���[�ɏ����Ȃ��B�����Ȃ�}�l�[�W���[�N���X��
	//static Stage& Instance();
private:
	Model* model = nullptr;
};