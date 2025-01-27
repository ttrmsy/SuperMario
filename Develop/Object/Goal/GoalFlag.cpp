#include "GoalFlag.h"
#include "DxLib.h"

void GoalFlag::Initialize()
{
	flag_image[0] = LoadGraph("Resource/Images/flag.png");
	flag_image[1] = LoadGraph("Resource/Images/pole_down.png");

	collision.object_type = eGoal;
	collision.hit_object_type.push_back(ePlayer);
	collision.box_size = Vector2D(16, 32);

	image = flag_image[0];

	is_mobility = false;
}

void GoalFlag::Update(float delta_seconde)
{

}

void GoalFlag::Draw(const Vector2D& screen_offset) const
{
	if (image == flag_image[1])
	{
		__super::Draw(screen_offset);
	}
	else
	{
		Vector2D graph_location = this->location - screen_offset;
		DrawRotaGraphF(graph_location.x - OBJECT_SIZE / 2, graph_location.y, 1.0, 0.0, image, TRUE, filp_flag);
	}
	
}

void GoalFlag::Finalize()
{
	
}

void GoalFlag::OnHitCollision(GameObject* hit_object)
{

}

const Vector2D& GoalFlag::GetLocation() const
{
	return location;
}

const Collision& GoalFlag::GetCollision() const
{
	return collision;
}

const unsigned char GoalFlag::GetZLayer() const
{
	return z_layer;
}

const bool GoalFlag::GetMobility() const
{
	return is_mobility;
}

void GoalFlag::Set_Image(int number)
{
	switch (number)
	{
	case 0:
		image = flag_image[0];
		break;

	case 1:
		image = flag_image[1];
		break;
	}
}