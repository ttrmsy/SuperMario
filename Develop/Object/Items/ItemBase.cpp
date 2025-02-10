#include "ItemBase.h"
#include "../GameObjectManager.h"
#include "../../Utility/ResourceManager.h"

#define ITEM_SPEED		(2.0f)			//アイテムのスピード
#define DEFAULT_SPEED	(50.0f)			//基礎スピード

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

//移動処理
void ItemBase::Movement(float delta_seconde)
{
	//地面にいないかつハコから出ているときに重力を設定する
	if (is_ground == false && box_out == true)
	{
		this->velocity.y += 1.0f;
		g_velocity += D_GRAVITY / 444.0f;
		this->velocity.y += g_velocity;
	}
	else if(is_ground == true && box_out == true)		//地面に触れていてハコから出ているとき
	{
		//アイテムがスター以外の場合
		if (item_type != eStar)
		{
			this->velocity.y = 0;
			g_velocity = 0.0f;
		}
		else      //スターの場合は跳ねるようにする
		{
			g_velocity = 0.0f;
			//this->velocity.y = 0.0f;
		}
	}

	//移動の実行
	this->location += this->velocity * DEFAULT_SPEED * delta_seconde;
}

//当たり判定処理
void ItemBase::OnHitCollision(GameObject* hit_object)
{
	if (box_out == true)
	{
		hit_flag = true;

		Vector2D diff; //dv;
		Vector2D target_boxsize, this_boxsize;
		diff = 0.0f;
		Vector2D dv = 0.0f;
		Vector2D target_location = hit_object->GetLocation();
		Collision target_collision = hit_object->GetCollision();

		target_boxsize = hit_object->GetCollision().box_size;
		this_boxsize = this->collision.box_size;


		//2点間の距離を求める
		diff = this->location - target_location;

		if (diff.x >= 0)	//自身がHitしたオブジェクトよりも右側にいたとき
		{
			if (diff.y > 0)	//自身がHitしたオブジェクトよりも下側にいたとき
			{
				dv.x = (target_location.x + target_boxsize.x / 2) - (this->location.x - this_boxsize.x / 2);
				dv.y = (target_location.y + target_boxsize.y / 2) - (this->location.y - this_boxsize.y / 2);

				if (dv.x > dv.y)
				{
					this->location.y += dv.y;
					velocity.y = 0;
				}
				else
				{
					this->location.x += dv.x;
					this->velocity.x = ITEM_SPEED;
					/*if (target_collision.object_type == eEnemy)
					{
						state = die;
					}*/
				}



			}
			else	//自身がHitしたオブジェクトよりも上側にいたとき
			{
				dv.x = (target_location.x + target_boxsize.x / 2) - (this->location.x - this_boxsize.x / 2);
				dv.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);

				if (dv.x > dv.y)
				{
					if (target_collision.object_type != eEnemy)
					{
						this->location.y += -dv.y;

						if (target_collision.object_type == eGround || target_collision.object_type == eBlock)
						{
							if (hit_object->GetMobility() == true && box_out == true)
							{
								is_ground = false;					//地面の接触フラグをfalseにする
								this->velocity.y = -15.0f;			//ジャンプ力の設定
								this->velocity.x = ITEM_SPEED;		//移動方向を反対にする
								g_velocity = 0;
							}
							else if(hit_object->GetMobility() == false && box_out == true)
							{
								is_ground = true;
								g_velocity = 0;
							}
						}



					}
					else
					{
						/*if (hit_object->GetMobility() == true)
						{
							velocity.y = 0;
							velocity.y += -20.0;
						}*/
					}

				}
				else
				{
					this->location.x += dv.x;
					this->velocity.x = ITEM_SPEED;
				}
			}
		}
		else	//自身がHitしたオブジェクトよりも左側にいたとき
		{
			if (diff.y > 0)	//自身がHitしたオブジェクトよりも下側にいたとき
			{
				dv.x = (this->location.x + this_boxsize.x / 2) - (target_location.x - target_boxsize.x / 2);
				dv.y = (target_location.y + target_boxsize.y / 2) - (this->location.y - this_boxsize.y / 2);

				if (dv.x < dv.y)
				{
					this->location.x += -dv.x;
					this->velocity.x = -ITEM_SPEED;
				}
				else
				{
					this->location.y += dv.y;
					velocity.y = 0;
				}


			}
			else	//自身がHitしたオブジェクトよりも上側にいたとき
			{
				dv.x = (this->location.x + this_boxsize.x / 2) - (target_location.x - target_boxsize.x / 2);
				dv.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);

				if (dv.x > dv.y)
				{
					if (target_collision.object_type != eEnemy)
					{
						this->location.y += -dv.y;


						if (target_collision.object_type == eGround || target_collision.object_type == eBlock)
						{
							//当たっているオブジェクトがブロックで当たったブロックが可動だったら
							if (hit_object->GetMobility() == true && box_out == true)
							{
								is_ground = false;					//地面の接触フラグをfalseにする
								this->velocity.y = -15.0f;			//ジャンプ力の設定
								this->velocity.x = -ITEM_SPEED;		//移動方向を反対にする
								g_velocity = 0;						//重力加速度を0にする
							}
							else if (hit_object->GetMobility() == false && box_out == true)
							{
								is_ground = true;
								g_velocity = 0;
							}
						}

						//// 当たったオブジェクトがプレイヤーだったら、削除する
						//if (hit_object->GetCollision().object_type == eObjectType::eBlock && hit_object->GetMobility() == true)
						//{
						//	//
						//	this->velocity.y = -30.0f;
						//}


					}
					else
					{
						/*if (hit_object->GetMobility() == true)
						{
							velocity.y = 0;
							velocity.y += -20.0;
						}*/
					}

				}
				else
				{
					this->location.x += -dv.x;
					this->velocity.x = -ITEM_SPEED;		//反対側に移動する
					/*if (target_collision.object_type == eEnemy)
					{
						state = die;
					}*/
				}
			}
		}
	}

	// 当たったオブジェクトがプレイヤーだったら、削除する
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer && box_out == true)
	{
		//ゲームオブジェクトのポインタを取得
		GameObjectManager* gm_p = GameObjectManager::GetInstance();

		//PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);

		//自身を削除リストに追加
		gm_p->DestroyGameObject(this);
	}

	
}

//ボックスから出てくる処理
void ItemBase::ItemPush()
{
	//ボックスから出ているかどうか
	if (box_out == false)
	{
		//アイテム別の処理
		switch (item_type)
		{
		case eNull:
			break;
		case eCoin:
				//コインだった場合
				if (this->location.y > old_loction.y - ((32.0f * 3) - 5.0f))
				{
					location.y -= ITEM_SPEED;

					velocity = 0.0f;

					box_out = false;

					return;
				}

				break;
		case eMushroom:
		case eFlower:
		case eOneup:
		case eStar:
				//ハコから出るまで上に行き続ける
				if (this->location.y > old_loction.y - 27.0f)
				{
					location.y -= 0.5f;

					velocity = 0.0f;

					box_out = false;

					return;
				}

				if (item_type != eFlower)
				{
					//ボックスからでたら右方向に進むようにする
					this->velocity.x = 2.0f;
				}

				break;
		default:
			break;
		}

		//ボックスから出た状態にする
		box_out = true;
	}

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