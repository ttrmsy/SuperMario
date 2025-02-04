#include "Kuribo.h"
#include "../../Utility/ResourceManager.h"

#define D_GRAVITY (9.807f)		//重力加速度
#define SPEED (30)

void Kuribo::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImageResource("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);

	collision.is_blocking = true;
	collision.object_type = eEnemy;
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.box_size = Vector2D(32, 32);

	//レイヤー設定
	z_layer = 4;

	//可動性の設定
	is_mobility = true;

	image = move_animation[0];

	velocity.x = -1.0f;

	animation_count = 0;

	animation_time = 0;

	state = live;

	die_time = 0;

}

void Kuribo::Update(float delta_seconde)
{
	float x = camera->Get_CameraLocation().x + D_WIN_MAX_X / 2;

	switch (state)
	{
	case live:
		if (location.x - OBJECT_SIZE / 2 < x)
		{
			Movement(delta_seconde);
			AnimationControl(delta_seconde);
		}
		break;

	case die:
		//is_mobility = false;
		image = move_animation[2];
		die_time++;
		break;
	}

}

void Kuribo::Draw(const Vector2D& screen_offset) const
{
	//親クラスの処理を呼び出す
	__super::Draw(screen_offset);

	Vector2D ul = location - (collision.box_size / 2);
	Vector2D br = location + (collision.box_size / 2);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
}

void Kuribo::Finalize()
{
	move_animation.clear();
}

void Kuribo::OnHitCollision(GameObject* hit_object)
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


	//2点間の距離を求める
	diff = this->location - target_location;

	if (diff.x > 0)	//自身がHitしたオブジェクトよりも右側にいたとき
	{
		if (diff.y > 0)	//自身がHitしたオブジェクトよりも下側にいたとき
		{
			dv.x = (target_location.x + target_boxsize.x / 2) - (this->location.x - this_boxsize.x / 2);
			dv.y = (target_location.y + target_boxsize.y / 2) - (this->location.y - this_boxsize.y / 2);

			state = die;
			PlaySound("Resource/Sounds/Se_StepOn.wav", DX_PLAYTYPE_BACK);

			if (dv.x > dv.y)
			{
				this->location.y += dv.y;
			}
			else
			{
				this->location.x += dv.x;
			}

			if (velocity.y < 0)
			{
				velocity.y = 0;
			}

		}
		else	//自身がHitしたオブジェクトよりも上側にいたとき
		{
			dv.x = (target_location.x + target_boxsize.x / 2) - (this->location.x - this_boxsize.x / 2);
			dv.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);

			if (dv.x > dv.y)
			{
				if (target_collision.object_type != eEnemy)
				{
					this->location.y += -dv.y;

					if (target_collision.object_type == eGround)
					{
						is_ground = true;
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
	else	//自身がHitしたオブジェクトよりも左側にいたとき
	{
		if (diff.y > 0)	//自身がHitしたオブジェクトよりも下側にいたとき
		{
			dv.x = (this->location.x + this_boxsize.x / 2) - (target_location.x - target_boxsize.x / 2);
			dv.y = (target_location.y + target_boxsize.y / 2) - (this->location.y - this_boxsize.y / 2);

			state = die;
			PlaySound("Resource/Sounds/Se_StepOn.wav", DX_PLAYTYPE_BACK);

			if (dv.x > dv.y)
			{
				this->location.y += dv.y;
			}
			else
			{
				this->location.x += -dv.x;
			}

			if (velocity.y < 0)
			{
				velocity.y = 0;
			}
		}
		else	//自身がHitしたオブジェクトよりも上側にいたとき
		{
			dv.x = (this->location.x + this_boxsize.x / 2) - (target_location.x - target_boxsize.x / 2);
			dv.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);

			if (dv.x > dv.y)
			{
				if (target_collision.object_type != eEnemy)
				{
					this->location.y += -dv.y;


					if (target_collision.object_type == eGround)
					{
						is_ground = true;
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
			}
		}
	}
}

const Vector2D& Kuribo::GetLocation() const
{
	return location;
}

const Collision& Kuribo::GetCollision() const
{
	return collision;
}

const unsigned char Kuribo::GetZLayer() const
{
	return z_layer;
}

const  bool Kuribo::GetMobility() const
{
	return is_mobility;
}

void Kuribo::Set_Player(Player* p)
{
	player = p;
}

void Kuribo::Filp_flag(bool flag)
{

}

void Kuribo::Set_Velocity(Vector2D velocity)
{

}

void Kuribo::Set_Camera(Camera* c)
{
	camera = c;
}

void Kuribo::Movement(float delta_seconde)
{
	location += velocity * SPEED * delta_seconde;
}

void Kuribo::AnimationControl(float delta_seconde)
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