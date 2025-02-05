#include "ItemBase.h"
#include "../GameObjectManager.h"
#include "../../Utility/ResourceManager.h"

#define ITEM_SPEED		(50.0f)

ItemBase::ItemBase() : animation_count(0.0f),
animation_time(0.0f),
item_type(eNull),
box_out(false),
item_sound(NULL)
{
	//リソースマネージャーのインスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
	item_sound = rm->GetSoundResource("Resource/Sounds/SE_ItemAppearance.wav");	//アイテムが出てきた時の音
}

ItemBase::~ItemBase()
{

}

void ItemBase::Movement(float delta_seconde)
{


	this->location += velocity * ITEM_SPEED * delta_seconde;
}

//当たり判定処理
void ItemBase::OnHitCollision(GameObject* hit_object)
{
	

	// 当たったオブジェクトがプレイヤーだったら、削除する
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer && box_out == true)
	{
		//ゲームオブジェクトのポインタを取得
		GameObjectManager* gm_p = GameObjectManager::GetInstance();

		//PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);

		gm_p->DestroyGameObject(this);
	}
}

//ボックスから出てくる処理
void ItemBase::ItemPush()
{
	//アイテムがコイン以外の場合
	if (item_type != eCoin)
	{
		if (this->location.y > old_loction.y - 27.0f)
		{
			location.y -= 0.5f;

			velocity = 0.0f;

			box_out = false;

			return;
		}
	}
	else  //コインだった場合
	{
		if (this->location.y > old_loction.y - ((32.0f * 3) - 5.0f))
		{
			location.y -= 2.0f;

			velocity = 0.0f;

			box_out = false;

			return;
		}
	}
	
	box_out = true;

}

//跳ねる処理
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