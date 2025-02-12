#pragma once
#include "../Character.h"
#include "PlayerState/PlayerStateBase.h"
#include "../../Utility/Camera.h"
#include <vector>

enum ePlayerState
{
	idle,
	walk,
	jump,
	get,
	damage,
	none
};

enum ePlayerLevel
{
	Small,
	Big,
	Fire
};

class Player : public Character
{
private:
	std::vector<int> SmallMario_animation;		//Player(Small)�̉摜
	std::vector<int> BigMario_animation;		//Player(Big)�̉摜
	std::vector<int> FireMario_animation;		//Player(Fier)�̉摜
	std::vector<int> SmallStarMario_animation;	//Small�̂Ƃ��̃X�^�[��Ԃ̃A�j���[�V�����摜
	std::vector<int> BigStarMarion_animation;	//Big�̂Ƃ��̃X�^�[��Ԃ̃A�j���[�V�����摜
	std::vector<int> levelup_animation;			//���x���A�b�v�̃A�j���[�V�����摜
	class PlayerStateBase* player_state;		//PlayerStateBase�̃|�C���^
	ePlayerState next_state;					//Player�̑J�ڐ���
	ePlayerState p_state;						//Player�̏��
	ePlayerLevel p_level;						//Player�̃��x��
	float animation_time;						//�A�j���[�V�����̎���
	int move_animation_count;					//�A�j���[�V�����̉�
	int move_animation_number;					//�A�j���[�V�����z��̓Y����
	int level_animation_count;					//���x���ύX���̃A�j���[�V�����p�J�E���g
	int level_animation_number;					//���x���ύX���̃A�j���[�V�����p�Y����
	float g_velocity;							//�d��
	bool is_ground;								//�n�ʂɒ��n���Ă��邩�̔���t���O
	class Camera* camera;						//�X�N���[���J�����̃|�C���^
	int fire_count;								//�t�@�C�A�[�{�[�����o������
	bool change_flag;							//Level(UP,Down)�̃A�j���[�V�����̏I������t���O
	bool pipe_enter;							//�y�ǂɓ���邩�ǂ���
	bool pipe_now;								//�y�ǂɓ����Ă���Œ���
	float old_enter_lc;							//�y�ǂɓ���O�̍��W
	int is_death;

public:
	bool jump_flag;								//�W�����v�ł����Ԃ��̔���t���O
	bool slide_flag;							//�}���I���u���[�L���|���Ă����Ԃ��̔���t���O

	//�A�j���[�V�����̏���
	int animation_num[5][3] = { { 1, 2, 3},		//�}���I��Small�̂Ƃ�
								{ 2, 3, 4},		//�}���I��Big��Fire�̂Ƃ�
								{ 0, 1, 0},		//�}���I��Small����Big�Ƀ��x���A�b�v�����Ƃ��i���������j
								{ 0, 1, 2},
								{ 2, 1, 0} };	//�}���I�����x���_�E�������Ƃ�
								
public:
	virtual void Initialize() override;									//����������
	virtual void Update(float delta_seconde) override;					//�X�V����
	virtual void Draw(const Vector2D& screen_offset) const override;	//�`�揈��
	virtual void Finalize() override;									//�I������
	virtual void OnHitCollision(GameObject* hit_object) override;		//�����蔻�菈��
	virtual const Collision& GetCollision() const override;				//�R���W�����擾����
	virtual const unsigned char GetZLayer() const override;				//Z���C���[�擾����
	virtual const bool GetMobility() const override;					//�����擾����
	ePlayerState GetPlayerState() const;								//Player��Ԏ擾����
	void SetNextState(ePlayerState next_state);							//Player�̎��̏�Ԏ擾����
	void SetFilp_flag(bool flag);										//���]�t���O�̐ݒ菈��
	bool GetFilp_flag();												//���]�t���O�̎擾����
	Vector2D Get_Velocity();											//�ړ��ʂ̎擾����
	void Set_Velocity(Vector2D velocity);								//�ړ��ʂ̐ݒ菈��
	void Set_IsGround(bool flag);										//�n�ʂɒ��n���Ă��邩�̔���ݒ菈��
	void Set_Camera(Camera* c);											//�J�����̃|�C���^�ݒ菈��
	void Set_SlideFlag(bool flag);										//�u���[�L���|���Ă����Ԃ��̔���ݒ菈��
	int Get_DeathCount();												
	void Set_FireCount(int count);										//�t�@�C�A�{�[�����o���鐔�̐ݒ菈��
	ePlayerLevel Get_PlayerLevel();										//Player�̃��x���擾����

private:
	void Movement(float delta_second);									//�ړ�����
	void AnimationControl(float delta_seconde);							//�ړ��p�A�j���[�V����
	void Levelup_Animation(float delta_seconde);						//���x���A�b�v���̃A�j���[�V����
	void Fire_Animation(float delta_seconde);							//
	void Leveldown_Animation(float delta_seconde);						//���x���_�E�����̃A�j���V���[��
	void DeathCount();


};
