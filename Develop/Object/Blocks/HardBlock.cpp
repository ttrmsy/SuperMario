#include "HardBlock.h"
#include "DxLib.h"

void HardBlock::Initialize()
{
	image = LoadGraph("Resource/Images/Block/kai_block.png");

	collision.object_type = eHardBlock;
	collision.hit_object_type.push_back(ePlayer);
	collision.hit_object_type.push_back(eEnemy);
	collision.hit_object_type.push_back(eItem);
	collision.box_size = Vector2D(32, 32);

	is_mobility = false;

}

void HardBlock::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void HardBlock::Finalize()
{

}

void HardBlock::OnHitCollision(GameObject* hit_object)
{

}

const Vector2D& HardBlock::GetLocation() const
{
	return location;
}

const Collision& HardBlock::GetCollision() const
{
	return collision;
}

const unsigned char HardBlock::GetZLayer() const
{
	return z_layer;
}

const bool HardBlock::GetMobility() const
{
	return is_mobility;
}
