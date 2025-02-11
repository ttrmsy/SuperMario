#include "Player.h"
#include "../../Utility/ResourceManager.h"
#include "PlayerState/PlayerStateFactory.h"
#include "../../Utility/Application.h"
#include "DxLib.h"
#include "../GameObjectManager.h"
#include "../../Utility/InputManager.h"
#include "../GameObjectManager.h"
#include "FireBall.h"


#define D_GRAVITY (9.807f)		//重力加速度
#define P_SPEED (50.0f)

void Player::Initialize()
{
	player_state = PlayerStateFactory::Get((*this), ePlayerState::idle);
	next_state = none;
	p_level = Big;


	ResourceManager* rm = ResourceManager::GetInstance();
	SmallMario_animation = rm->GetImageResource("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	BigMario_animation = rm->GetImageResource("Resource/Images/Mario/dekamario.png", 10, 10, 1, 32, 64);
	FireMario_animation = rm->GetImageResource("Resource/Images/Mario/faiyamario.png", 9, 9, 1, 32, 64);
	levelup_animation = rm->GetImageResource("Resource/Images/Mario/dekamarimation.png", 3, 3, 1, 32, 64);
	collision.is_blocking = true;
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.hit_object_type.push_back(eObjectType::eItem);
	collision.box_size = Vector2D(32,64);

	//レイヤー設定
	z_layer = 5;

	//可動性の設定
	is_mobility = true;

	image = SmallMario_animation[0];	//アニメーション画像の設定
	animation_time = 0;			//アニメーションの時間
	move_animation_count = 0;	//移動アニメーションカウントの初期化
	move_animation_number = 0;	//移動アニメーション時の画像配列の添え字初期化

	level_animation_count = 0;	//レベル変更(up/down)時のアニメーションカウントの初期化
	level_animation_number = 0;	//レベル変更(up/down)時のアニメーション画像配列の添え字初期化

	//画像反転フラグの設定
	filp_flag = FALSE;	

	//地面に着地しているか判定フラグの設定
	is_ground = false;

	//ジャンプできる状態かの判定フラグ
	jump_flag = true;

	/*
	 オブジェクトにヒットしている = true
	オブジェクトにヒットしていない = false
	*/
	hit_flag = true;

	//横スクロール用カメラのポインタ
	camera = nullptr;

	//スライド（ブレーキ）フラグ
	slide_flag = false;

	state = live;

	fire_count = 0;

	change_flag = false;

}

void Player::Update(float delta_seconde)
{
	//ePlayerState p_state;
	slide_flag = false;

	if (p_state != get && p_state != damage)
	{
		if (next_state != ePlayerState::none)
		{
			player_state = PlayerStateFactory::Get((*this), next_state);
			next_state = ePlayerState::none;
		}

		p_state = GetPlayerState();
	}

	GameObjectManager* objm = GameObjectManager::GetInstance();

	InputManager* input = InputManager::GetInstance();

	/*if (input->GetKeyState(KEY_INPUT_Z) == eInputState::Pressed || input->GetKeyState(KEY_INPUT_Z) == eInputState::Held)
	{
		p_state = none;
	}*/


	//プレイヤーの状態で、処理を変える
	if (state == live)
	{
		switch (p_state)
		{
		case ePlayerState::idle:
			player_state->Update(delta_seconde);
			AnimationControl(delta_seconde);
			break;

		case ePlayerState::walk:
			/*player_state->Initialize();*/
			player_state->Update(delta_seconde);
			AnimationControl(delta_seconde);
			break;

		case ePlayerState::jump:
			player_state->Update(delta_seconde);
			AnimationControl(delta_seconde);
			break;

		case ePlayerState::get:
			velocity = 0;
			GetItem_Animation(delta_seconde);
			/*image = levelup_animation[2];*/
			break;

		case ePlayerState::damage:
			velocity = 0;
			PowerDown_Animation(delta_seconde);
			break;

		default:
			break;
		}
	}
	/*else if(state == die)
	{
		image = move_animation[6];
	}*/
	
	if (fire_count < 2)
	{
		if (input->GetKeyState(KEY_INPUT_LCONTROL) == eInputState::Pressed)
		{
			image = FireMario_animation[2];
			FireBall* fire = nullptr;
			fire = objm->CreateGameObject<FireBall>(this->location);
			fire->Set_Player(this);
			fire->Set_Filpflag(this->filp_flag);
			fire->Set_Camera(camera);
			fire_count++;
		}
	}

	//if (input->GetKeyState(KEY_INPUT_Z) == eInputState::Held)
	//{
	//	/*GetItem_Animation(delta_seconde);*/
	//	PowerDown_Animation(delta_seconde);
	//}

	//マリオが
	if (is_ground == false /*&& p_state != get */&& p_state == jump)
	{
		g_velocity += (D_GRAVITY / 444);
		velocity.y += g_velocity;
	}
	else if(is_ground == true)
	{
		velocity.y = 0;
	}

	if (change_flag == true)
	{
		change_flag = false;
		this->location.y += 16;
		image = SmallMario_animation[0];
	}
	
	//マリオがどのオブジェクトにも触れていないときの重力処理
	if (hit_flag == false && p_state != jump && p_state != get && p_state != damage && change_flag == false)
	{
		is_ground = false;
		velocity.y = D_GRAVITY;
		jump_flag = false;
	}
	
	
	//マリオが画面外に行かないようにする処理
	if (camera != nullptr)
	{
		float x = camera->Get_CameraLocation().x;
		if (this->location.x - OBJECT_SIZE / 2 < x - D_WIN_MAX_X / 2)
		{
			if (velocity.x < 1.0e-6f)
			{
				velocity.x = 0;
			}
		}
	}

	hit_flag = false;
	
	Movement(delta_seconde);
	
	DeathCount();
}

void Player::Draw(const Vector2D& screen_offset) const
{
	//親クラスの処理を呼び出す
	__super::Draw(screen_offset);

	SetFontSize(15);
	DrawFormatString(100, 100, GetColor(255, 0, 0), "Vx:%f0,Vy:%f0", velocity.x, velocity.y);
	DrawFormatString(100, 150, GetColor(255, 0, 0), "is_ground:%d", hit_flag);
	Vector2D ul = location - (collision.box_size / 2);
	Vector2D br = location + (collision.box_size / 2);
	DrawBoxAA(ul.x - screen_offset.x, ul.y, br.x - screen_offset.x, br.y, GetColor(255, 0, 0), FALSE);
	DrawCircle(this->location.x - screen_offset.x, this->location.y, 3, GetColor(255, 0, 0));
	DrawFormatString(10, 30, 0xffffff, "%f", this->location.y, TRUE);
	DrawFormatString(10, 10, 0xffffff, "%d", is_death, TRUE);
}

void Player::Finalize()
{
	SmallMario_animation.clear();
	BigMario_animation.clear();
	FireMario_animation.clear();
}

void Player::OnHitCollision(GameObject* hit_object)
{
	hit_flag = true;

	Vector2D diff; //dv;
	Vector2D target_boxsize, this_boxsize;
	diff = 0.0f;
	Vector2D target_location = hit_object->GetLocation();
	Collision target_collision = hit_object->GetCollision();

	target_boxsize = hit_object->GetCollision().box_size;
	this_boxsize = this->collision.box_size;
	

	//2点間の距離を求める
	diff = this->location - target_location;
	
	if (diff.x >= 0)	//自身がHitしたオブジェクトよりも右側にいたとき
	{
		if (diff.y >= 0)	//自身がHitしたオブジェクトよりも下側にいたとき
		{
      		diff.x = (target_location.x + target_boxsize.x / 2) - (this->location.x - this_boxsize.x / 2);
			diff.y = (target_location.y + target_boxsize.y / 2) - (this->location.y - this_boxsize.y / 2);
			
			if (diff.x > diff.y)
			{
				this->location.y += diff.y;
				if (target_collision.object_type == eBlock)
				{
					velocity.y = 0;
				}

			}
			else
			{
				this->location.x += diff.x;
			}
			
			
	
		}
		else	//自身がHitしたオブジェクトよりも上側にいたとき
		{
			diff.x = (target_location.x + target_boxsize.x / 2) - (this->location.x - this_boxsize.x / 2);
			diff.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);

			if (diff.x > diff.y)
			{
				if (target_collision.object_type != eEnemy)
				{
					this->location.y += -diff.y;
					
					if (target_collision.object_type == eGround)
					{
						if (velocity.y > 0)
						{
							is_ground = true;
							jump_flag = true;
						}
						g_velocity = 0;
					}

					if (target_collision.object_type == eBlock
						|| target_collision.object_type == ePipe
						|| target_collision.object_type == eHardBlock)
					{

						/*if (diff.y < 0.1)
						{*/
							if (/*velocity.y != D_GRAVITY &&*/ velocity.y > 0)
							{
								is_ground = true;
								jump_flag = true;

							}
							g_velocity = 0;
						/*}*/
					}

					
				}
				else
				{
					if (hit_object->GetMobility() == true)
					{
						velocity.y = 0;
						velocity.y += -20.0;
					}
				}
			
			}
			else
			{
				this->location.x += diff.x;
			}
		}
	}
	else	//自身がHitしたオブジェクトよりも左側にいたとき
	{
		if (diff.y >= 0)	//自身がHitしたオブジェクトよりも下側にいたとき
		{
			diff.x = (this->location.x + this_boxsize.x / 2) - (target_location.x - target_boxsize.x / 2);
			diff.y = (target_location.y + target_boxsize.y / 2) - (this->location.y - this_boxsize.y / 2);

			if (diff.x <= diff.y)
			{
				this->location.x += -diff.x;
			}
			else
			{
				this->location.y += diff.y;
				if (target_collision.object_type == eBlock)
				{
  					velocity.y = 0;
				}
			}

			/*if (target_collision.object_type == eEnemy)
			{
				p_state = damage;
				p_level = Small;
			}*/
			
		}
		else	//自身がHitしたオブジェクトよりも上側にいたとき
		{
			diff.x = (this->location.x + this_boxsize.x / 2) - (target_location.x - target_boxsize.x / 2);
			diff.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);

			if (diff.x > diff.y)
			{
				if (target_collision.object_type != eEnemy)
				{
					this->location.y += -diff.y;

					
					if (target_collision.object_type == eGround)
					{
						/*if (velocity.y > 0)
						{
						*/	is_ground = true;
							jump_flag = true;
						/*}*/
						g_velocity = 0;
					}

					if (target_collision.object_type == eBlock
						|| target_collision.object_type == ePipe
						|| target_collision.object_type == eHardBlock)
					{

						//if (diff.y < 0.1)
						//{
							if (/*velocity.y != D_GRAVITY &&*/ velocity.y > 0)
							{

								is_ground = true;
								jump_flag = true;
							}
						/*}*/
						g_velocity = 0;
					}

				}
				else
				{
					if (hit_object->GetMobility() == true)
					{
						velocity.y = 0;
						velocity.y += -20.0;
					}
				}
					
			}
			else
			{
				this->location.x += -diff.x;
				/*if (target_collision.object_type == eEnemy)
				{
					p_state = damage;
				}*/
			}

		}
	}

	if (target_collision.object_type == eItem)
	{
		p_state = get;
	}

	/*if (target_collision.object_type == eEnemy)
	{
		p_state = damage;
		p_level = Small;
	}*/
}


