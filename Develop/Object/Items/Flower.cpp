#include "Flower.h"
#include "../../Utility/ResourceManager.h"

Flower::Flower()
{

}

Flower::~Flower()
{

}

void Flower::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImageResource("Resource/Images/Item/flower.png", 4, 4, 1, 32, 32);

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
	item_type = eFlower;

	//�A�C�e�����o�Ă������̉��𗬂�
	PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);
}

void Flower::Update(float delta_seconde)
{
	ItemPush();

	AnimationControl(delta_seconde);
}

void Flower::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Flower::Finalize()
{

}

void Flower::AnimationControl(float delta_seconde)
{
	animation_time += delta_seconde;

	if (animation_time >= (1.0f / 16.0f))
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