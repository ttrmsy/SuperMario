#include "FireBall.h"
#include "../../Utility/ResourceManager.h"
#include "../GameObjectManager.h"

#define SPEED (40)
#define D_GRAVITY (9.807f)		//重力加速度

void FireBall::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	//ファイアボールの画像読み込み
	fire_image = rm->GetImageResource("Resource/Images/Mario/fireball.png", 1, 1, 1, 32, 32);
	blast_image = rm->GetImageResource("Resource/Images/bakuha.png", 3, 3, 1, 32, 32);

	//初期画像設定
	image = fire_image[0];
	//オブジェクトタイプ設定
	collision.object_type = eFireBall;
	//当たり判定設定
	collision.box_size = Vector2D(22, 22);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::ePipe);

	//重力
	g_velocity = 0.0f;

	//移動量初期化
	velocity.x = 0;

	//可動性の初期設定
	is_mobility = true;

	//回転量の初期設定
	radian = 60;

	//削除フラグの初期設定
	delete_flag = false;

	//ヒット判定の初期設定
	hit_flag = false;
}

void FireBall::Update(float delta_seconde)
{
	if (delete_flag == true)	//削除判定フラグがtrueなら削除する処理
	{
		player->Set_FireCount(-1);	//削除する際にplayer側のファイアボールを出せる数を変更する
		this->Finalize();
	}

	if (delete_flag == false && hit_flag == false)
	{
		if (filp_flag == true)
		{
			velocity.x = -20;
		}
		else
		{
			velocity.x = 20;
		}

		//重力加算処理
		g_velocity += D_GRAVITY * delta_seconde;
		velocity.y += g_velocity;

		//回転量加算処理
		radian += radian * delta_seconde;

		//移動処理
		Movement(delta_seconde);

		if (camera != nullptr)	//ファイアボールが画面外にあると削除する処理
		{
			float x = camera->Get_CameraLocation().x;
			if (x + D_WIN_MAX_X / 2 <= this->location.x || x - D_WIN_MAX_X / 2 >= this->location.x)
			{
				delete_flag = true;
			}
		}
	}
	else if (hit_flag == true)	//オブジェクトに当たるとアニメーションをする処理
	{
		AnimationControl(delta_seconde);
	}
	
	
}

void FireBall::Draw(const Vector2D& screen_offset) const
{
	Vector2D graph_location = this->location - screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, radian, image, TRUE, filp_flag);
}

void FireBall::Finalize()
{
	GameObjectManager* objm = GameObjectManager::GetInstance();
	objm->DestroyGameObject(this);
	fire_image.clear();
}

void FireBall::OnHitCollision(GameObject* hit_object)
{
	//地面に当たると跳ねる処理
	if (hit_object->GetCollision().object_type == eGround)
	{
		g_velocity = 0.0f;
		velocity.y = 0;
		velocity.y = -13;
	}

	//オブジェクト(Block,Pipe)に当たるとhit_flagをtrueにする
	if (hit_object->GetCollision().object_type == eBlock
		|| hit_object->GetCollision().object_type == ePipe)
	{
		velocity = 0;
		hit_flag = true;
	}
}

void FireBall::Movement(float delta_seconde)
{
	location += velocity * SPEED * delta_seconde;
}

void FireBall::Set_Filpflag(bool flag)
{
	filp_flag = flag;
}

bool FireBall::Get_DeleteFlag()
{
	return delete_flag;
}

void FireBall::Set_Camera(Camera* c)
{
	camera = c;
}

void FireBall::Set_Player(Player* p)
{
	player = p;
}

void FireBall::AnimationControl(float delta_seconde)
{
	animation_time += delta_seconde;

	if (animation_time >= (1.0f / 32.0f))
	{
		animation_time = 0.0f;

		image = blast_image[animation_count];

		animation_count++;

		if (animation_count > 2)	//animation_countが2より大きくなると削除フラグをtrueにする
		{
			animation_count = 0;
			delete_flag = true;
		}

	}
}