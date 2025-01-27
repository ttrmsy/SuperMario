#include "SceneManager.h"
#include "SceneFactory.h"
#include "../Utility/Application.h"
#include "../Utility/InputManager.h"

SceneManager::SceneManager() : current_scene(nullptr)
{
	
}

void SceneManager::Initialize()
{
	ChangeScene(eSceneType::eTitle);
}

bool SceneManager::Update(float delta_second)
{
	InputManager* input = InputManager::GetInstance();

	input->Update();

	eSceneType next_scene = current_scene->Update(delta_second);

	// ��ʂ̏�����
	ClearDrawScreen();
	// �V�[���̕`�揈��
	current_scene->Draw();
	// ����ʂ̓��e��\��ʂɔ��f����
	ScreenFlip();

	// �Q�[�����I�����邩�m�F����
	if ((next_scene == eSceneType::eExit) ||
		(eInputState::Release == input->GetButtonState(XINPUT_BUTTON_BACK)) ||
		(eInputState::Release == input->GetKeyState(KEY_INPUT_ESCAPE)))
	{
		return false;
	}

	if (current_scene->GetNowSceneType() != next_scene)
	{
		ChangeScene(next_scene);
	}

	return true;
}


void SceneManager::Finalize()
{
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

bool SceneManager::ChangeScene(enum eSceneType type)
{
	//�V�����V�[�����쐬����
	SceneBase* next_scene = SceneFactory::CreateScene(type);

	//�G���[�`�F�b�N
	if (next_scene == nullptr)
	{
		throw("�V�[���������ł��܂���ł���\n");
		return false;
	}

	//�ύX�O�V�[���̏I������
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	//�V�����V�[���̏���������
	next_scene->Initialize();
	//�V�[���̏㏑��
	current_scene = next_scene;

	return true;
}