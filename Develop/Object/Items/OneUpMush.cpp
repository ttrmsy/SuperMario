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
	image = rm->GetImageResource("Resource/Images/Item/1up_mushroom.png")[0];	//初期画像設定

	collision.object_type = eItem;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.box_size = Vector2D(32, 32);

	//レイヤー設定
	z_layer = 4;

	//可動性の設定
	is_mobility = false;

	//オブジェクトのタイプ設定
	item_type = eCoin;

	//アイテムが出てきた時の音を流す
	PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);
}

void OneUpMush::Update(float delta_seconde)
{
	//ハコから出てくる処理
	ItemPush();

	//移動処理
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