#include "InputManager.h"
#include "DxLib.h"

//InputManager::InputManager()
//{
//
//}

void InputManager::Update()
{
	//�L�[���͂̍X�V
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));
	GetHitKeyStateAll(now_key);

	//�R���g���[���[���͒l�̍X�V
	XINPUT_STATE input = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	for (int i = 0; i < D_BUTTON_MAX; i++)
	{
		old_button[i] = now_button[i];
		now_button[i] = static_cast<bool>(input.Buttons[i]);
	}
	trigger[0] = TriggerNormalize(input.LeftTrigger);
	trigger[1] = TriggerNormalize(input.RightTrigger);
	stick[0] = StickNormalize(input.ThumbLX);
	stick[1] = StickNormalize(input.ThumbRY);
}

eInputState InputManager::GetKeyState(int key_code) const
{

	//�L�[�������ꂽ�u�Ԃ�
	if (CheckKeycodeRange(key_code) && (now_key[key_code] == TRUE && old_key[key_code] == FALSE))
	{
		return eInputState::Pressed;
	}

	//�L�[��������Ă�����
	if (CheckKeycodeRange(key_code) && (now_key[key_code] == TRUE && old_key[key_code] == TRUE))
	{
		return eInputState::Held;
	}

	//�L�[�������ꂽ�u�Ԃ�
	if (CheckKeycodeRange(key_code) && (now_key[key_code] == FALSE && old_key[key_code] == TRUE))
	{
		return eInputState::Release;
	}

	return eInputState::None;
}

eInputState InputManager::GetButtonState(int button) const
{
	//�{�^����������Ă��邩
	if (CheckButtonRange(button) && (now_button[button] && old_button[button]))
	{
		return eInputState::Held;
	}

	//�{�^���������ꂽ�u�Ԃ�
	if (CheckButtonRange(button) && (now_button[button] && !old_button[button]))
	{
		return eInputState::Pressed;
	}

	//�{�^���������ꂽ�u�Ԃ�
	if (CheckButtonRange(button) && (!now_button[button] && old_button[button]))
	{
		return eInputState::Release;
	}
}

//eInputState InputManager::GetMouseButton(int m_button) const
//{
//
//}

float InputManager::GetLeftTrigger() const
{
	return trigger[0];
}

float InputManager::GetRightTrigger() const
{
	return trigger[1];
}

const Vector2D& InputManager::GetLeftStick() const
{
	return stick[0];
}

const Vector2D& InputManager::GetRightStick() const
{
	return stick[1];
}

bool InputManager::CheckKeycodeRange(int key_code) const
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}

bool InputManager::CheckButtonRange(int button) const
{
	return (0 <= button && button < D_BUTTON_MAX);
}

float InputManager::TriggerNormalize(unsigned char value) const
{
	float result = 0.0f;

	result = (float)value / (float)UCHAR_MAX;

	return result;
}

float InputManager::StickNormalize(unsigned char value) const
{
	float result = 0.0f;

	if (value >= 0)
	{
		result = (float)value / (float)SHRT_MAX;
	}
	else
	{
		result = -((float)value / (float)SHRT_MIN);
	}

	return result;
}