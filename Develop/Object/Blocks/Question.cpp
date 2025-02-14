#include "Question.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/Singleton.h"
#include "../Items/Mushroom.h"
#include "../Items/Flower.h"
#include "../Items/OneUpMush.h"
#include "../Items/Coin.h"
#include "../Items/Star.h"
#include "DxLib.h"

#include "../GameObjectManager.h"

void Question::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	block_image = rm->GetImageResource("Resource/Images/Block/hatena.png", 4, 4, 1, 32, 32);
	block_sound = rm->GetSoundResource("Resource/Sounds/SE_Block.wav");
	kara_block = rm->GetImageResource("Resource/Images/Block/kara_block.png")[0];
	collision.object_type = eBlock;
	collision.hit_object_type.push_back(ePlayer);
	collision.hit_object_type.push_back(eEnemy);
	collision.hit_object_type.push_back(eItem);

	collision.box_size = Vector2D(32, 32);

	z_layer = 5;

	is_mobility = false;

	image = block_image[0];

	animation_time = 0.0f;
	
	animation_count = 0;

	up_count = 0;

	down_count = 0;

	hit_flag = false;

	//create_item = eNull;

}

void Question::Update(float delta_seconde)
{
	if (hit_flag == true)
	{
		if (up_count < 8)
		{
			this->location.y += -1;
			up_count++;
		}
		else if (down_count < 8)
		{
			this->location.y += 1;
			down_count++;
		}
	}
	AnimationControl(delta_seconde);
}

void Question::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

	/*Vector2D ul = location - (collision.box_size / 2);
	Vector2D br = location + (collision.box_size / 2);
	DrawBoxAA(ul.x - screen_offset.x, ul.y, br.x - screen_offset.x, br.y, GetColor(255, 0, 0), FALSE);*/
	DrawFormatString(200, 80, 0xffffff, "%f", this->location.y, TRUE);
}

void Question::Finalize()
{

}

//�����蔻�菈��
void Question::OnHitCollision(GameObject* hit_object)
{
	Vector2D diff = 0.0f;
	Vector2D target_boxsize, this_boxsize;
	Vector2D target_location = hit_object->GetLocation();

	//2�_�Ԃ̋��������߂�
	diff = this->location - target_location;

	if (diff.y < 0)
	{
		//���������I�u�W�F�N�g���}���I�ŉ摜����̃u���b�N�ł͂Ȃ���
		if (hit_object->GetCollision().object_type == ePlayer && image != kara_block)
		{
			//�Q�[���I�u�W�F�N�g�̃|�C���^���擾
			GameObjectManager* gm_p = GameObjectManager::GetInstance();

			//sound���Đ�
			PlaySoundMem(block_sound, DX_PLAYTYPE_BACK);

			//�摜����̃u���b�N�ɕύX����
			image = kara_block;

			//�q�b�g�t���O��true�ɂ���
			hit_flag = true;

			//�A�C�e���𐶐�����Ƃ��ɃA�C�e����������͂ݏo��̂�h�����߂Ɉ�x�ϐ��Ɏ����̍��W��ۑ�����
			Vector2D lc_handover = location;

			//�����Ŏ�����y���W��-5.0f�����l�ɂ��Đ�������Ƃ��ɓn��
			lc_handover.y -= 5.0f;

			//�L�m�R�𐶐�����
			switch (create_item)
			{
			case eNull:
				gm_p->CreateGameObject<Coin>(lc_handover)->SetOldLocation(lc_handover);
				break;
			case eCoin:
				gm_p->CreateGameObject<Coin>(lc_handover)->SetOldLocation(lc_handover);
				break;
			case eMushroom:
				gm_p->CreateGameObject<Mushroom>(lc_handover)->SetOldLocation(lc_handover);
				break;
			case eFlower:
				gm_p->CreateGameObject<Flower>(lc_handover)->SetOldLocation(lc_handover);
				break;
			case eOneup:
				gm_p->CreateGameObject<OneUpMush>(lc_handover)->SetOldLocation(lc_handover);
				break;
			case eStar:
				gm_p->CreateGameObject<Star>(lc_handover)->SetOldLocation(lc_handover);
				break;
			default:
				break;
			}
		}
	}
}
const Vector2D& Question::GetLocation() const
{
	return location;
}

const Collision& Question::GetCollision() const
{
	return collision;
}

const unsigned char Question::GetZLayer() const
{
	return z_layer;
}

const bool Question::GetMobility() const
{
	return is_mobility;
}

void Question::SetItemType(Items a)
{
	create_item = a;
}

//�A�j���[�V��������
void Question::AnimationControl(float delta_seconde)
{
	animation_time += delta_seconde;

	if (animation_time >= 0.2)
	{
		animation_time = 0.0f;

		animation_count++;

		if (animation_count >= 4)
		{
			animation_count = 0;
		}

		if (hit_flag == false)
		{
			image = block_image[animation_count];
		}
		else
		{
			image = kara_block;
		}
		
	}
}