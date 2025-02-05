#include "Player.h"
#include "../../Utility/ResourceManager.h"
#include "PlayerState/PlayerStateFactory.h"
#include "../../Utility/Application.h"
#include "DxLib.h"
#include "../GameObjectManager.h"


#define D_GRAVITY (9.807f)		//�d�͉����x
#define P_SPEED (50.0f)

void Player::Initialize()
{
	player_state = PlayerStateFactory::Get((*this), ePlayerState::idle);
	next_state = none;

	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImageResource("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);

	collision.is_blocking = true;
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.hit_object_type.push_back(eObjectType::eItem);
	collision.box_size = Vector2D(OBJECT_SIZE,OBJECT_SIZE);

	//���C���[�ݒ�
	z_layer = 5;

	//�����̐ݒ�
	is_mobility = true;

	//�A�j���[�V�����摜�̐ݒ�
	image = move_animation[0];

	//�摜���]�t���O�̐ݒ�
	filp_flag = FALSE;	

	//�n�ʂɒ��n���Ă��邩����t���O�̐ݒ�
	is_ground = false;

	//�W�����v�ł����Ԃ��̔���t���O
	jump_flag = true;

	/*
	 �I�u�W�F�N�g�Ƀq�b�g���Ă��� = true
	�I�u�W�F�N�g�Ƀq�b�g���Ă��Ȃ� = false
	*/
	hit_flag = true;

	//���X�N���[���p�J�����̃|�C���^
	camera = nullptr;

	//�X���C�h�i�u���[�L�j�t���O
	slide_flag = false;

	state = live;

}

void Player::Update(float delta_seconde)
{
	//ePlayerState p_state;
	slide_flag = false;

	
	if (next_state != ePlayerState::none)
	{
		player_state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::none;
	}

	p_state = GetPlayerState();

	//�v���C���[�̏�ԂŁA������ς���
	if (state == live)
	{
		switch (p_state)
		{
		case ePlayerState::idle:
			image = move_animation[0];
			/*player_state->Initialize();*/
			player_state->Update();
			break;

		case ePlayerState::walk:
			/*player_state->Initialize();*/
			player_state->Update();
			AnimationControl(delta_seconde);
			break;

		case ePlayerState::jump:
			player_state->Update();
			image = move_animation[5];
			break;

		default:
			break;
		}
	}
	else if(state == die)
	{
		image = move_animation[6];

		GameObjectManager* m = GameObjectManager::GetInstance();
		m->DestroyGameObject(this);

	}

	
	if (is_ground == false)
	{
		g_velocity += D_GRAVITY / 444.0f;
		velocity.y += g_velocity;
	}
	else
	{
		velocity.y = 0;
	}

	

	if (hit_flag == false && p_state != jump)
	{
		velocity.y = 6;
		jump_flag = false;
	}
	
	hit_flag = false;
	
	if (camera != nullptr)
	{
		float x = camera->Get_CameraLocation().x;
		if (this->location.x - OBJECT_SIZE / 2 < x - D_WIN_MAX_X / 2)
		{
			if (velocity.x < 1.0e-6f)
			{
				velocity.x = 0;
			}
		}
	}
	
	Movement(delta_seconde);

	
	DeathCount();
}

void Player::Draw(const Vector2D& screen_offset) const
{
	//�e�N���X�̏������Ăяo��
	__super::Draw(screen_offset);

	SetFontSize(15);
	DrawFormatString(100, 100, GetColor(255, 0, 0), "Vx:%f0,Vy:%f0", velocity.x, velocity.y);
	DrawFormatString(100, 150, GetColor(255, 0, 0), "Bx:%f0,By:%f0", dv.x,dv.y);
	Vector2D ul = location - (collision.box_size / 2);
	Vector2D br = location + (collision.box_size / 2);
	DrawBoxAA(ul.x - screen_offset.x, ul.y, br.x - screen_offset.x, br.y, GetColor(255, 0, 0), FALSE);

	DrawFormatString(10, 30, 0xffffff, "%f", this->location.y, TRUE);
	DrawFormatString(10, 10, 0xffffff, "%d", is_death, TRUE);
}

void Player::Finalize()
{
	move_animation.clear();
}

void Player::OnHitCollision(GameObject* hit_object)
{
	hit_flag = true;

	Vector2D diff; //dv;
	Vector2D target_boxsize, this_boxsize;
	diff = 0.0f;
	dv = 0.0f;
	Vector2D target_location = hit_object->GetLocation();
	Collision target_collision = hit_object->GetCollision();

	target_boxsize = hit_object->GetCollision().box_size;
	this_boxsize = this->collision.box_size;
	

	//2�_�Ԃ̋��������߂�
	diff = this->location - target_location;
	
	if (diff.x >= 0)	//���g��Hit�����I�u�W�F�N�g�����E���ɂ����Ƃ�
	{
		if (diff.y > 0)	//���g��Hit�����I�u�W�F�N�g���������ɂ����Ƃ�
		{
      		dv.x = (target_location.x + target_boxsize.x / 2) - (this->location.x - this_boxsize.x / 2);
			dv.y = (target_location.y + target_boxsize.y / 2) - (this->location.y - this_boxsize.y / 2);
			
			if (dv.x > dv.y)
			{
				this->location.y += dv.y;
				velocity.y = 0;
			}
			else
			{
				this->location.x += dv.x;
				/*if (target_collision.object_type == eEnemy)
				{
					state = die;
				}*/
			}
			
			
	
		}
		else	//���g��Hit�����I�u�W�F�N�g�����㑤�ɂ����Ƃ�
		{
			dv.x = (target_location.x + target_boxsize.x / 2) - (this->location.x - this_boxsize.x / 2);
			dv.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);
			
			if (dv.x > dv.y)
			{
				if (target_collision.object_type != eEnemy)
				{
					this->location.y += -dv.y;
					
					if (target_collision.object_type == eGround || target_collision.object_type == eBlock)
					{
 						is_ground = true;
						jump_flag = true;
						g_velocity = 0;
					}

					
					
				}
				else
				{
					if (hit_object->GetMobility() == true)
					{
						velocity.y = 0;
						velocity.y += -20.0;
					}
				}
			
			}
			else
			{
				this->location.x += dv.x;
			}
		}
	}
	else	//���g��Hit�����I�u�W�F�N�g���������ɂ����Ƃ�
	{
		if (diff.y > 0)	//���g��Hit�����I�u�W�F�N�g���������ɂ����Ƃ�
		{
			dv.x = (this->location.x + this_boxsize.x / 2) - (target_location.x - target_boxsize.x / 2);
			dv.y = (target_location.y + target_boxsize.y / 2) - (this->location.y - this_boxsize.y / 2);

			if (dv.x < dv.y)
			{
				this->location.x += -dv.x;
			}
			else
			{
				this->location.y += dv.y;
				velocity.y = 0;
			}

			
		}
		else	//���g��Hit�����I�u�W�F�N�g�����㑤�ɂ����Ƃ�
		{
			dv.x = (this->location.x + this_boxsize.x / 2) - (target_location.x - target_boxsize.x / 2);
			dv.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);

			if (dv.x > dv.y)
			{
				if (target_collision.object_type != eEnemy)
				{
					this->location.y += -dv.y;

					
					if (target_collision.object_type == eGround || target_collision.object_type == eBlock)
					{
						is_ground = true;
						jump_flag = true;
						g_velocity = 0;
					}
					
					
				}
				else
				{
					if (hit_object->GetMobility() == true)
					{
						velocity.y = 0;
						velocity.y += -20.0;
					}
				}
				
			}
			else
			{
				this->location.x += -dv.x;
				/*if (target_collision.object_type == eEnemy)
				{
					state = die;
				}*/
			}
		}
	}


}


