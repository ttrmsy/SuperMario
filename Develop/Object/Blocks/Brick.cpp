#include "Brick.h"
#include "DxLib.h"

#define MAX_COUNT	(8)		//ボックス上昇・下降する上限カウント

void Brick::Initialize()
{
	collision.object_type = eBlock;
	collision.hit_object_type.push_back(ePlayer);
	collision.hit_object_type.push_back(eEnemy);
	collision.hit_object_type.push_back(eItem);
	collision.box_size = Vector2D(32, 32);

	image = LoadGraph("Resource/Images/Block/block.png");

	is_mobility = false;

	z_layer = 5;

	up_count = 0;

	down_count = 0;

	now_bouce = false;

	hit_flag = false;

}

void Brick::Update(float delta_seconde)
{
	//マリオが下から触れたら上に少し上がる処理
	if (hit_flag == true)
	{
		if (up_count < MAX_COUNT)
		{
			this->location.y += -1;

			if (up_count > 3)
			{
				is_mobility = false;
			}

			up_count++;
		}
		else if (down_count < MAX_COUNT)
		{
			this->location.y += 1;
			down_count++;
		}
		else
		{
			//火っと判定とup/downカウントの初期化
			hit_flag = false;
			up_count = 0;
			down_count = 0;
		}
	}

	//アニメーション処理
	AnimationControl(delta_seconde);
}

void Brick::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

	Vector2D ul = location - (collision.box_size / 2);
	Vector2D br = location + (collision.box_size / 2);
	DrawBoxAA(ul.x - screen_offset.x, ul.y, br.x - screen_offset.x, br.y, GetColor(255, 0, 0), FALSE);
	DrawFormatString(100, 30, 0xffffff, "%f", this->location.y, TRUE);
}

void Brick::Finalize()
{

}

void Brick::OnHitCollision(GameObject* hit_object)
{
	Vector2D diff = 0.0f;
	Vector2D target_boxsize, this_boxsize;
	Vector2D target_location = hit_object->GetLocation();

	//2点間の距離を求める
	diff = this->location - target_location;

	if (diff.y < 0)
	{
		if (hit_object->GetCollision().object_type == ePlayer)
		{
			//soundを再生
			PlaySoundMem(block_sound, DX_PLAYTYPE_BACK);

			//ヒットフラグをtrueにする
			hit_flag = true;

			Vector2D lc_handover = location;

			lc_handover.y -= 5.0f;

			PlaySound("Resource/Sounds/SE_Block.wav", DX_PLAYTYPE_BACK);
			hit_flag = true;
			is_mobility = true;
		}
	}

}

const Vector2D& Brick::GetLocation() const
{
	return location;
}

const Collision& Brick::GetCollision() const
{
	return collision;
}

const unsigned char Brick::GetZLayer() const
{
	return z_layer;
}

const bool Brick::GetMobility() const
{
	return is_mobility;
}

void Brick::AnimationControl(float delta_seconde)
{

}
