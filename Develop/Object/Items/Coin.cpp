#include "Coin.h"
#include "../../Utility/ResourceManager.h"

Coin::Coin()
{

}

Coin::~Coin()
{

}

void Coin::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImageResource("Resource/Images/Item/coin.png", 4, 4, 1, 32, 32);

	collision.is_blocking = true;
	collision.object_type = eItem;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.box_size = Vector2D(32, 32);

	//���C���[�ݒ�
	z_layer = 4;

	//�����̐ݒ�
	is_mobility = false;

	//�����摜�ݒ�
	image = move_animation[0];

	animation_count = 0;

	animation_time = 0;

	//�I�u�W�F�N�g�̃^�C�v�ݒ�
	item_type = eCoin;
}

void Coin::Update(float delta_seconde)
{
	AnimationControl(delta_seconde);
}

void Coin::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Coin::Finalize()
{

}

void Coin::AnimationControl(float delta_seconde)
{
	animation_time += delta_seconde;

	if (animation_time >= 0.5)
	{
		animation_time = 0.0f;

		image = move_animation[animation_count];

		animation_count++;

		if (animation_count > 3)
		{
			animation_count = 0;
		}

	}
}