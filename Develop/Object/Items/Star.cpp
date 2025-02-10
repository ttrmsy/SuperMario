#include "Star.h"
#include "../../Utility/ResourceManager.h"

#define STAR_JUMP	(30.0f)			//�X�^�[�̃W�����v��

Star::Star()
{

}

Star::~Star()
{

}

void Star::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImageResource("Resource/Images/Item/star.png", 4, 4, 1, 32, 32);

	collision.is_blocking = true;
	collision.object_type = eItem;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.box_size = Vector2D(32, 32);

	//���C���[�ݒ�
	z_layer = 4;

	//�����̐ݒ�
	is_mobility = true;

	is_ground = true;

	//�I�u�W�F�N�g�̃^�C�v�ݒ�
	item_type = eStar;

	//�A�C�e�����o�Ă������̉��𗬂�
	PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);
}

//�X�V����
void Star::Update(float delta_seconde)
{
	//�n�R����o�Ă��鏈��
	ItemPush();

	//�I�u�W�F�N�g�ɓ������Ă��Ȃ���Βn�ʂɓ������Ă��Ȃ�����ɂ���
	if (hit_flag == false)
	{
		is_ground = false;
	}

	//�n�ʂɐG��Ă����璵�˂�
	if (is_ground == true)
	{
		this->velocity.y = -STAR_JUMP;
	}

	//�ړ�����
	Movement(delta_seconde);

	//animation����
	AnimationControl(delta_seconde);

	//�����蔻���false�ɂ���
	hit_flag = false;
}

//�`�揈��
void Star::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Star::Finalize()
{

}

//�A�j���[�V��������
void Star::AnimationControl(float delta_seconde)
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