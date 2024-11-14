#include "Graphics/Graphics.h"
#include "Graphics/Model.h"

// �R���X�g���N�^
Model::Model(const char* filename)
{
	// ���\�[�X�ǂݍ���
	resource = std::make_shared<ModelResource>();
	resource->Load(Graphics::Instance().GetDevice(), filename);

	// �m�[�h
	const std::vector<ModelResource::Node>& resNodes = resource->GetNodes();

	nodes.resize(resNodes.size());
	for (size_t nodeIndex = 0; nodeIndex < nodes.size(); ++nodeIndex)
	{
		auto&& src = resNodes.at(nodeIndex);
		auto&& dst = nodes.at(nodeIndex);

		dst.name = src.name.c_str();
		dst.parent = src.parentIndex >= 0 ? &nodes.at(src.parentIndex) : nullptr;
		dst.scale = src.scale;
		dst.rotate = src.rotate;
		dst.translate = src.translate;

		if (dst.parent != nullptr)
		{
			dst.parent->children.emplace_back(&dst);
		}
	}

	// �s��v�Z
	const DirectX::XMFLOAT4X4 transform = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	UpdateTransform(transform);
}

// �ϊ��s��v�Z
void Model::UpdateTransform(const DirectX::XMFLOAT4X4& transform)
{
	DirectX::XMMATRIX Transform = DirectX::XMLoadFloat4x4(&transform);

	for (Node& node : nodes)
	{
		// ���[�J���s��Z�o
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(node.scale.x, node.scale.y, node.scale.z);
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(&node.rotate));
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(node.translate.x, node.translate.y, node.translate.z);
		DirectX::XMMATRIX LocalTransform = S * R * T;

		// ���[���h�s��Z�o
		DirectX::XMMATRIX ParentTransform;
		if (node.parent != nullptr)
		{
			ParentTransform = DirectX::XMLoadFloat4x4(&node.parent->worldTransform);
		}
		else
		{
			ParentTransform = Transform;
		}
		DirectX::XMMATRIX WorldTransform = LocalTransform * ParentTransform;

		// �v�Z���ʂ��i�[
		DirectX::XMStoreFloat4x4(&node.localTransform, LocalTransform);
		DirectX::XMStoreFloat4x4(&node.worldTransform, WorldTransform);
	}
}

