#include "Pipe.h"
#include "DxLib.h"

void Pipe::Initialize()
{
	pipe_image[0] = LoadGraph("Resource/Images/dokan_left_up.png");
	pipe_image[1] = LoadGraph("Resource/Images/dokan_left_down.png");
	pipe_image[2] = LoadGraph("Resource/Images/dokan_right_up.png");
	pipe_image[3] = LoadGraph("Resource/Images/dokan_right_down.png");

	collision.object_type = ePipe;
	collision.hit_object_type.push_back(ePlayer);
	collision.hit_object_type.push_back(eEnemy);
	collision.hit_object_type.push_back(eItem);

	collision.box_size = Vector2D(32, 32);
	
	image = pipe_image[0];
}

void Pipe::Update(float delta_seconde)
{

}

void Pipe::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Pipe::Finalize()
{

}

void Pipe::OnHitCollision(GameObject* hit_object)
{
	//Vector2D diff, dv;
	//Vector2D target_boxsize, this_boxsize;
	//diff = 0.0f;
	//dv = 0.0f;
	//Vector2D target_location = hit_object->GetLocation();
	//Collision target_collision = hit_object->GetCollision();

	//target_boxsize = hit_object->GetCollision().box_size;
	//this_boxsize = this->collision.box_size;


	////2“_ŠÔ‚Ì‹——£‚ð‹‚ß‚é
	//diff = this->location - target_location;

	//if (diff.x > 0)
	//{
	//	if (diff.y > 0)
	//	{
	//		dv.x = (target_location.x + target_boxsize.x / 2) - (this->location.x - this_boxsize.x / 2);
	//		dv.y = (target_location.y + target_boxsize.y / 2) - (this->location.y - this_boxsize.y / 2);

	//		if (dv.x > dv.y)
	//		{
	//			this->location.y += dv.y;
	//		}
	//		else
	//		{
	//			this->location.x += dv.x;
	//		}
	//	}
	//	else
	//	{
	//		dv.x = (target_location.x + target_boxsize.x / 2) - (this->location.x - this_boxsize.x / 2);
	//		dv.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);

	//		if (dv.x > dv.y)
	//		{
	//			this->location.y += -dv.y;
	//		}
	//		else
	//		{
	//			this->location.x += dv.x;
	//		}
	//	}
	//}
	//else
	//{
	//	if (diff.y > 0)
	//	{
	//		dv.x = (this->location.x + this_boxsize.x / 2) - (target_location.x - target_boxsize.x / 2);
	//		dv.y = (target_location.y + target_boxsize.y / 2) - (this->location.y - this_boxsize.y / 2);

	//		if (dv.x > dv.y)
	//		{
	//			this->location.y += dv.y;
	//		}
	//		else
	//		{
	//			this->location.x += -dv.x;
	//		}
	//	}
	//	else
	//	{
	//		dv.x = (this->location.x + this_boxsize.x / 2) - (target_location.x - target_boxsize.x / 2);
	//		dv.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);

	//		if (dv.x > dv.y)
	//		{
	//			this->location.y += -dv.y;
	//		}
	//		else
	//		{
	//			this->location.x += -dv.x;
	//		}
	//	}
	//}
}

const Vector2D& Pipe::GetLocation() const
{
	return location;
}

const Collision& Pipe::GetCollision() const
{
	return collision;
}

const unsigned char Pipe::GetZLayer() const
{
	return z_layer;
}

const bool Pipe::GetMobility() const
{
	return is_mobility;
}

void Pipe::Set_Image(int number)
{
	switch (number)
	{
	case 0:
		image = pipe_image[0];
		break;

	case 1:
		image = pipe_image[1];
		break;

	case 2:
		image = pipe_image[2];
		break;

	case 3:
		image = pipe_image[3];
		break;
	}
}