#include "WalkingState.h"
#include "../../../Utility/Vector2D.h"
#include "DxLib.h"


WalkingState::WalkingState(class Player* p)
	: PlayerStateBase(p),input(nullptr), speed(0)
{
	
}

WalkingState::~WalkingState()
{

}

void WalkingState::Initialize()
{
	//“ü—Íî•ñ
	input = InputManager::GetInstance();

	if (speed < 0)
	{
		if (input->GetKeyState(KEY_INPUT_D) == eInputState::Held || input->GetKeyState(KEY_INPUT_D) == eInputState::Pressed)
		{
			speed = 0;
		}
	}
	else if (speed > 0)
	{
		if (input->GetKeyState(KEY_INPUT_A) == eInputState::Held || input->GetKeyState(KEY_INPUT_A) == eInputState::Pressed)
		{
			speed = 0;
		}
	}
	
}

void WalkingState::Update(float delta_seconde)
{
	eInputState input_a, input_d;
	input_a = input->GetKeyState(KEY_INPUT_A);
	input_d = input->GetKeyState(KEY_INPUT_D);

	if (input_a == eInputState::Pressed || input_a == eInputState::Held)
	{
		if (input_d != eInputState::Pressed && input_d != eInputState::Held)
		{
			if (speed >= 0)
			{
				player->Set_SlideFlag(TRUE);
				speed += -0.2/* * delta_seconde*/;
			}
			else
			{
				player->SetFilp_flag(TRUE);
			}

			if (speed > -6)
			{
				speed += (float)6 / 60 * -1 /** delta_seconde*/;
			}
			player->Set_Velocity(Vector2D(speed, player->Get_Velocity().y));
		}
	
	}
	

	if (input_d == eInputState::Pressed || input_d == eInputState::Held)
	{
		if (input_a != eInputState::Pressed && input_a != eInputState::Held)
		{
			
			if (speed <= 0)
			{
				player->Set_SlideFlag(TRUE);
				speed += 0.2/* * delta_seconde*/;
			}
			else
			{
				player->SetFilp_flag(FALSE);
			}

			if (speed < 6)
			{
				speed += (float)6 / 60 /** delta_seconde*/;
			}
			player->Set_Velocity(Vector2D(speed, player->Get_Velocity().y));
		}
		
	}
	
	
	if (player->jump_flag == true)
	{
		if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
		{
			player->SetNextState(ePlayerState::jump);
		}
	}

	
	if (input_d == eInputState::None && input_a == eInputState::None)
	{
		if (speed > 0)
		{
			speed += (float)-4 / 30 /** delta_seconde*/;
			if (speed < 1.0e-6f)
			{
				speed = 0;
				player->SetNextState(ePlayerState::idle);
			}
		}
		else
		{
			speed += (float)4 / 30/* * delta_seconde*/;
			if (speed > -1.0e-6f)
			{
				speed = 0;
				player->SetNextState(ePlayerState::idle);
			}
		}
		
	}
	
}

void WalkingState::Draw() const
{

}

void WalkingState::Finalize()
{

}

ePlayerState WalkingState::GetState() const
{
	return ePlayerState::walk;
}

void WalkingState::Set_Speed(float s)
{
	speed = s;
}