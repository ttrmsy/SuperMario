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

	collision.object_type = eItem;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.box_size = Vector2D(32, 32);

	//���C���[�ݒ�
	z_layer = 4;

	//�����̐ݒ�
	is_mobility = false;

	//�I�u�W�F�N�g�̃^�C�v�ݒ�
	item_type = eCoin;

	//�A�C�e�����o�Ă������̉��𗬂�
	PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);
}

void OneUpMush::Update(float delta_seconde)
{
	//�n�R����o�Ă��鏈��
	ItemPush();

	//�ړ�����
	Movement(delta_seconde);

	velocity.x = 2.0f;

}

void OneUpMush::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

//void OneUpMush::Finalize()
//{
//
//}