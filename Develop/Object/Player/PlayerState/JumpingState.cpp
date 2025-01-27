#include "JumpingState.h"
#include "../../../Utility/InputManager.h"
#include "DxLib.h"

#define JUMP_VECTOR (-10.0f)
#define D_GRAVITY (9.807f)		//�d�͉����x

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
	PlayMusic("Resource/Sounds/SE_SuperJump.wav", DX_PLAYTYPE_BACK);
}

void JumpingState::Update()
{
	InputManager* input = InputManager::GetInstance();

	//SPACE�L�[������������ƃW�����v�̍������ω�����
	if (input->GetKeyState(KEY_INPUT_SPACE) == Held && Held_jump < 24)
	{
		j_velocity = player->Get_Velocity();
		j_velocity.y += -0.5;
		player->Set_Velocity(j_velocity);
		Held_jump++;
	}

	//�d�͑��x�̌v�Z
	/*if (j_velocity.y < 0)
	{
		g_velocity += D_GRAVITY / 444.0f;
		j_velocity.y += g_velocity;
		player->Set_Velocity(j_velocity);
	}
	else*/ if (j_velocity.y >= 0 && j_velocity.y < 12)
	{
		j_velocity.y += 2;
		player->Set_Velocity(j_velocity);
	}
	

	if (this->player->jump_flag == true)
	{
		if (input->GetKeyState(KEY_INPUT_A) == Pressed || input->GetKeyState(KEY_INPUT_A) == Held
			|| input->GetKeyState(KEY_INPUT_D) == Pressed || input->GetKeyState(KEY_INPUT_D) == Held)
		{
			g_velocity = 0;
			player->SetNextState(ePlayerState::walk);
		}

		if (input->GetKeyState(KEY_INPUT_A) == None && input->GetKeyState(KEY_INPUT_D) == None)
		{
			g_velocity = 0;
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