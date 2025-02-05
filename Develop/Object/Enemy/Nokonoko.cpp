#include "Nokonoko.h"
#include "../../Utility/ResourceManager.h"

#define SPEED (30)
#define D_GRAVITY (9.807f)		//�d�͉����x

void Nokonoko::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImageResource("Resource/Images/Enemy/nokonoko.png", 2, 2, 1, 32, 64);
	die_animation = rm->GetImageResource("Resource/Images/Enemy/nokonoko_revival.png", 2, 2, 1, 32, 32);

	for (int i = 0; i < 2; i++)
	{
		if (move_animation[i] == NULL)
		{
			throw("�m�R�m�R�̉摜������܂���\n");
		}
	}
	collision.is_blocking = true;
	collision.object_type = eEnemy;
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.box_size = Vector2D(32, 32);

	//���C���[�ݒ�
	z_layer = 4;

	//�����̐ݒ�
	is_mobility = true;

	image = move_animation[0];

	velocity.x = -1.0f;

	animation_count = 0;

	animation_time = 0;

	state = live;

	die_time = 0;

	image_offset = 16;
}

void Nokonoko::Update(float delta_seconde)
{
	if (is_ground == false)
	{
		velocity.y = 5;
	}
	else
	{
		velocity.y = 0;
	}

	switch (state)
	{
	case live:
		image_offset = 16;
		is_mobility = true;
		collision.box_size = Vector2D(32, 32);
		Movement(delta_seconde);
		AnimationControl(delta_seconde);
		break;

	case down:
		image_offset = 0;
		is_mobility = false;
		die_time++;
		velocity.y = 0;
		collision.box_size = Vector2D(32, 32);
		image = die_animation[0];
		Movement(delta_seconde);

		if (die_time > 800)
		{
			image = die_animation[1];
		}
		
		if (die_time == 1000)
		{
			state = live;
			image = move_animation[0];
			die_time = 0;
		}

		is_ground = false;

	}
}

void Nokonoko::Draw(const Vector2D& screen_offset) const
{
	Vector2D graph_location = this->location - screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y - image_offset, 1.0, 0.0, image, TRUE, filp_flag);
}

void Nokonoko::Finalize()
{

}

void Nokonoko::OnHitCollision(GameObject* hit_object)
{
	Vector2D diff, dv;
	Vector2D target_boxsize, this_boxsize;
	diff = 0.0f;
	dv = 0.0f;
	Vector2D target_location = hit_object->GetLocation();

	target_boxsize = hit_object->GetCollision().box_size;
	this_boxsize = this->collision.box_size;

	//2�_�Ԃ̋��������߂�
	diff = this->location - target_location;

	//���g��Hit�����I�u�W�F�N�g�����E���ɂ����Ƃ�
	if (diff.x > 0)
	{
		//���g��Hit�����I�u�W�F�N�g���������ɂ����Ƃ�
		if (diff.y > 0)
		{
			if (state == down)
			{
				dv.x = (target_location.x + target_boxsize.x / 2) - (this->location.x - this_boxsize.x / 2);
				dv.y = (target_location.y + target_boxsize.y / 2) - (this->location.y - this_boxsize.y / 2);

				if (dv.x > dv.y)
				{
					if (state != down)
					{
						this->location.y += dv.y;
					}
					
				}
				else
				{
					if (state != down)
					{
						this->location.x += dv.x;
					}
				}
			}

			if (hit_object->GetCollision().object_type == ePlayer)
			{
				if (this->state == down)
				{
					this->velocity.x = 6;
				}
				else
				{
					state = down;
					PlaySound("Resource/Sounds/Se_StepOn.wav", DX_PLAYTYPE_BACK);
				}
				
			}

		}
		else	//���g��Hit�����I�u�W�F�N�g�����㑤�ɂ����Ƃ�
		{
			dv.x = (target_location.x + target_boxsize.x / 2) - (this->location.x - this_boxsize.x / 2);
			dv.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);

			if (dv.x > dv.y)
			{
				this->location.y += -dv.y;
			}
			else
			{
		
				this->location.x += dv.x;
			}

			if (hit_object->GetCollision().object_type == eGround)
			{
				is_ground = true;
				g_velocity = 0;
				this->velocity.y = 0;
			}
		}
	}
	else	//���g��Hit�����I�u�W�F�N�g���������ɂ����Ƃ�
	{
		//���g��Hit�����I�u�W�F�N�g���������ɂ����Ƃ�
		if (diff.y > 0)
		{
			
				dv.x = (this->location.x + this_boxsize.x / 2) - (target_location.x - target_boxsize.x / 2);
				dv.y = (target_location.y + target_boxsize.y / 2) - (this->location.y - this_boxsize.y / 2);

				if (dv.x > dv.y)
				{
					if (state != down)
					{
						this->location.y += dv.y;
					}
				}
				else
				{
					this->location.x += -dv.x;
				}

	

				if (hit_object->GetCollision().object_type == ePlayer)
				{
					if (this->state == down)
					{
						this->velocity.x = -3;
					}
					else
					{
						velocity.x = 0;
						state = down;
						PlaySound("Resource/Sounds/Se_StepOn.wav", DX_PLAYTYPE_BACK);
					}
					
				}
		}
		else	//���g��Hit�����I�u�W�F�N�g�����㑤�ɂ����Ƃ�
		{
			dv.x = (this->location.x + this_boxsize.x / 2) - (target_location.x - target_boxsize.x / 2);
			dv.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);

			if (dv.x > dv.y)
			{
				if (state != down)
				{
					this->location.y += -dv.y;
				}

			}
			else
			{
				if (state != down)
				{
					this->location.x += -dv.x;
				}
			}

			if (hit_object->GetCollision().object_type == eGround)
			{
				is_ground = true;
				g_velocity = 0;
				this->velocity.y = 0;
			}


			if (hit_object->GetCollision().object_type == ePlayer)
			{
				if (this->state == down)
				{
					this->velocity.x = -3;
				}
				else
				{
					velocity.x = 0;
				}
			}
		}
	}
}

const Vector2D& Nokonoko::GetLocation() const
{
	return location;
}

const Collision& Nokonoko::GetCollision() const
{
	return collision;
}

const unsigned char Nokonoko::GetZLayer() const
{
	return z_layer;
}

const bool Nokonoko::GetMobility() const
{
	return is_mobility;
}

void Nokonoko::Filp_flag(bool flag)
{
	filp_flag = flag;
}

void Nokonoko::Set_Velocity(Vector2D velocity)
{
	this->velocity = velocity;
}

void Nokonoko::Set_Camera(Camera* c)
{
	camera = c;
}

void Nokonoko::Movement(float delta_seconde)
{
	location += velocity * SPEED * delta_seconde;
}

void Nokonoko::AnimationControl(float delta_seconde)
{
	animation_time += delta_seconde;

	if (animation_time >= 0.5)
	{
		animation_time = 0.0f;

		image = move_animation[animation_count];

		animation_count++;

		if (animation_count > 1)
		{
			animation_count = 0;
		}
	}
}
