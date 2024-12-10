#include "Character.h"
#include "StageManager.h"
#include <Mathf.h>

//行列更新処理
void Character::UpdateTransform()
{
	//スケール行列を作成
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	
	//回転行列を作成
	//DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);
	
	DirectX::XMMATRIX X = DirectX::XMMatrixRotationX(angle.x);
	DirectX::XMMATRIX Y = DirectX::XMMatrixRotationY(angle.y);
	DirectX::XMMATRIX Z = DirectX::XMMatrixRotationZ(angle.z);
	DirectX::XMMATRIX R = Y * X * Z;
	
	//位置行列を作成
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	//3つの行列を組み合わせ、ワールド行列を作成
	DirectX::XMMATRIX W = S * R * T;
	
	//計算したワールド行列を取り出す
	DirectX::XMStoreFloat4x4(&transform, W);
}

void Character::Move(float elapsedTime,float vx, float vz, float speed)
{
    speed *= elapsedTime;
    position.x += vx * speed * 0.5f;
    position.z += vz * speed * 0.5f;
}

void Character::Turn(float elapsedTime, float vx, float vz, float speed)
{
    speed *= elapsedTime;

    //進行ベクトルがゼロベクトルの場合は処理する必要なし
    float length = sqrtf(vx * vx + vz * vz);
    if (length < 0.001f)return;
    //進行ベクトルを単位ベクトル化
    vx /= length;
    vz /= length;

    //自身の回転値から前方向を求める
    float frontX = sinf(angle.y); 
    float frontZ = cosf(angle.y);

    //回転角を求めるため、２つの単位ベクトルの内積を計算する
    float dot = (frontX * vx) + (frontZ * vz);

    //内積値は-1.0~1.0で表現されており、２つの単位ベクトルの角度が
    //小さいほど1.0に近づくという性質を利用して回転速度を調整する
    float rot = 1.0f - dot;
    if (rot > speed)rot = speed;

    //左右判定を行うために２つの単位ベクトルの外積を計算する
    float cross = (frontZ * vx) - (frontX * vz);

    //2Dの外積値が正の場合か負の場合によって左右判定が行える
    //左右判定を行うことによって左回転を選択する
    if (cross < 0.0f) 
    {
        angle.y -= rot;
    }
    else 
    {
        angle.y += rot;
    }
}