#include "OneUpMush.h"
#include "../../Utility/ResourceManager.h"

OneUpMush::OneUpMush()
{

}

OneUpMush::~OneUpMush()
{

}

void OneUpMush::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImageResource("Resource/Images/Item/1up_mushroom.png")[0];	//�����摜�ݒ�

	collision.is_blocking = true;
	collision.object_type = eItem;
	collision.item_type = eOneup;		//�I�u�W�F�N�g�̃^�C�v�ݒ�
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.box_size = Vector2D(8, 8);

	//���C���[�ݒ�
	z_layer = 4;

	//�����̐ݒ�
	is_mobility = true;

	is_ground = true;



	//�A�C�e�����o�Ă������̉��𗬂�
	PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);
}

void OneUpMush::Update(float delta_seconde)
{
	//�n�R����o�Ă��鏈��
	ItemPush();

	if (hit_flag == false)
	{
		is_ground = false;
	}

	//�{�b�N�X����ł��瓖���蔻���ʏ�ɂ���
	if (box_out == true)
	{
		collision.box_size = Vector2D(32, 32);
	}

	//�ړ�����
	Movement(delta_seconde);

	hit_flag = false;
}

void OneUpMush::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

//void OneUpMush::Finalize()
//{
//
//}