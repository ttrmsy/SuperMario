#include "ItemBase.h"
#include "../GameObjectManager.h"
#include "../../Utility/ResourceManager.h"

ItemBase::ItemBase() : animation_count(0.0f),
animation_time(0.0f),
item_type(eNull),
box_out(false),
item_sound(NULL)
{
	//リソースマネージャーのインスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
	item_sound = rm->GetSoundResource("Resource/Sounds/SE_ItemAppearance.wav");	//アイテムが出てきた時の音

	//アイテムが出てきた時の音を流す
	PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);
}

ItemBase::~ItemBase()
{

}

void ItemBase::Movement()
{

}

//当たり判定処理
void ItemBase::OnHitCollision(GameObject* hit_object)
{
	// 当たったオブジェクトがプレイヤーだったら、削除する
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer && box_out == true)
	{
		//ゲームオブジェクトのポインタを取得
		GameObjectManager* gm_p = GameObjectManager::GetInstance();

		PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);

		gm_p->DestroyGameObject(this);
	}
}

//跳ねる処理
void ItemBase::ItemPush()
{
	if (this->location.y > old_loction.y - 32.0f)
	{
		location.y -= 1.0f;

		box_out = false;

		return;
	}

	box_out = true;

}

void ItemBase::Bounce()
{
	/*if (this->location.y < this->location.y - 32.0f)
	{
		location.y--;
	}*/
}

//タイプ取得処理
Items ItemBase::GetItemType()
{
	return this->item_type;
}

//生成時の座標保存
void ItemBase::SetOldLocation(Vector2D a)
{
	this->old_loction = a;
}