const Collision& Player::GetCollision() const
{
	return collision;
}

const unsigned char Player:: GetZLayer() const
{
	return z_layer;
}

const bool Player:: GetMobility() const
{
	return is_mobility;
}

ePlayerState Player::GetPlayerState() const
{
	return player_state->GetState();
}

void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}

void Player::SetFilp_flag(bool flag)
{
	filp_flag = flag;
}

bool Player::GetFilp_flag()
{
	return filp_flag;
}

Vector2D Player::Get_Velocity()
{
	return this->velocity;
}

void Player::Set_Velocity(Vector2D velocity)
{
	this->velocity = velocity;
}

void Player::Set_IsGround(bool flag)
{
	is_ground = flag;
}

void Player::Set_Camera(Camera* c)
{
	camera = c;
}

void Player::Set_SlideFlag(bool flag)
{
	slide_flag = flag;
}

void Player::Movement(float delta_second)
{
	location += velocity * P_SPEED * delta_second;
}

void Player::Set_FireCount(int count)
{
	fire_count += count;
}

ePlayerLevel Player::Get_PlayerLevel()
{
	return p_level;
}

void Player::AnimationControl(float delta_second)
{
	//移動アニメーション
	animation_time += delta_second;

	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		
		switch (p_level)
		{
		case ePlayerLevel::Small:
			if (p_state == idle)
			{
				image = SmallMario_animation[0];
			}
			else if (p_state == jump)
			{
				image = SmallMario_animation[5];
			}
			 else if (slide_flag == true)
			{
				image = SmallMario_animation[4];
			}
			 else
			{
				image = SmallMario_animation[animation_num[Small][move_animation_count]];
				move_animation_count++;
			}
			break;

		case ePlayerLevel::Big:
			
			if (p_state == idle)
			{
				image = BigMario_animation[0];
			}
			else if (p_state == jump)
			{
				image = BigMario_animation[6];
			}
			else if (slide_flag == true)
			{
				image = BigMario_animation[5];
			}
			else
			{
				image = BigMario_animation[animation_num[1][move_animation_count]];
				move_animation_count++;
			}
			break;

		case ePlayerLevel::Fire:
			
			if (p_state == idle)
			{
				image = FireMario_animation[0];
			}
			else if (p_state == jump)
			{
				image = FireMario_animation[6];
			}
			else if (slide_flag == true)
			{
				image = FireMario_animation[5];
			}
			else
			{
				image = FireMario_animation[animation_num[1][move_animation_count]];
				move_animation_count++;
			}
			break;

		default:
			break;
		}
		
		
		if (move_animation_count >= 3)
		{
			move_animation_count = 0;
		}
		
	}

}

