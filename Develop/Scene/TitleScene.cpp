#include "TitleScene.h"
#include "../Utility/ResourceManager.h"
#include "../Utility/InputManager.h"
#include "DxLib.h"

void TitleScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	UI_num = rm->GetImageResource("Resource/Images/UI/num.png", 15, 15, 1, 16, 16);
	UI_string = rm->GetImageResource("Resource/Images/UI/string.png", 26, 26, 1, 16, 16);
	UI_coin = rm->GetImageResource("Resource/Images/UI/uicoin.png", 4, 4, 1, 16, 16);
	num_image = UI_num[0];
	for (int i = 0; UI_string.begin() + i < UI_string.end(); i++)
	{
		string_image[i] = UI_string[i];
	}
	coin_image = UI_coin[0];

	__super::Initialize();
}

eSceneType TitleScene::Update(float delta_second)
{
	InputManager* input = InputManager::GetInstance();

 	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		return eSceneType::eInGame;
	}

	return __super::Update(delta_second);
}

void TitleScene::Draw() const
{
	//�^�C�g���w�i�摜�̕`��
	LoadGraphScreen(0, 0, "Resource/Images/title.png", TRUE);

	DrawFormatString(210, 300, GetColor(255, 255, 255), "PUSH SPASE");
	SetFontSize(40);
	//UI�F����MARIO�̕`��
	LoadGraphScreen(88, 28, "Resource/Images/UI/name_mario.png", TRUE);
	//UI�F�X�R�A�̕`��i6���̐����j
	int x, y;
	x = 96;
	y = 55;
	for (int i = 0; i < 6; i++)
	{
		DrawRotaGraphF(x, y, 1.0, 0.0, num_image, TRUE);
		x += 16;
	}
	//UI�F�R�C���̕`��
	
	
	__super::Draw();
}

void TitleScene::Finalize()
{
	__super::Finalize();
}
eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}