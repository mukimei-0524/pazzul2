#include "Collision.h"

//���Ƌ��̌�������
bool Collision::IntersectSphereVsSphere(const DirectX::XMFLOAT3& positionA, 
								float radiusA,
								const DirectX::XMFLOAT3& positionB,
								float radiusB, 
								DirectX::XMFLOAT3& outPositionB)
{
	//A��B�̒P�ʃx�N�g�����Z�o
	DirectX::XMVECTOR PositionA = DirectX::XMLoadFloat3(&positionA);
	DirectX::XMVECTOR PositionB = DirectX::XMLoadFloat3(&positionB);
	DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(PositionB, PositionA);
	DirectX::XMVECTOR LengthSq = DirectX::XMVector3LengthSq(Vec);
	float lengthSq;
	DirectX::XMStoreFloat(&lengthSq, LengthSq);

	//��������
	float range = radiusA + radiusB;
	if (lengthSq > range * range)
	{
		return false;
	}

	//A��B�������o��
	Vec = DirectX::XMVector3Normalize(Vec);
	Vec = DirectX::XMVectorScale(Vec, range);
	PositionB = DirectX::XMVectorAdd(PositionA, Vec);
	DirectX::XMStoreFloat3(&outPositionB, PositionB);

	return true;
}

//�~���Ɖ~���̌�������
bool Collision::IntersectCylinderVsCylinder(const DirectX::XMFLOAT3& positionA, 
											float radiusA, 
											float heightA, 
											const DirectX::XMFLOAT3& positionB, 
											float radiusB,
											float heightB, 
											DirectX::XMFLOAT3& outpositionB)
{
	//A�̑�����B�̓�����Ȃ瓖�����ĂȂ�
	if (positionA.y > positionB.y + heightB)
	{
		return false;
	}
	//A�̓���B�̑�����艺�Ȃ瓖�����ĂȂ�
	if (positionA.y + heightA < positionB.y)
	{
		return false;
	}

	//XZ���ʂł͈̔̓`�F�b�N
	float vx = positionB.x - positionA.x;
	float vz = positionB.z - positionA.z;
	float range = radiusA + radiusB;
	float distXZ = sqrt(vx * vx + vz * vz);

	if (distXZ > range)
	{
		return false;
	}

	//A��B�������o��
	vx /= distXZ;
	vz /= distXZ;

	outpositionB.x = positionA.x + (vx * range);
	outpositionB.y = positionB.y;
	outpositionB.z = positionA.z + (vz * range);

	return true;
}

//���Ɖ~���̌�������
bool Collision::IntersectSphereVsCylinder(const DirectX::XMFLOAT3& spherePosition,
											float sphereRadius,
											const DirectX::XMFLOAT3& cylinderPosition,
											float cylinderRadius,
											float cylinderHeight,
											DirectX::XMFLOAT3& outCylinderPosition)
{
#if 0
	{
		//���Ɖ~���̒��S�̋������v�Z
		DirectX::XMVECTOR SphereCenter = DirectX::XMLoadFloat3(&spherePosition);
		DirectX::XMVECTOR CylinderCenter = DirectX::XMLoadFloat3(&cylinderPosition);
		float distanceY = fabs(spherePosition.y - cylinderPosition.y);

		//���Ɖ~���̔��a�̘a
		float sumRadius = sphereRadius * cylinderRadius;

		//���Ɖ~���̒��S�̋��������a�̘a���傫���ꍇ�͌������Ă��Ȃ�
		if (distanceY > cylinderHeight / 2.0f + sphereRadius) return false;

		//XZ���ʏ�ł̋��Ɖ~���̋������v�Z
		float distanceXZ = sqrtf((spherePosition.x - cylinderPosition.x) * (spherePosition.x - cylinderPosition.x) +
			(spherePosition.z - cylinderPosition.z) * (spherePosition.z - cylinderPosition.z));

		//XZ���ʏ�ł̋��Ɖ~���̔��a�̘a
		float sumRadiusXZ = sphereRadius + cylinderRadius;

		//XZ���ʏ�ł̋��Ɖ~���̋��������a�̘a���傫���ꍇ�͌������Ă��Ȃ�
		if (distanceXZ > sumRadiusXZ) return false;

		//�����~���̍������ɂ���A����XZ���ʏ�Ō������Ă���ꍇ�͌������Ă���
		//���̏ꍇ�����~���������o���K�v������
		float penetrationDepth = sumRadiusXZ - distanceXZ;
		float penetrationRatio = sumRadiusXZ / distanceXZ;

		//���̒��S�Ɖ~���̒��S�̃x�N�g��
		DirectX::XMVECTOR centerVector = DirectX::XMVectorSubtract(SphereCenter, CylinderCenter);
		DirectX::XMVECTOR normalizeCenterVector = DirectX::XMVector3Normalize(centerVector);

		//���������o����鋗��
		DirectX::XMVECTOR pushOut = DirectX::XMVectorScale(normalizeCenterVector, penetrationDepth);
		DirectX::XMVECTOR newCylinderPosition = DirectX::XMVectorAdd(CylinderCenter, pushOut);
		
		//�V�����~���̈ʒu��CyrinderPosition�ɕۑ�
		DirectX::XMStoreFloat3(&outCylinderPosition, newCylinderPosition);
	}
#endif // 1

	//���Ɖ�
#if 1
	{
		//�����`�F�b�N
		if (spherePosition.y + sphereRadius < cylinderPosition.y) return false;
		if (spherePosition.y - sphereRadius > cylinderPosition.y + cylinderHeight) return false;

		//XZ���ʂł͈̔̓`�F�b�N
		float vx = cylinderPosition.x - spherePosition.x;
		float vz = cylinderPosition.z - spherePosition.z;
		float range = sphereRadius + cylinderRadius;
		float distXZ = sqrtf(vx * vx + vz * vz);
		if (distXZ > range)return false;

		//�����~���������o��
		vx /= distXZ;
		vz /= distXZ;
		outCylinderPosition.x = spherePosition.x + (vx * range);
		outCylinderPosition.y = spherePosition.y;
		outCylinderPosition.z = spherePosition.z + (vz * range);
	}

#endif	//0
	return true;
}

