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
	image = rm->GetImageResource("Resource/Images/Item/mushroom.png")[0];		//初期画像の設定

	collision.is_blocking = true;
	collision.object_type = eItem;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.box_size = Vector2D(32, 32);

	//レイヤー設定
	z_layer = 4;

	//可動性の設定
	is_mobility = true;

	//オブジェクトのタイプ設定
	item_type = eMushroom;

	//アイテムが出てきた時の音を流す
	PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);
}

//更新処理
void Mushroom::Update(float delta_seconde)
{
	//ハコから出てくる処理
	ItemPush();

	//移動処理
	Movement(delta_seconde);

	velocity.x = 2.0f;

}

//描画処理
void Mushroom::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Mushroom::Finalize()
{

}