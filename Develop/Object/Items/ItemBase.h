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

public:
	ItemBase();
	~ItemBase();

	void Finalize() {
		move_animation.clear();
	}

	//�A�C�e�����o�Ă��鏈��
	void ItemPush();

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

	//�A�C�e���^�C�v�擾
	Items GetItemType();
};