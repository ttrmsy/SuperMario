#pragma once
#include "../Character.h"

enum Items
{
	eNull,
	eCoin,
	eMushroom,
	wFlower,
	eOneup,
	eStar
};

class ItemBase : public Character
{
protected:
	std::vector<int> move_animation;	//�A�j���[�V�����摜
	Items item_type;					//�A�C�e���^�C�v
	float animation_count;				//�A�j���[�V�����J�E���g
	float animation_time;
	Vector2D old_loction;		//�������W
	bool box_out;				//�{�b�N�X���犮�S�ɏo�Ă��邩
	int item_sound;			//�A�C�e���擾sound

public:
	ItemBase();
	~ItemBase();

	void Finalize() {
		move_animation.clear();
	}


	//�ړ�����
	virtual void Movement();

	//�A�C�e�����o�Ă��鏈��
	void ItemPush();

	//�u���b�N�����������Ə�ɒ��˂鏈��
	void Bounce();

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

	//�A�C�e���^�C�v�擾
	Items GetItemType();

	//�������W�̕ۑ�
	void SetOldLocation(Vector2D a);

};