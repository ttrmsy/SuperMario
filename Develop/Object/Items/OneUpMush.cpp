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

	collision.is_blocking = true;
	collision.object_type = eItem;
	collision.item_type = eOneup;		//オブジェクトのタイプ設定
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.box_size = Vector2D(8, 8);

	//レイヤー設定
	z_layer = 4;

	//可動性の設定
	is_mobility = true;

	is_ground = true;



	//アイテムが出てきた時の音を流す
	PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);
}

void OneUpMush::Update(float delta_seconde)
{
	//ハコから出てくる処理
	ItemPush();

	if (hit_flag == false)
	{
		is_ground = false;
	}

	//ボックスからでたら当たり判定を通常にする
	if (box_out == true)
	{
		collision.box_size = Vector2D(32, 32);
	}

	//移動処理
	Movement(delta_seconde);

	hit_flag = false;
}

void OneUpMush::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

//void OneUpMush::Finalize()
//{
//
//}