void Model::UpdateAnimation(float elapsedTime)
{
	//�Đ����łȂ��Ȃ珈�����Ȃ�
	if (!IsPlayAnimation()) return;

	//�u�����h���̌v�Z
	float blendRate = 1.0f;
	if (animationBlendTime < animationBlendSeconds) {
		animationBlendTime += elapsedTime;
		if (animationBlendTime >= animationBlendSeconds) {
			animationBlendTime = animationBlendSeconds;
		}
		blendRate = animationBlendTime / animationBlendSeconds;
		blendRate *= blendRate;
	}

	//�w��̃A�j���[�V�����f�[�^���擾
	const std::vector<ModelResource::Animation>& animations = resource->GetAnimations();
	const ModelResource::Animation& animation = animations.at(currentAnimationIndex);
	
	//�A�j���[�V�����f�[�^����L�[�t���[���f�[�^���X�g���擾
	const std::vector<ModelResource::Keyframe>& keyframes = animation.keyframes;
	int keyCount = static_cast<int>(keyframes.size());
	for (int keyIndex = 0; keyIndex < keyCount - 1; ++keyIndex)
	{
		//���݂̎��Ԃ��ǂ̃L�[�t���[���̊Ԃɂ��邩���肷��
		const ModelResource::Keyframe& keyframe0 = keyframes.at(keyIndex);
		const ModelResource::Keyframe& keyframe1 = keyframes.at(keyIndex + 1);
		if (currentAnimationSceconds >= keyframe0.seconds &&
			currentAnimationSceconds < keyframe1.seconds)
		{
			//�Đ����ԂƃL�[�t���[���̎��Ԃ���⊮�����Z�o����
			float rate = (currentAnimationSceconds - keyframe0.seconds) / (keyframe1.seconds - keyframe0.seconds);

			int nodeCount = static_cast<int>(nodes.size());
			for (int nodeIndex = 0; nodeIndex < nodeCount; ++nodeIndex)
			{
				//2�̃L�[�t���[���Ԃ̕⊮�v�Z
				const ModelResource::NodeKeyData& key0 = keyframe0.nodeKeys.at(nodeIndex);
				const ModelResource::NodeKeyData& key1 = keyframe1.nodeKeys.at(nodeIndex);
				Node& node = nodes[nodeIndex];

				// �X�P�[���̕⊮
				DirectX::XMVECTOR scale0 = DirectX::XMLoadFloat3(&key0.scale);
				DirectX::XMVECTOR scale1 = DirectX::XMLoadFloat3(&key1.scale);
				DirectX::XMVECTOR interpolatedScale = DirectX::XMVectorLerp(scale0, scale1, rate);
				DirectX::XMStoreFloat3(&node.scale, interpolatedScale);

				// ��]�̕⊮ (�N�H�[�^�j�I������`��Ԃł͂Ȃ����ʐ��`��� (Slerp) �ŕ�Ԃ���)
				DirectX::XMVECTOR rotate0 = DirectX::XMLoadFloat4(&key0.rotate);
				DirectX::XMVECTOR rotate1 = DirectX::XMLoadFloat4(&key1.rotate);
				DirectX::XMVECTOR interpolatedRotate = DirectX::XMQuaternionSlerp(rotate0, rotate1, rate);
				DirectX::XMStoreFloat4(&node.rotate, interpolatedRotate);

				// �ړ��̕⊮
				DirectX::XMVECTOR translate0 = DirectX::XMLoadFloat3(&key0.translate);
				DirectX::XMVECTOR translate1 = DirectX::XMLoadFloat3(&key1.translate);
				DirectX::XMVECTOR interpolatedTranslate = DirectX::XMVectorLerp(translate0, translate1, rate);
				DirectX::XMStoreFloat3(&node.translate, interpolatedTranslate);

				//�u�����h�⊮����
				if (blendRate < 1.0f)
				{
					//���݂̎p���Ǝ��̃L�[�t���[���Ƃ̎p���̕⊮
					//�g�嗦�̒l��XMVECTOR�ɕϊ�
					DirectX::XMVECTOR S0 = DirectX::XMLoadFloat3(&node.scale);
					DirectX::XMVECTOR S1 = DirectX::XMLoadFloat3(&key1.scale);

					//��]�̒l��XMVECTOR�ɕϊ�
					DirectX::XMVECTOR R0 = DirectX::XMLoadFloat4(&node.rotate);
					DirectX::XMVECTOR R1 = DirectX::XMLoadFloat4(&key1.rotate);

					//�ʒu�̒l��XMVECTOR�ɕϊ�
					DirectX::XMVECTOR T0 = DirectX::XMLoadFloat3(&node.translate);
					DirectX::XMVECTOR T1 = DirectX::XMLoadFloat3(&key1.translate);

					//�g��̒l����`�⊮�Ōv�Z
					DirectX::XMVECTOR S = DirectX::XMVectorLerp(S0, S1, blendRate);
					//��]�̒l�����ʐ��`�⊮�ŎZ�o
					DirectX::XMVECTOR R = DirectX::XMQuaternionSlerp(R0, R1, blendRate);
					//�ʒu�̒l����`�⊮�Ōv�Z
					DirectX::XMVECTOR T = DirectX::XMVectorLerp(T0, T1, blendRate);

					//�v�Z���ʁi�g��A��]�A�ʒu�j���{�[���inode�j�Ɋi�[
					DirectX::XMStoreFloat3(&node.scale, S);
					DirectX::XMStoreFloat4(&node.rotate, R);
					DirectX::XMStoreFloat3(&node.translate, T);
				}
				//�ʏ�̏���
				else
				{
					//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̎p����⊮
					//�g�嗦�̒l��XMVECTOR�ɕϊ�
					DirectX::XMVECTOR S0 = DirectX::XMLoadFloat3(&key0.scale);
					DirectX::XMVECTOR S1 = DirectX::XMLoadFloat3(&key1.scale);

					//��]�̒l��XMVECTOR�ɕϊ�
					DirectX::XMVECTOR R0 = DirectX::XMLoadFloat4(&key0.rotate);
					DirectX::XMVECTOR R1 = DirectX::XMLoadFloat4(&key1.rotate);

					//�ʒu�̒l��XMVECTOR�ɕϊ�
					DirectX::XMVECTOR T0 = DirectX::XMLoadFloat3(&key0.translate);
					DirectX::XMVECTOR T1 = DirectX::XMLoadFloat3(&key1.translate);

					//�g��̒l����`�⊮�Ōv�Z
					DirectX::XMVECTOR S = DirectX::XMVectorLerp(S0, S1, rate);
					//��]�̒l�����ʐ��`�⊮�ŎZ�o
					DirectX::XMVECTOR R = DirectX::XMQuaternionSlerp(R0, R1, rate);
					//�ʒu�̒l����`�⊮�Ōv�Z
					DirectX::XMVECTOR T = DirectX::XMVectorLerp(T0, T1, rate);

					//�v�Z���ʁi�g��A��]�A�ʒu�j���{�[���inode�j�Ɋi�[
					DirectX::XMStoreFloat3(&node.scale, S);
					DirectX::XMStoreFloat4(&node.rotate, R);
					DirectX::XMStoreFloat3(&node.translate, T);
				}
			}
			break;
		}
	}
	//�ŏI�t���[������
	if (animationEndFlag)
	{
		animationEndFlag = false;
		currentAnimationIndex = -1;
		return;
	}
	//���Ԍo��
	currentAnimationSceconds += elapsedTime;

	//�Đ����Ԃ��I�[���Ԃ𒴂�����
	if (currentAnimationSceconds >= animation.secondsLength)
	{
		if (animationLoopFlag)
		{
			// ���[�v����ꍇ�A�Đ����Ԃ������߂�
			currentAnimationSceconds -= animation.secondsLength;
		}
		else
		{
			// ���[�v���Ȃ��ꍇ�A�A�j���[�V�������~����
			currentAnimationSceconds = animation.secondsLength; // �I�[�ŌŒ�
			animationEndFlag = true;  // �A�j���[�V�����I���t���O�𗧂Ă�
		}
	}
}

//�A�j���[�V�����Đ�
void Model::PlayAnimation(int index, bool loop, float blendSeconds)
{
	currentAnimationIndex = index;
	currentAnimationSceconds = 0.0f;
	animationBlendTime = 0.0f;
	animationBlendSeconds = blendSeconds;
}

bool Model::IsPlayAnimation() const
{
	//if (currentAnimationIndex < 0)return false;
	if (currentAnimationIndex >= resource->GetAnimations().size())return false;
	return true;
}