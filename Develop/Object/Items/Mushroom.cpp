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
	collision.item_type = eMushroom;		//オブジェクトのタイプ設定
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.box_size = Vector2D(8, 8);		//出ている最中はコリジョンを小さくする

	//レイヤー設定
	z_layer = 4;

	//可動性の設定
	is_mobility = true;

	is_ground = true;

	//アイテムが出てきた時の音を流す
	PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);
}

//更新処理
void Mushroom::Update(float delta_seconde)
{
	//ハコから出てくる処理
	ItemPush();

	//ボックスからでたら当たり判定を通常にする
	if (box_out == true)
	{
		collision.box_size = Vector2D(32, 32);
	}

	if (hit_flag == false)
	{
		is_ground = false;
	}	

	//移動処理
	Movement(delta_seconde);

	hit_flag = false;
}

//描画処理
void Mushroom::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

	Vector2D ul = location - (collision.box_size / 2);
	Vector2D br = location + (collision.box_size / 2);
	DrawBoxAA(ul.x - screen_offset.x, ul.y, br.x - screen_offset.x, br.y, GetColor(255, 0, 0), FALSE);
	DrawFormatString(10, 150, 0xffffff, "%f", this->location.y, TRUE);
}

void Mushroom::Finalize()
{

}