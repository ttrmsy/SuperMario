#include "FireBall.h"
#include "../../Utility/ResourceManager.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define SPEED (40)
#define D_GRAVITY (9.807f)		//d—Í‰Á‘¬“x

void FireBall::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	fire_image = rm->GetImageResource("Resource/Images/Mario/fireball.png", 1, 1, 1, 32, 32);
	image = fire_image[0];
	collision.object_type = eFireBall;
	collision.box_size = Vector2D(32, 32);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	g_velocity = 0.0f;

	velocity.x = 20;

	is_mobility = true;

	radian = 0.1 * (M_PI / 180);
}

void FireBall::Update(float delta_seconde)
{
	if (filp_flag == true)
	{
		velocity.x *= -1;
	}

	g_velocity += D_GRAVITY * delta_seconde;
	velocity.y += g_velocity;

	radian += radian;

	Movement(delta_seconde);
}

void FireBall::Draw(const Vector2D& screen_offset) const
{
	Vector2D graph_location = this->location - screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, radian, image, TRUE, filp_flag);
	/*__super::Draw(screen_offset);*/
}

void FireBall::Finalize()
{
	fire_image.clear();
}

void FireBall::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetCollision().object_type == eGround)
	{
		g_velocity = 0.0f;
		velocity.y = 0;
		velocity.y = -10;
	}
}

void FireBall::Movement(float delta_seconde)
{
	location += velocity * SPEED * delta_seconde;
}

void FireBall::Set_Filpflag(bool flag)
{
	filp_flag = flag;
}