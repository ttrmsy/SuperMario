#include "ResultScene.h"
#include "../Utility/InputManager.h"
#include "DxLib.h"

void ResultScene::Initialize()
{

}

eSceneType ResultScene::Update(float delta_second)
{
	InputManager* input = InputManager::GetInstance();

	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		return eSceneType::eTitle;
	}

	return __super::Update(delta_second);

	return GetNowSceneType();
}

void ResultScene::Draw() const
{
	__super::Draw();

	SetFontSize(60);

	DrawFormatString(180, 210, GetColor(255, 255, 255), "GAME OVER");

}

void ResultScene::Finalize()
{

}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}