const Collision& Player::GetCollision() const
{
	return collision;
}

const unsigned char Player:: GetZLayer() const
{
	return z_layer;
}

const bool Player:: GetMobility() const
{
	return is_mobility;
}

ePlayerState Player::GetPlayerState() const
{
	return player_state->GetState();
}

void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}

void Player::SetFilp_flag(bool flag)
{
	filp_flag = flag;
}

bool Player::GetFilp_flag()
{
	return filp_flag;
}

Vector2D Player::Get_Velocity()
{
	return this->velocity;
}

void Player::Set_Velocity(Vector2D velocity)
{
	this->velocity = velocity;
}

void Player::Set_IsGround(bool flag)
{
	is_ground = flag;
}

void Player::Set_Camera(Camera* c)
{
	camera = c;
}

void Player::Set_SlideFlag(bool flag)
{
	slide_flag = flag;
}

void Player::Movement(float delta_second)
{
	location += velocity * P_SPEED * delta_second;
}

void Player::AnimationControl(float delta_second)
{
	//�ړ��A�j���[�V����
	animation_time += delta_second;

	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
	
		image = move_animation[animation_num[animation_count]];

		if (slide_flag == true)
		{
			image = move_animation[4];
		}

		animation_count++;
		
		if (animation_count >= 3)
		{
			animation_count = 0;
		}
		
	}

	

}


void Player::DeathCount()
{
	if (location.y >= 500 && eSceneType::eInGame)
	{
		is_death++;

	}
	else
	{
		is_death = 0;
	}
}

int Player::Get_DeathCount()
{
	return is_death;
}

