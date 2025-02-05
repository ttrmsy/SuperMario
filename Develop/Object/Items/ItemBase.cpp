#include "ItemBase.h"
#include "../GameObjectManager.h"
#include "../../Utility/ResourceManager.h"

#define ITEM_SPEED		(50.0f)

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


	this->location += velocity * ITEM_SPEED * delta_seconde;
}

//�����蔻�菈��
void ItemBase::OnHitCollision(GameObject* hit_object)
{
	

	// ���������I�u�W�F�N�g���v���C���[��������A�폜����
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer && box_out == true)
	{
		//�Q�[���I�u�W�F�N�g�̃|�C���^���擾
		GameObjectManager* gm_p = GameObjectManager::GetInstance();

		//PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);

		gm_p->DestroyGameObject(this);
	}
}

//�{�b�N�X����o�Ă��鏈��
void ItemBase::ItemPush()
{
	//�A�C�e�����R�C���ȊO�̏ꍇ
	if (item_type != eCoin)
	{
		if (this->location.y > old_loction.y - 27.0f)
		{
			location.y -= 0.5f;

			velocity = 0.0f;

			box_out = false;

			return;
		}
	}
	else  //�R�C���������ꍇ
	{
		if (this->location.y > old_loction.y - ((32.0f * 3) - 5.0f))
		{
			location.y -= 2.0f;

			velocity = 0.0f;

			box_out = false;

			return;
		}
	}
	
	box_out = true;

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