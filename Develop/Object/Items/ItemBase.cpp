#include "ItemBase.h"
#include "../GameObjectManager.h"
#include "../../Utility/ResourceManager.h"

ItemBase::ItemBase() : animation_count(0.0f),
animation_time(0.0f),
item_type(eNull),
box_out(false),
item_sound(NULL)
{
	//���\�[�X�}�l�[�W���[�̃C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();
	item_sound = rm->GetSoundResource("Resource/Sounds/SE_ItemAppearance.wav");	//�A�C�e�����o�Ă������̉�

	//�A�C�e�����o�Ă������̉��𗬂�
	PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);
}

ItemBase::~ItemBase()
{

}

void ItemBase::Movement()
{

}

//�����蔻�菈��
void ItemBase::OnHitCollision(GameObject* hit_object)
{
	// ���������I�u�W�F�N�g���v���C���[��������A�폜����
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer && box_out == true)
	{
		//�Q�[���I�u�W�F�N�g�̃|�C���^���擾
		GameObjectManager* gm_p = GameObjectManager::GetInstance();

		PlaySoundMem(item_sound, DX_PLAYTYPE_BACK);

		gm_p->DestroyGameObject(this);
	}
}

//���˂鏈��
void ItemBase::ItemPush()
{
	if (this->location.y > old_loction.y - 32.0f)
	{
		location.y -= 1.0f;

		box_out = false;

		return;
	}

	box_out = true;

}

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