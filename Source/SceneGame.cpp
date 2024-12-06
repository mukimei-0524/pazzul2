#include "Graphics/Graphics.h"
#include "SceneGame.h"
#include "camera.h"
#include "EffectManager.h"
#include "Input/Input.h"
#include "Scene.h"
#include "Graphics/LambertShader.h"
#include "PlayerManager.h"
#include "StageMain.h"


//2D�̂����𒲂ׂ�i�O���b�g�ړ��j
// �p�b�N�}���Q�l
// ������
void SceneGame::Initialize()
{
#if 0
	//�X�e�[�W������
	//stage = new Stage();

	StageManager& stageManager = StageManager::Instance();
	StageMain* stageMain = new StageMain();

	stageManager.Register(stageMain);
	//StageMoveFloor* stageMoveFloor = new StageMoveFloor();
	//stageMoveFloor->SetStartPoint(DirectX::XMFLOAT3(0, 1, 3));
	//stageMoveFloor->SetGoalPoint(DirectX::XMFLOAT3(10, 2, 3));
	//stageMoveFloor->SetTorque(DirectX::XMFLOAT3(0, 1.0f, 0));
	//stageManager.Register(stageMoveFloor);
#endif
	tentative_UI = new Sprite("Data/Sprite/tentative_UI.png");

	desk = new Model("Data/Model/team/MDL/desk_02.mdl");

	//�v���C���[������
	Player* player = new Player("Data/Model/team/MDL/Rock_5-0.mdl");
	PlayerManager::Instance().Register(player);		//�s�[�X(player)��o�^

	player = new Player("Data/Model/team/MDL/Rock_5-1.mdl");
	PlayerManager::Instance().Register(player);		

	player = new Player("Data/Model/team/MDL/Rock_5-2.mdl");
	PlayerManager::Instance().Register(player);		

	player = new Player("Data/Model/team/MDL/Rock_5-3.mdl");
	PlayerManager::Instance().Register(player);

	player = new Player("Data/Model/team/MDL/Rock_5-4.mdl");
	PlayerManager::Instance().Register(player);		



	//�J���������ݒ�
	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::Instance();
	camera.SetLookAt(
		DirectX::XMFLOAT3(0, 53, -53),
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

	//UI�̎��v������
	UIManager& uiManager = UIManager::Instance();
	clock = new Clock();
	clock->Initialize();
	uiManager.UIRegister(clock);
}

// �I����
void SceneGame::Finalize()
{
	//StageManager::Instance().Clear();

	//�v���C���[�}�l�[�W���[����v���[���[�������I����
	PlayerManager::Instance().Clear();

	//�J�����R���g���[���[�I����
	if (cameraController != nullptr)
	{
		delete cameraController;
		cameraController = nullptr;
	}

	if (tentative_UI != nullptr)
	{
		delete tentative_UI;
		tentative_UI = nullptr;
	}

	//UI�I����
	UIManager::Instance().Clear();

	if (desk != nullptr)
	{
		delete desk;
		desk = nullptr;
	}
}

// �X�V����
void SceneGame::Update(float elapsedTime)
{
	//StageManager::Instance().Update(elapsedTime);

	//UI�X�V����
	UIManager::Instance().Update(elapsedTime);

	//player�X�V����
	PlayerManager::Instance().Update(elapsedTime);

	//�J�����R���g���[���[�X�V����
	DirectX::XMFLOAT3 target = {0.0f, 0.0f, 0.0f};
	target.y += 0.5f;
	cameraController->SetTarget(target);
	cameraController->Update(elapsedTime);

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

	//����UI
	float screenWidth = static_cast<float>(graphics.GetScreenWidth());
	float screenHeight = static_cast<float>(graphics.GetScreenHeight());
	float textureWidth = static_cast<float>(tentative_UI->GetTextureWidth());
	float textureHeight = static_cast<float>(tentative_UI->GetTextureHeight());
	float positionX = screenWidth - textureWidth;
	float positionY = screenHeight - textureHeight;



	HandleClick(dc, rc.view, rc.projection);


	// 3D���f���`��
	{
		Shader* shader = graphics.GetShader();
		shader->Begin(dc, rc);
		shader->SetAlpha(1.0f);
		shader->Draw(dc, desk);
		
		//�v���C���[�}�l�[�W���[����v���C���[������`��
		PlayerManager::Instance().Render(dc, shader);
		shader->End(dc);
	}
	//2D
	UIManager::Instance().Render();

	//3D�G�t�F�N�g�`��
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}

	// 3D�f�o�b�O�`��
	{
		// ���C�������_���`����s
		graphics.GetLineRenderer()->Render(dc, rc.view, rc.projection);

		// �f�o�b�O�����_���`����s
		graphics.GetDebugRenderer()->Render(dc, rc.view, rc.projection);

	}

	//��ŕύX
	tentative_UI->Render(dc,
		0, 400, 1280, 760,
		0, 0, textureWidth, textureHeight,
		0,
		1, 1, 1, 1
	);

	// 2D�f�o�b�OGUI�`��
	{
		//player�f�o�b�N�`��
		//PlayerManager::Instance().
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
			hit.hitPlayer->SetAlpha(1.0f);
			Player* player = nullptr;
		}
	}
}
