#include "Pipeenter.h"
#include "DxLib.h"

void Pipeenter::Initialize()
{
	collision.object_type = ePipeEnter;
	//collision.hit_object_type.push_back(ePlayer);
	collision.box_size = Vector2D(48, 16);
	 
	is_mobility = false;
	 
	z_layer = 5;

	hit_flag = false;
}

void Pipeenter::Update(float delta_seconde)
{
	
}

void Pipeenter::Draw(const Vector2D& screen_offset) const
{
	Vector2D ul = location - (collision.box_size / 2);
	Vector2D br = location + (collision.box_size / 2);
	DrawBoxAA(ul.x - screen_offset.x, ul.y, br.x - screen_offset.x, br.y, GetColor(255, 0, 0), FALSE);
}

void Pipeenter::Finalize()
{

}

void Pipeenter::OnHitCollision(GameObject* hit_object)
{
	//Vector2D diff = 0.0f;
	//Vector2D target_boxsize, this_boxsize;
	//Vector2D target_location = hit_object->GetLocation();

	////2点間の距離を求める
	//diff = this->location - target_location;

	//if (diff.y < 0)
	//{
	//	//当たったオブジェクトがマリオなら
	//	if (hit_object->GetCollision().object_type == ePlayer)
	//	{
	//		//マリオの状態がちび状態かどうか
	//		if (hit_object->GetCollision().box_size.y > 32)		//それ以外ならブロックを破壊する
	//		{
	//		
	//		}
	//		else     //ちび状態ならブロックが少し上に上がる処理
	//		{
	//		
	//		}

	//	}

	//}
}

const Vector2D& Pipeenter::GetLocation() const
{
	return location;
}

const Collision& Pipeenter::GetCollision() const
{
	return collision;
}

const unsigned char Pipeenter::GetZLayer() const
{
	return z_layer;
}

const bool Pipeenter::GetMobility() const
{
	return is_mobility;
}