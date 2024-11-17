#include "Graphics/Graphics.h"
#include "SceneGame.h"
#include "camera.h"
#include "EffectManager.h"
#include "EffectManager.h"
#include "Input/Input.h"
#include "Scene.h"
#include "StageManager.h"
#include "StageMain.h"
//#include "StageMoveFloor.h"

// ������
void SceneGame::Initialize()
{
	//�X�e�[�W������
	//stage = new Stage();

	//StageManager& stageManager = StageManager::Instance();
	//StageMain* stageMain = new StageMain();
	//stageManager.Register(stageMain);
#if 0
	StageMoveFloor* stageMoveFloor = new StageMoveFloor();
	stageMoveFloor->SetStartPoint(DirectX::XMFLOAT3(0, 1, 3));
	stageMoveFloor->SetGoalPoint(DirectX::XMFLOAT3(10, 2, 3));
	stageMoveFloor->SetTorque(DirectX::XMFLOAT3(0, 1.0f, 0));
	stageManager.Register(stageMoveFloor);
#endif
	//�v���C���[������
	player = new Player();

	//�Q�[�W�X�v���C�g
	gauge = new Sprite();

	//�J���������ݒ�
	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::Instance();
	camera.SetLookAt(
		DirectX::XMFLOAT3(0, 10, -10),
		DirectX::XMFLOAT3(0, 0, 0),
		DirectX::XMFLOAT3(0, 1, 0)
	);
	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(45),
		graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);

	//�J�����R���g���[���[�̏�����
	cameraController = new CameraController();
}

// �I����
void SceneGame::Finalize()
{
	//StageManager::Instance().Clear();

	//�v���C���[�I����
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}

	//�J�����R���g���[���[�I����
	if (cameraController != nullptr)
	{
		delete cameraController;
		cameraController = nullptr;
	}

	//�Q�[�W�X�v���C�g�I����
	if (gauge != nullptr)
	{
		delete gauge;
		gauge = nullptr;
	}
}

// �X�V����
void SceneGame::Update(float elapsedTime)
{
	//player�X�V����
	PlayerManager::Instance().Update(elapsedTime);

	//�J�����R���g���[���[�X�V����
	DirectX::XMFLOAT3 target = player->GetPosition();
	target.y += 0.5f;
	cameraController->SetTarget(target);
	cameraController->Update(elapsedTime);

	//�G�t�F�N�g�X�V����
	EffectManager::Instance().Update(elapsedTime);
}

// �`�揈��
void SceneGame::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

	// ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
	FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0�`1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// �`�揈��
	RenderContext rc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ���C�g�����i�������j
	rc.alpha = 0.5f;
	//�J�����p�����[�^�[�ݒ�
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();
	// 3D���f���`��
	{
		Shader* shader = graphics.GetShader();
		shader->Begin(dc, rc);
		
		//�X�e�[�W�`��
		//StageManager::Instance().Render(dc, shader);

		//�v���C���[�`��
		player->Render(dc, shader);
		
		shader->End(dc);
	}

	//3D�G�t�F�N�g�`��
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}

	// 3D�f�o�b�O�`��
	{
		//�v���C���[�f�o�b�O�v���~�e�B�u�`��
		//player->DrawDebugPrimitive();

		// ���C�������_���`����s
		graphics.GetLineRenderer()->Render(dc, rc.view, rc.projection);

		// �f�o�b�O�����_���`����s
		graphics.GetDebugRenderer()->Render(dc, rc.view, rc.projection);

	}

	// 2D�f�o�b�OGUI�`��
	{
		//player�f�o�b�N�`��
		player->DrawDebugGUI();
	}
}

//�N���b�N����
void SceneGame::HandleClick(ID3D11DeviceContext* dc, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection)
{
	//�r���[�|�[�g
	D3D11_VIEWPORT viewport;
	UINT numViewports = 1;
	dc->RSGetViewports(&numViewports, &viewport);

	//�ϊ��s��
	DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&view);
	DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&projection);
	DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();
	
	Mouse& mouse = Input::Instance().GetMouse();
	if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
	{
		//�}�E�X�J�[�\�����W���擾
		DirectX::XMFLOAT3 screenPosition;
		screenPosition.x = static_cast<float>(mouse.GetPositionX());
		screenPosition.y = static_cast<float>(mouse.GetPositionY());

		DirectX::XMVECTOR ScreenPosition, WorldPosition;

		//���C�̎n�_���v�Z
		screenPosition.z = 0.0f;  //�r���[�|�[�g�̐[�x��0.0�ɐݒ�
		//ScreenPosition��XMVECTOR�ɕϊ�9								
		ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
		//�n�_��2D����3D�ɕϊ�
		WorldPosition = DirectX::XMVector3Unproject
		(ScreenPosition,
			viewport.TopLeftX,   //0.0f
			viewport.TopLeftY,   //0.0f
			viewport.Width,
			viewport.Height,
			viewport.MinDepth,   //0.0f,																																																																						
			viewport.MaxDepth,   //1.0f,
			Projection,  //DirectX::XMLoadFloat4x4(&projection),
			View,        //DirectX::XMLoadFloat4x4(&view),
			World
		);

		//���[���h��ԏ�ł̃��C�̎n�_�iWorldPosition��XMFLOAT3�ɕϊ��j
		DirectX::XMFLOAT3 rayStart;
		DirectX::XMStoreFloat3(&rayStart, WorldPosition);

		//���C�̏I�_���Z�o
		screenPosition.z = 1.0f;//�r���[�|�[�g�̐[�x��1.0�ɐݒ�
		//screenPosition��XMVECTOR�ɕϊ�
		ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);

		//�n�_��2D����3D�ɕϊ�
		WorldPosition = DirectX::XMVector3Unproject
		(ScreenPosition,
			viewport.TopLeftX,   //0.0f,
			viewport.TopLeftY,   //0.0f,
			viewport.Width,
			viewport.Height,
			viewport.MinDepth,   //0.0f,																																																																						
			viewport.MaxDepth,   //1.0f,
			Projection,  //DirectX::XMLoadFloat4x4(&projection),
			View,        //DirectX::XMLoadFloat4x4(&view),
			World
		);
		//���[���h��ԏ�ł̃��C�̏I�_�iWorldPosition��XMFLOAT3�ɕϊ��j
		DirectX::XMFLOAT3 rayEnd;
		DirectX::XMStoreFloat3(&rayEnd, WorldPosition);

		//���C�L���X�g
		HitResult hit;
		if (PlayerManager::Instance().RayCast(rayStart, rayEnd, hit))
		{
			//Player*player=

			//PlayerManager::Instance().Register(player);
		}

	}
}
