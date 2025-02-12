#pragma once
#include "../Character.h"
#include "../Blocks/Brick.h"

#define D_GRAVITY (9.807f)		//�d�͉����x


class ItemBase : public Character
{
protected:
	std::vector<int> move_animation;	//�A�j���[�V�����摜
	float animation_count;				//�A�j���[�V�����J�E���g
	float animation_time;
	Vector2D old_loction;		//�������W
	bool box_out;				//�{�b�N�X���犮�S�ɏo�Ă��邩
	int item_sound;			//�A�C�e���擾sound
	bool is_ground;
	bool hit_flag;
	float g_velocity;
	class Brick* block_p;

public:
	ItemBase();
	~ItemBase();

	void Finalize() {
		move_animation.clear();
	}


	//�ړ�����
	virtual void Movement(float delta_seconde);

	//�A�C�e�����o�Ă��鏈��
	void ItemPush();

	//�u���b�N�����������Ə�ɒ��˂鏈��
	void Bounce();

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

	//�������W�̕ۑ�
	void SetOldLocation(Vector2D a);

};