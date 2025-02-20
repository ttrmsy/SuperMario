#include "JumpingState.h"
#include "../../../Utility/InputManager.h"
#include "DxLib.h"

#define JUMP_VECTOR (-15.0f)

JumpingState::JumpingState(class Player* p)
	: PlayerStateBase(p),g_velocity(0)
{

}

JumpingState::~JumpingState()
{

}

void JumpingState::Initialize()
{
	this->player->Set_IsGround(false);
	this->player->Set_Velocity(Vector2D(player->Get_Velocity().x, JUMP_VECTOR));
	j_velocity = player->Get_Velocity();
	player->jump_flag = false;
	Held_jump = 0.0f;
	PlaySound("Resource/Sounds/SE_SuperJump.wav", DX_PLAYTYPE_BACK);

}

void JumpingState::Update(float delta_seconde)
{
	InputManager* input = InputManager::GetInstance();

	

	eInputState input_a, input_d;
	input_a = input->GetKeyState(KEY_INPUT_A);
	input_d = input->GetKeyState(KEY_INPUT_D);

	if (input_a == eInputState::Pressed || input_a == eInputState::Held)
	{
		if (input_d != eInputState::Pressed && input_d != eInputState::Held)
		{
			j_velocity = player->Get_Velocity();
			if (j_velocity.x < 6)
			{
				j_velocity.x += -0.15 /** delta_seconde*/;
				player->Set_Velocity(j_velocity);
			}
			
		}

	}


	if (input_d == eInputState::Pressed || input_d == eInputState::Held)
	{
		if (input_a != eInputState::Pressed && input_a != eInputState::Held)
		{
			j_velocity = player->Get_Velocity();
			if (j_velocity.x < 6)
			{
				j_velocity.x += 0.15 /** delta_seconde*/;
				player->Set_Velocity(j_velocity);
			}
		}

	}

	

	//SPACEを押し続けるとジャンプの高さが変わる処理
	if (input->GetKeyState(KEY_INPUT_SPACE) == Held && Held_jump < 24)
	{
		j_velocity = player->Get_Velocity();
		j_velocity.y += -0.2 /** delta_seconde*/;
		player->Set_Velocity(j_velocity);
		Held_jump++;
	}

	if (j_velocity.y >= 0 && j_velocity.y < 12)
	{
		j_velocity.y += 2 /** delta_seconde*/;
		player->Set_Velocity(j_velocity);
	}
	
	
	

	if (this->player->jump_flag == true)
	{
		if (input->GetKeyState(KEY_INPUT_A) == Pressed || input->GetKeyState(KEY_INPUT_A) == Held
			|| input->GetKeyState(KEY_INPUT_D) == Pressed || input->GetKeyState(KEY_INPUT_D) == Held)
		{
			player->SetNextState(ePlayerState::walk);
		}

		if (input->GetKeyState(KEY_INPUT_A) == None && input->GetKeyState(KEY_INPUT_D) == None)
		{
			player->SetNextState(ePlayerState::idle);
		}
	}

}
void JumpingState::Draw() const
{

}

void JumpingState::Finalize()
{

}

ePlayerState JumpingState::GetState() const
{
	return ePlayerState::jump;
}