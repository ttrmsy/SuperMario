#include "ItemBase.h"

ItemBase::ItemBase() : animation_count(0.0f),
animation_time(0.0f),
item_type(eNull)
{

}

ItemBase::~ItemBase()
{

}

//“–‚½‚è”»’èˆ—
void ItemBase::OnHitCollision(GameObject* hit_object)
{

}

//’µ‚Ë‚éˆ—
void ItemBase::ItemPush()
{

}

//ƒ^ƒCƒvŽæ“¾ˆ—
Items ItemBase::GetItemType()
{
	return this->item_type;
}