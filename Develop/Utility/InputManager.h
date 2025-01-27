#pragma once
#include "Singleton.h"
#include "Vector2D.h"

//�}�N����`
#define D_KEYCODE_MAX	(256)
#define D_BUTTON_MAX	(16)

enum eInputState
{
	None,
	Pressed,
	Release,
	Held
};

class InputManager : public Singleton<InputManager>
{
private:
	char now_key[D_KEYCODE_MAX];	//���݂̓��͒l
	char old_key[D_KEYCODE_MAX];	//�O��̓��͒l

	//�R���g���[���[���͏��
	bool now_button[D_BUTTON_MAX];
	bool old_button[D_BUTTON_MAX];
	float trigger[2];
	float stick[2];

public:
	/*InputManager();*/

	void Update();
	eInputState GetKeyState(int key_code) const;
	eInputState GetButtonState(int button) const;
	/*eInputState GetMouseButton(int m_button) const;*/
	float GetLeftTrigger() const;
	float GetRightTrigger() const;
	const Vector2D& GetLeftStick() const;
	const Vector2D& GetRightStick() const;

private:
	bool CheckKeycodeRange(int key_code) const;
	bool CheckButtonRange(int button) const;
	float TriggerNormalize(unsigned char value) const;
	float StickNormalize(unsigned char value) const;

};
