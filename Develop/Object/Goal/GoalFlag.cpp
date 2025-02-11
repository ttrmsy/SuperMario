#include "GoalFlag.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

void GoalFlag::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	flag_image = rm->GetImageResource("Resource/Images/flag.png", 1, 1, 1, 32, 32);
	pole_image = rm->GetImageResource("Resource/Images/pole_down.png", 1, 1, 1, 32, 32);

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
	if (image == pole_image[0])
	{
		__super::Draw(screen_offset);
	}
	else	//ゴールフラグトップ（一番上）の描画処理
	{
		Vector2D graph_location = this->location - screen_offset;
		//X座標がずれているためOBJECT_SIZE(32) ÷ 2した値分横に描画する
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
		image = pole_image[0];
		break;
	}
}