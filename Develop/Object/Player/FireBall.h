#pragma once
#include "../Character.h"
#include "../../Utility/Camera.h"
#include "../Player/Player.h"

class FireBall : public Character
{
private:
	std::vector<int> fire_image;	//�t�@�C�A�{�[���̉摜
	std::vector<int> blast_image;	//�t�@�C�A�{�[���̔��j�摜
	float g_velocity;				//�d��
	double radian;					//��]��
	bool delete_flag;				//�t�@�C�A�{�[���̍폜�t���O
	class Player* player;			//Player�̃|�C���^
	class Camera* camera;			//�J�����|�C���^
	float animation_time;			//�A�j���[�V�����̎���
	int animation_count;			//�A�j���[�V�����̉�
	bool hit_flag;					//�I�u�W�F�N�g�Ƀq�b�g�������̔���t���O

public:
	virtual void Initialize() override;									//����������
	virtual void Update(float delta_seconde) override;					//�X�V����
	virtual void Draw(const Vector2D& screen_offset) const override;	//�`�揈��
	virtual void Finalize() override;									//�I������
	virtual void OnHitCollision(GameObject* hit_object) override;		//�����蔻��ʒm����
	void Set_Filpflag(bool flag);										//���]�t���O�ݒ菈��
	bool Get_DeleteFlag();												//�폜����擾����
	void Set_Camera(class Camera* c);									//�J�����|�C���^�ݒ菈��
	void Set_Player(class Player* p);

private:
	void Movement(float delta_seconde);									//�ړ�����
	void AnimationControl(float delta_seconde);							//�A�j���[�V��������
	
};

