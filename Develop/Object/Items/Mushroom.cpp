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
	collision.box_size = Vector2D(32, 32);

	//���C���[�ݒ�
	z_layer = 4;

	//�����̐ݒ�
	is_mobility = false;

	//�I�u�W�F�N�g�̃^�C�v�ݒ�
	item_type = eMushroom;
}

//�X�V����
void Mushroom::Update(float delta_seconde)
{
	ItemPush();
}

//�`�揈��
void Mushroom::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Mushroom::Finalize()
{

}