//���C�ƃ��f���̌�������
bool Collision::IntersectRayVsModel(
	const DirectX::XMFLOAT3& start, 
	const DirectX::XMFLOAT3& end, 
	const Model* model, 
	HitResult& result)
{
	DirectX::XMVECTOR WorldStart = DirectX::XMLoadFloat3(&start);
	DirectX::XMVECTOR WorldEnd = DirectX::XMLoadFloat3(&end);
	DirectX::XMVECTOR WorldRayVec = DirectX::XMVectorSubtract(WorldEnd, WorldStart);
	DirectX::XMVECTOR worldRayLength = DirectX::XMVector3Length(WorldRayVec);

	//���[���h��Ԃ̃��C�̒���
	DirectX::XMStoreFloat(&result.distance, worldRayLength);

	bool hit = false;
	const ModelResource* resource = model->GetResource();
	for (const ModelResource::Mesh& mesh : resource->GetMeshes())
	{
		//���b�V���m�[�h�擾
		const Model::Node& node = model->GetNodes().at(mesh.nodeIndex);

		//���C�����[���h��Ԃ��烍�[�J����Ԃ֕ϊ�	Inverse:�t�A����
		DirectX::XMMATRIX WorldTransform = DirectX::XMLoadFloat4x4(&node.worldTransform);
		DirectX::XMMATRIX InverseWorldTransform = DirectX::XMMatrixInverse(nullptr, WorldTransform);

		DirectX::XMVECTOR S = DirectX::XMVector3TransformCoord(WorldStart, InverseWorldTransform);
		DirectX::XMVECTOR E = DirectX::XMVector3TransformCoord(WorldEnd, InverseWorldTransform);
		DirectX::XMVECTOR SE = DirectX::XMVectorSubtract(E, S);
		DirectX::XMVECTOR V = DirectX::XMVector3Normalize(SE);
		DirectX::XMVECTOR Length = DirectX::XMVector3Length(SE);

		//���C�̒���
		float neart;
		DirectX::XMStoreFloat(&neart, Length);

		//�O�p�`(��)�Ƃ̌�������
		const std::vector<ModelResource::Vertex>& vertices = mesh.vertices;
		const std::vector<UINT>indices = mesh.indices;

		int materialIndex = -1;
		DirectX::XMVECTOR HitPosition;
		DirectX::XMVECTOR HitNormal;
		for (const ModelResource::Subset& subset : mesh.subsets)
		{
			for (UINT i = 0; i < subset.indexCount; i += 3)
			{
				UINT index = subset.startIndex + i;

				//�O�p�`�̒��_�𒊏o
				const ModelResource::Vertex& a = vertices.at(indices.at(index));
				const ModelResource::Vertex& b = vertices.at(indices.at(index + 1));
				const ModelResource::Vertex& c = vertices.at(indices.at(index + 2));

				DirectX::XMVECTOR A = DirectX::XMLoadFloat3(&a.position);
				DirectX::XMVECTOR B = DirectX::XMLoadFloat3(&b.position);
				DirectX::XMVECTOR C = DirectX::XMLoadFloat3(&c.position);

				//�O�p�`�̎O�Ӄx�N�g�����Z�o
				DirectX::XMVECTOR AB = DirectX::XMVectorSubtract(B, A);
				DirectX::XMVECTOR BC = DirectX::XMVectorSubtract(C, B);
				DirectX::XMVECTOR CA = DirectX::XMVectorSubtract(A, C);

				//�O�p�`�̖@���x�N�g��(�O��)���Z�o
				DirectX::XMVECTOR N = DirectX::XMVector3Cross(AB, BC);

				//���ς̌��ʂ��v���X�Ȃ�Η�����
				DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(V, N);		//d2
				float dot;
				DirectX::XMStoreFloat(&dot, Dot);
				if (dot >= 0.0f)continue;

				//���C�ƕ��ʂ̌�_���Z�o
				DirectX::XMVECTOR SA = DirectX::XMVectorSubtract(A, S);
				DirectX::XMVECTOR D1 = DirectX::XMVector3Dot(SA, N);		//d1
				float d1;
				DirectX::XMStoreFloat(&d1, D1);
				float x = d1 / dot;
				if (x<.0f || x>neart) continue;		//��_�܂ł̋��������܂łɌv�Z�����ŋߋ������
													//�傫���Ƃ��̓X�L�b�v
				//S+V*x
				DirectX::XMVECTOR P = DirectX::XMVectorAdd(S, DirectX::XMVectorScale(V, x));


				//��_���O�p�`�̓����ɂ��邩����
				//1��
				DirectX::XMVECTOR PA = DirectX::XMVectorSubtract(A, P);
				DirectX::XMVECTOR Cross1 = DirectX::XMVector3Cross(PA, AB);
				DirectX::XMVECTOR Dot1 = DirectX::XMVector3Dot(Cross1, N);
				float dot1;
				DirectX::XMStoreFloat(&dot1, Dot1);
				if (dot1 < 0.0f)continue;

				//2��
				DirectX::XMVECTOR PB = DirectX::XMVectorSubtract(B, P);
				DirectX::XMVECTOR Cross2 = DirectX::XMVector3Cross(PB, BC);
				DirectX::XMVECTOR Dot2 = DirectX::XMVector3Dot(Cross2, N);
				float dot2;
				DirectX::XMStoreFloat(&dot2, Dot2);
				if (dot2 < 0.0f)continue;

				//3��
				DirectX::XMVECTOR PC = DirectX::XMVectorSubtract(C, P);
				DirectX::XMVECTOR Cross3 = DirectX::XMVector3Cross(PC, CA);
				DirectX::XMVECTOR Dot3 = DirectX::XMVector3Dot(Cross3, N);
				float dot3;
				DirectX::XMStoreFloat(&dot3, Dot3);
				if (dot3 < 0.0f)continue;

				//�ŋߋ������X�V
				neart = x;

				//��_�Ɩ@�����X�V
				HitPosition = P;
				HitNormal = N;
				materialIndex = subset.materialIndex;
			}
		}
		if (materialIndex >= 0)
		{
			//���[�J����Ԃ��烏�[���h��Ԃ֕ϊ�
			DirectX::XMVECTOR WorldPosition = DirectX::XMVector3TransformCoord(HitPosition,
																				WorldTransform);
			DirectX::XMVECTOR WorldCrossVec = DirectX::XMVectorSubtract(WorldPosition, WorldStart);
			DirectX::XMVECTOR WorldCrossLength = DirectX::XMVector3Length(WorldCrossVec);
			float distance;
			DirectX::XMStoreFloat(&distance, WorldCrossLength);

			//�q�b�g���ۑ�
			if (result.distance > distance)
			{
				DirectX::XMVECTOR WorldNormal = DirectX::XMVector3TransformNormal(HitNormal, WorldTransform);


				result.distance = distance;
				result.materialIndex = materialIndex;
				DirectX::XMStoreFloat3(&result.position, WorldPosition);
				DirectX::XMStoreFloat3(&result.normal, DirectX::XMVector3Normalize(WorldNormal));
				hit = true;
			}
		}
	}
	return hit;
}

