#include "ItemBase.h"

ItemBase::ItemBase() : animation_count(0.0f),
animation_time(0.0f),
item_type(eNull)
{

}

ItemBase::~ItemBase()
{

}

//�����蔻�菈��
void ItemBase::OnHitCollision(GameObject* hit_object)
{

}

//���˂鏈��
void ItemBase::ItemPush()
{

}

//�^�C�v�擾����
Items ItemBase::GetItemType()
{
	return this->item_type;
}