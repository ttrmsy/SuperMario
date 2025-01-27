#include "Application.h"
#include "DxLib.h"
#include "InputManager.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneBase.h"

Application::Application() :
	delta_second(0),start_time(0),
	now_time(0),refresh_rate(0),scene(nullptr)
{

}

Application::~Application()
{
	//����Y��h�~
	Shutdown();
}

bool Application::WakeUp()
{
	scene = SceneManager::GetInstance();

	//�E�B���h�E���[�h�ŋN������
	ChangeWindowMode(TRUE);

	//�E�B���h�E�T�C�Y�̐ݒ�	
	 SetGraphMode(D_WIN_MAX_X, D_WIN_MAX_Y, D_COLOR_BIT);

	//DX���C�u�����̏�����
	if (DxLib_Init() == D_FAILURE)
	{
		throw std::string("Dx���C�u�����̏������Ɏ��s���܂���\n");
	}

	//�`����\��ʂɔ��f����
	SetDrawScreen(DX_SCREEN_BACK);

	//�V�[���̏���������
	scene->Initialize();
	
	return true;
}

void Application::Run()
{

	while (ProcessMessage() == D_SUCCESS)
	{
		//�t���[�����[�g�̐���
		UpdateDeLtaTime();

		scene->Update(delta_second);
		
		
		
	}

	Shutdown();
}

void Application::Shutdown()
{
	//�V�[���̏I������
	scene->Finalize();

	//Dx���C�u�����̏I������
	DxLib_End();
}

void Application::UpdateDeLtaTime()
{
	//���݂̎��Ԏ擾
	now_time = GetNowHiPerformanceCount();

	// �J�n���Ԃ��猻�ݎ��Ԃ܂łɌo�߂������Ԃ��v�Z����i�ʕb�j
	// ����\���ʕb���b�ɕϊ�����
	delta_second = (float)(now_time - start_time) * 1.0e-6f;

	// �v���J�n���Ԃ��X�V����
	start_time = now_time;

	//���t���b�V�����[�g���擾����
	refresh_rate = (int)GetRefreshRate();

	//�P�t���[�������莞�Ԃ�1/refresh_rate�b�𒴂����璲������
	if (delta_second > (1.0f / refresh_rate))
	{
		delta_second = (1.0f / refresh_rate);
	}
}

int Application::ErrorThrow(std::string error_log)
{
	ErrorLogFmtAdd(error_log.c_str());
	return D_FAILURE;
}

float Application::Get_delta_Second()
{
	return delta_second;
}
