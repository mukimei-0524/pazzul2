#include "Input/Input.h"

#include "SceneFind.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "SceneGame.h"

#include "ChipManager.h"
#include "mapchip.h"
#include "Chip.h"
#include "camera.h"
#include "UIManager.h"


void SceneFind::Initialize()
{
	Floor = new Model("Data/Model/team/MDL/Floor.mdl");

	actor = new Actor();

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
	cameraController_2 = new CameraController_2();

	//���̏�����
	ChipManager& chipManager = ChipManager::Instance();
	for (int y = 0; y <= 8; ++y)
	{
		for (int x = 0; x <= 8; ++x)
		{
			//switch���Ń`�b�v�̎�ނ�؂�ւ���
			Chip* chip = new Chip();
			chip->SetPosition(DirectX::XMFLOAT3(x * 23.0f - 23 * 8 / 2, 0, y * 23.0f - 23 * 8 / 2));
			chipManager.Register(chip);
		}
	}

	//UI_Memo
	UIManager& uiManager = UIManager::Instance();
	memo = new UI_Memo();
	memo->Initialize();
	uiManager.UIRegister(memo);
}

void SceneFind::Finalize()
{
	//�J�����R���g���[���[�I����
	if (cameraController_2 != nullptr)
	{
		delete cameraController_2;
		cameraController_2 = nullptr;
	}
	//�����f���I����
	if (Floor != nullptr)
	{
		delete Floor;
		Floor = nullptr;
	}

	if (actor != nullptr)
	{
		delete actor;
		actor = nullptr;
	}

	ChipManager::Instance().Clear();

	//UI�I����
	UIManager::Instance().Clear();
}

void SceneFind::Update(float elapsedTime)
{
	//�J�����R���g���[���[�X�V����
	DirectX::XMFLOAT3 target = { 0.0f, 0.0f, 0.0f };
	target.y += 0.5f;
	cameraController_2->SetTarget(target);
	cameraController_2->Update(elapsedTime);

	actor->Update(elapsedTime);

	//Enter����������Q�[����ʂ�(�̂��ɍ�Ƒ�̑O�ɗ�����֕ύX)
	GamePad& gamePad = Input::Instance().GetGamePad();
	const GamePadButton anyBotton = GamePad::BTN_START;

	if (gamePad.GetButtonDown() & anyBotton)
	{
		SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame()));
	}

	ChipManager::Instance().Update(elapsedTime);

	//UI�X�V����
	UIManager::Instance().Update(elapsedTime);
}

void SceneFind::Render()
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
	//rc.alpha = 0.5f;

	//�J�����p�����[�^�[�ݒ�
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();


	Shader* shader = graphics.GetShader();
	shader->Begin(dc, rc);
	shader->SetAlpha(1.0f);

	//shader->Draw(dc, Floor);

	actor->Render(dc, shader);

	ChipManager::Instance().Render(dc, shader);
	//�v���C���[�}�l�[�W���[����v���C���[������`��
	//PlayerManager::Instance().Render(dc, shader);

	shader->End(dc);

	UIManager::Instance().Render();
}
