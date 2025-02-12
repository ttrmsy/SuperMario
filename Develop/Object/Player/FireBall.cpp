#include "FireBall.h"
#include "../../Utility/ResourceManager.h"
#include "../GameObjectManager.h"

#define SPEED (40)
#define D_GRAVITY (9.807f)		//�d�͉����x

void FireBall::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	//�t�@�C�A�{�[���̉摜�ǂݍ���
	fire_image = rm->GetImageResource("Resource/Images/Mario/fireball.png", 1, 1, 1, 32, 32);
	blast_image = rm->GetImageResource("Resource/Images/bakuha.png", 3, 3, 1, 32, 32);

	//�����摜�ݒ�
	image = fire_image[0];
	//�I�u�W�F�N�g�^�C�v�ݒ�
	collision.object_type = eFireBall;
	//�����蔻��ݒ�
	collision.box_size = Vector2D(22, 22);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::ePipe);

	//�d��
	g_velocity = 0.0f;

	//�ړ��ʏ�����
	velocity.x = 0;

	//�����̏����ݒ�
	is_mobility = true;

	//��]�ʂ̏����ݒ�
	radian = 60;

	//�폜�t���O�̏����ݒ�
	delete_flag = false;

	//�q�b�g����̏����ݒ�
	hit_flag = false;
}

void FireBall::Update(float delta_seconde)
{
	if (delete_flag == true)	//�폜����t���O��true�Ȃ�폜���鏈��
	{
		player->Set_FireCount(-1);	//�폜����ۂ�player���̃t�@�C�A�{�[�����o���鐔��ύX����
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

		//�d�͉��Z����
		g_velocity += D_GRAVITY * delta_seconde;
		velocity.y += g_velocity;

		//��]�ʉ��Z����
		radian += radian * delta_seconde;

		//�ړ�����
		Movement(delta_seconde);

		if (camera != nullptr)	//�t�@�C�A�{�[������ʊO�ɂ���ƍ폜���鏈��
		{
			float x = camera->Get_CameraLocation().x;
			if (x + D_WIN_MAX_X / 2 <= this->location.x || x - D_WIN_MAX_X / 2 >= this->location.x)
			{
				delete_flag = true;
			}
		}
	}
	else if (hit_flag == true)	//�I�u�W�F�N�g�ɓ�����ƃA�j���[�V���������鏈��
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
	//�n�ʂɓ�����ƒ��˂鏈��
	if (hit_object->GetCollision().object_type == eGround)
	{
		g_velocity = 0.0f;
		velocity.y = 0;
		velocity.y = -13;
	}

	//�I�u�W�F�N�g(Block,Pipe)�ɓ������hit_flag��true�ɂ���
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

		if (animation_count > 2)	//animation_count��2���傫���Ȃ�ƍ폜�t���O��true�ɂ���
		{
			animation_count = 0;
			delete_flag = true;
		}

	}
}