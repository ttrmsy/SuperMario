#include "ItemBase.h"
#include "../GameObjectManager.h"
#include "../../Utility/ResourceManager.h"

#define ITEM_SPEED		(2.0f)			//�A�C�e���̃X�s�[�h
#define DEFAULT_SPEED	(50.0f)			//��b�X�s�[�h

ItemBase::ItemBase() : animation_count(0.0f),
animation_time(0.0f),
item_type(eNull),
box_out(false),
item_sound(NULL)
{
	//���\�[�X�}�l�[�W���[�̃C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();
	item_sound = rm->GetSoundResource("Resource/Sounds/SE_ItemAppearance.wav");	//�A�C�e�����o�Ă������̉�
}

ItemBase::~ItemBase()
{

}

void ItemBase::Movement(float delta_seconde)
{
	//�n�ʂɂ��Ȃ����n�R����o�Ă���Ƃ��ɏd�͂�ݒ肷��
	if (is_ground == false && box_out == true)
	{
		g_velocity += D_GRAVITY / 444.0f;
		this->velocity.y += g_velocity;
	}
	else
	{
		this->velocity.y = 0;
		g_velocity = 0.0f;
	}

	//�ړ��̎��s
	this->location += this->velocity * DEFAULT_SPEED * delta_seconde;
}

//�����蔻�菈��
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


		//2�_�Ԃ̋��������߂�
		diff = this->location - target_location;

		if (diff.x >= 0)	//���g��Hit�����I�u�W�F�N�g�����E���ɂ����Ƃ�
		{
			if (diff.y > 0)	//���g��Hit�����I�u�W�F�N�g���������ɂ����Ƃ�
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
			else	//���g��Hit�����I�u�W�F�N�g�����㑤�ɂ����Ƃ�
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
							is_ground = true;
							g_velocity = 0;
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
		else	//���g��Hit�����I�u�W�F�N�g���������ɂ����Ƃ�
		{
			if (diff.y > 0)	//���g��Hit�����I�u�W�F�N�g���������ɂ����Ƃ�
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
			else	//���g��Hit�����I�u�W�F�N�g�����㑤�ɂ����Ƃ�
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
							is_ground = true;
							g_velocity = 0;
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
					this->location.x += -dv.x;
					this->velocity.x = -ITEM_SPEED;
					/*if (target_collision.object_type == eEnemy)
					{
						state = die;
					}*/
				}
			}
		}
	}

	// ���������I�u�W�F�N�g���v���C���[��������A�폜����
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer && box_out == true)
	{
		//�Q�[���I�u�W�F�N�g�̃|�C���^���擾
		GameObjectManager* gm_p = GameObjectManager::GetInstance();

		//PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);

		//���g���폜���X�g�ɒǉ�
		gm_p->DestroyGameObject(this);
	}
}

//�{�b�N�X����o�Ă��鏈��
void ItemBase::ItemPush()
{
	//�{�b�N�X����o�Ă��邩�ǂ���
	if (box_out == false)
	{
		switch (item_type)
		{
		case eNull:
			break;
		case eCoin:
				//�R�C���������ꍇ
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
				//�n�R����o��܂ŏ�ɍs��������
				if (this->location.y > old_loction.y - 27.0f)
				{
					location.y -= 0.5f;

					velocity = 0.0f;

					box_out = false;

					return;
				}

				if (item_type != eFlower)
				{
					//�{�b�N�X����ł���E�����ɐi�ނ悤�ɂ���
					this->velocity.x = 2.0f;
				}

				break;
		default:
			break;
		}

		//�{�b�N�X����o����Ԃɂ���
		box_out = true;
	}

}

//���˂鏈��
void ItemBase::Bounce()
{
	/*if (this->location.y < this->location.y - 32.0f)
	{
		location.y--;
	}*/
}

//�^�C�v�擾����
Items ItemBase::GetItemType()
{
	return this->item_type;
}

//�������̍��W�ۑ�
void ItemBase::SetOldLocation(Vector2D a)
{
	this->old_loction = a;
}