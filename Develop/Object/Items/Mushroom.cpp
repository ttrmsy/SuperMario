#include "Mushroom.h"
#include "../../Utility/ResourceManager.h"

Mushroom::Mushroom()
{

}

Mushroom::~Mushroom()
{

}

void Mushroom::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImageResource("Resource/Images/Item/mushroom.png")[0];		//�����摜�̐ݒ�

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
	item_type = eMushroom;

	//�A�C�e�����o�Ă������̉��𗬂�
	PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);
}

//�X�V����
void Mushroom::Update(float delta_seconde)
{
	//�n�R����o�Ă��鏈��
	ItemPush();

	if (hit_flag == false)
	{
		is_ground = false;
	}	

	//�ړ�����
	Movement(delta_seconde);

	hit_flag = false;
}

//�`�揈��
void Mushroom::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Mushroom::Finalize()
{

}