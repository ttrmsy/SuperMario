#include "Brick.h"
#include "DxLib.h"

void Brick::Initialize()
{
	collision.object_type = eBlock;
	collision.hit_object_type.push_back(ePlayer);
	collision.hit_object_type.push_back(eEnemy);
	collision.hit_object_type.push_back(eItem);
	collision.box_size = Vector2D(32, 32);

	image = LoadGraph("Resource/Images/Block/block.png");

	is_mobility = false;

	//’Ç‰Á
	up_count = 0;
	down_count = 0;


}

void Brick::Update(float delta_seconde)
{
	if (hit_flag == true)
	{
		if (up_count < 8)
		{
			this->location.y += -1;
			up_count++;
		}
		else if (down_count < 8)
		{
			this->location.y += 1;
			down_count++;
		}
	}
	AnimationControl(delta_seconde);
}

void Brick::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Brick::Finalize()
{

}

void Brick::OnHitCollision(GameObject* hit_object)
{
	Vector2D diff = 0.0f;
	Vector2D target_boxsize, this_boxsize;

	diff = this->location - target_boxsize;

	if (diff.y < 0)
	{
		if (hit_object->GetCollision().object_type == ePlayer)
		{
			PlaySound("Resource/Sounds/SE_Block.wav", DX_PLAYTYPE_BACK);
			hit_flag = true;
		}
	}

}

const Vector2D& Brick::GetLocation() const
{
	return location;
}

const Collision& Brick::GetCollision() const
{
	return collision;
}

const unsigned char Brick::GetZLayer() const
{
	return z_layer;
}

const bool Brick::GetMobility() const
{
	return is_mobility;
}

void Brick::AnimationControl(float delta_seconde)
{

}
