#include "ItemBase.h"

ItemBase::ItemBase() : animation_count(0.0f),
animation_time(0.0f),
item_type(eNull)
{

}

ItemBase::~ItemBase()
{

}

//当たり判定処理
void ItemBase::OnHitCollision(GameObject* hit_object)
{

}

//跳ねる処理
void ItemBase::ItemPush()
{

}

//タイプ取得処理
Items ItemBase::GetItemType()
{
	return this->item_type;
}