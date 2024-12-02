#include "Cameracontroller_2.h"
#include "camera.h"
#include "Input/Input.h"

//更新処理
void CameraController_2::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisRX();
	float ay = gamePad.GetAxisRY();

	//カメラの回転速度
	float speed = rollSpeed * elapsedTime;

	//スティックの入力値に合わせてX軸とY軸を回転
	angle.x += ay * speed;	//angle.x x軸回転(縦軸)にスティックy軸回転(縦軸)
	angle.y += ax * speed;	//angle.y y軸回転(横軸)にスティックx軸回転(横軸)

	//カメラ回転値を回転行列に変換
	DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	//回転行列から前方向ベクトルを取り出す
	DirectX::XMVECTOR Front = Transform.r[2];
	DirectX::XMFLOAT3 front;
	DirectX::XMStoreFloat3(&front, Front);

	//注視点から後ろベクトル方向に一定距離離れたカメラ視点を求める
	DirectX::XMFLOAT3 eye;
	eye.x = front.x * range;
	eye.y = front.y * range + 160.0f;
	eye.z = front.z * range + 100.0f;

	//カメラの視点と注視点を設定
	Camera::Instance().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
}
