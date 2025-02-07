#include "Star.h"
#include "../../Utility/ResourceManager.h"

#define STAR_JUMP	(30.0f)			//スターのジャンプ力

Star::Star()
{

}

Star::~Star()
{

}

void Star::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImageResource("Resource/Images/Item/star.png", 4, 4, 1, 32, 32);

	collision.is_blocking = true;
	collision.object_type = eItem;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.box_size = Vector2D(32, 32);

	//レイヤー設定
	z_layer = 4;

	//可動性の設定
	is_mobility = true;

	is_ground = true;

	//オブジェクトのタイプ設定
	item_type = eStar;

	//アイテムが出てきた時の音を流す
	PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);
}

//更新処理
void Star::Update(float delta_seconde)
{
	//ハコから出てくる処理
	ItemPush();

	//オブジェクトに当たっていなければ地面に当たっていない判定にする
	if (hit_flag == false)
	{
		is_ground = false;
	}

	//地面に触れていたら跳ねる
	if (is_ground == true)
	{
		this->velocity.y = -STAR_JUMP;
	}

	//移動処理
	Movement(delta_seconde);

	//animation処理
	AnimationControl(delta_seconde);

	//当たり判定をfalseにする
	hit_flag = false;
}

//描画処理
void Star::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Star::Finalize()
{

}

//アニメーション処理
void Star::AnimationControl(float delta_seconde)
{
	animation_time += delta_seconde;

	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;

		image = move_animation[animation_count];

		animation_count++;

		if (animation_count > 3)
		{
			animation_count = 0;
		}

	}
}