#include "BreakBlock.h"
#include "../../Utility/ResourceManager.h"
#include "../GameObjectManager.h"
#include "../../Utility/Singleton.h"
#include "DxLib.h"

#define MAX_COUNT	(8)		//�{�b�N�X�㏸�E���~�������J�E���g
#define BOX_HALF	(16.0f)		//�{�b�N�X�㏸�E���~�������J�E���g
#define D_DOWN_SPEED	(50.0f)		//���~�X�s�[�h

void BreakBlock::Initialize()
{	
	ResourceManager* rm = ResourceManager::GetInstance();			//�C���X�^���X�擾
	image = rm->GetImageResource("Resource/Images/Block/bloak_1.png")[0];			//�摜�̓ǂݍ���
	break_sound = rm->GetSoundResource("Resource/Sounds/SE_BlockBreak.wav");		//SE�̓ǂݍ���

	PlaySoundMem(break_sound, DX_PLAYTYPE_BACK);	//SE�Đ�

	is_mobility = true;

	z_layer = 5;

	rotate_count = 0;

	velocity.x = 2.0f;
	velocity.y = -10.0f;
}

void BreakBlock::Update(float delta_seconde)
{
	//��������
	Falling(delta_seconde);

	//roteta_count��10���傫���Ȃ�Ɣj�Ђ̊p�x��ύX����
	if (rotate_count > 10)
	{
		radian += 0.8f;		//�p�x�̕ύX
		rotate_count = 0;	//�J�E���g�̏�����
	}

	//��ʊO�ɍs���Ə�������
	if (location.y > 640)
	{
		//�Q�[���I�u�W�F�N�g�̃|�C���^���擾
		GameObjectManager* gm_p = GameObjectManager::GetInstance();

		//���g���폜���X�g�ɒǉ�
		gm_p->DestroyGameObject(this);
	}

	//�ړ��͂̉��Z
	velocity.y = velocity.y + 1.0f;
	velocity.x = velocity.x + 0.1f;

	//
	rotate_count++;
}

//�`�揈��
void BreakBlock::Draw(const Vector2D& screen_offset) const
{
	//����j�Ђ̕`��
	DrawRotaGraphF(loc_1.x - screen_offset.x, loc_1.y - screen_offset.y, 1.0, -radian, image, TRUE, filp_flag);

	//�����j�Ђ̕`��
	DrawRotaGraphF(loc_2.x - screen_offset.x, loc_2.y - screen_offset.y, 1.0, -radian, image, TRUE, filp_flag);

	//�E��j�Ђ̕`��
	DrawRotaGraphF(loc_3.x - screen_offset.x, loc_3.y - screen_offset.y, 1.0, radian, image, TRUE, filp_flag);

	//�E���j�Ђ̕`��
	DrawRotaGraphF(loc_4.x - screen_offset.x, loc_4.y - screen_offset.y, 1.0, radian, image, TRUE, filp_flag);

}

//�I��������
void BreakBlock::Finalize()
{
	image = NULL;
	break_sound = NULL;
}

//�ړ�����
void BreakBlock::Falling(float delta_seconde)
{
	//���ɗ����Ă�������
	loc_1.y += (velocity.y * D_DOWN_SPEED) * delta_seconde;
	loc_2.y += (velocity.y * D_DOWN_SPEED) * delta_seconde;
	loc_3.y += (velocity.y * D_DOWN_SPEED) * delta_seconde;
	loc_4.y += (velocity.y * D_DOWN_SPEED) * delta_seconde;

	//���E�ɕ�����Ă�������
	loc_1.x -= (velocity.x * D_DOWN_SPEED) * delta_seconde;
	loc_2.x -= (velocity.x * D_DOWN_SPEED) * delta_seconde;
	loc_3.x += (velocity.x * D_DOWN_SPEED) * delta_seconde;
	loc_4.x += (velocity.x * D_DOWN_SPEED) * delta_seconde;
}

//�㉺���E�̍��W�ݒ�
void BreakBlock::SetLocation(Vector2D location)
{
	this->location = location;

	//����̍��W
	loc_1.x = (location.x - BOX_HALF);
	loc_1.y = (location.y - BOX_HALF);

	//�����̍��W
	loc_2.x = (location.x - BOX_HALF);
	loc_2.y = (location.y + BOX_HALF);

	//�E��̍��W
	loc_3.x = (location.x + BOX_HALF);
	loc_3.y = (location.y - BOX_HALF);

	//�E���̍��W
	loc_4.x = (location.x + BOX_HALF);
	loc_4.y = (location.y + BOX_HALF);
	
}