void Player::GetItem_Animation(float delta_seconde)
{
	animation_time += delta_seconde;


	if (animation_time >= (1.0f / 24.0f))
	{
		animation_time = 0.0f;

		
		if (level_animation_number == 0 && level_animation_count == 0)
		{
			this->location.y += -16;
			this->collision.box_size = Vector2D(32, 64);
		}

		if (level_animation_count <= 1)
		{

			image = levelup_animation[animation_num[2][level_animation_number]];
			level_animation_number++;

			
			if (level_animation_number >= 2)
			{
				level_animation_number = 0;
				level_animation_count++;
			}
		}
		else if (level_animation_count <= 2)
		{
			image = levelup_animation[animation_num[3][level_animation_number]];
			level_animation_number++;
			

			if (level_animation_number >= 3)
			{
				level_animation_number = 0;
				level_animation_count++;
			}
		}
		else
		{
			level_animation_number = 0;
			level_animation_count = 0;
			this->location.y += 16;
			p_state = idle;
			p_level = Big;
		}

	}
}

void Player::PowerDown_Animation(float delta_seconde)
{
	animation_time += delta_seconde;

	if (animation_time >= (1.0f / 24.0f))
	{
		animation_time = 0.0f;

		//if (level_animation_number == 0 && level_animation_count == 0)
		//{
		//	this->collision.box_size = Vector2D(32, 32);
		//}

		if (level_animation_count <= 1)
		{
			image = levelup_animation[animation_num[4][level_animation_number]];
			level_animation_number++;

			if (level_animation_number > 1)
			{
				level_animation_number = 0;
				level_animation_count++;
			}
		}
		else if (level_animation_count <= 3)
		{
			image = levelup_animation[animation_num[4][level_animation_number]];
			level_animation_number++;

			if (level_animation_number > 2)
			{
				level_animation_number = 0;
				level_animation_count++;
			}
		}
		else
		{
			level_animation_number = 0;
			level_animation_count = 0;
			this->collision.box_size = Vector2D(32, 32);
			p_state = idle;
			p_level = Small;
			change_flag = true;
		}
	

		

	}
}

void Player::DeathCount()
{
	if (location.y >= 500 && eSceneType::eInGame)
	{
		is_death++;

	}
	else
	{
		is_death = 0;
	}
}

int Player::Get_DeathCount()
{
	return is_death;
}

