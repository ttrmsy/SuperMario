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
	none
};

enum ePlayer_Level
{
	Small,
	Big,
	Fire
};

class Player : public Character
{
private:
	/*std::vector<int> SmallMario_animation;
	std::vector<int> BigMario_animation;
	std::vector<int> FireMario_animation;*/
	std::vector<int> move_animation;	//Player�摜
	std::vector<int> levelup_animation;	//�A�C�e���擾���̃A�j���[�V�����摜
	class PlayerStateBase* player_state;	//Player�̏��
	ePlayerState next_state;	//Player�̑J�ڐ���
	float animation_time;		//�A�j���[�V�����̎���
	int animation_count;		//�A�j���[�V�����̉�
	int animation_number;		//�A�j���[�V�����z��̓Y����
	float g_velocity;			//�d��
	bool is_ground;
	float x;
	bool hit[4];
	ePlayerState p_state;
	class Camera* camera;

	Vector2D dv;	//�f�o�b�N�p�ϐ�
	int is_death;

public:
	bool jump_flag;
	bool slide_flag;
	int animation_num[3][3] = { { 1, 2, 3},
								{ 0, 1, 0},
								{ 0, 1, 2}};	//�A�j���[�V�����̏���
								
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
	void SetNextState(ePlayerState next_state);
	void SetFilp_flag(bool flag);
	bool GetFilp_flag();
	Vector2D Get_Velocity();
	void Set_Velocity(Vector2D velocity);
	void Set_IsGround(bool flag);
	void Set_Camera(Camera* c);
	void Set_SlideFlag(bool flag);
	int Get_DeathCount();

private:
	void Movement(float delta_second);
	void AnimationControl(float delta_seconde);
	void GetItem_Animation(float delta_seconde);
	void DeathCount();


};

