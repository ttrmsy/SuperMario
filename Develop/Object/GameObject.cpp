#include "GameObject.h"
#include "DxLib.h"

/// <summary>
/// ����������
/// </summary>
void GameObject::Initialize()
{
	
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void GameObject::Update(float delta_second)
{

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset">�I�t�Z�b�g�l</param>
void GameObject::Draw(const Vector2D& screen_offset) const
{
	Vector2D graph_location = this->location - screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE, filp_flag);

}

/// <summary>
/// �I��������
/// </summary>
void GameObject::Finalize()
{

}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void GameObject::OnHitCollision(GameObject* hit_object)
{

}

void GameObject::Set_Hitflag(bool flag)
{
	hit_flag = flag;
}

/// <summary>
/// �ʒu���W�擾����
/// </summary>
/// <returns>�ʒu���W���</returns>
const Vector2D& GameObject::GetLocation() const
{
	return location;
}

// <summary>
/// �ʒu���ύX����
/// </summary>
/// <param name="location">�ύX�������ʒu���</param>
void GameObject::SetLocation(const Vector2D location)
{
	this->location = location;
}

/// <summary>
/// �����蔻��擾����
/// </summary>
/// <returns>�����蔻����</returns>
const Collision& GameObject::GetCollision() const
{
	return collision;
}

const State& GameObject::Get_State()const 
{
	return state;
}


/// <summary>
/// Z���C���[���擾����
/// </summary>
/// <returns>Z���C���[���</returns>
const unsigned char GameObject::GetZLayer() const
{
	return z_layer;
}

/// <summary>
/// �������̎擾����
/// </summary>
/// <returns>�������</returns>
const bool GameObject::GetMobility() const
{
	return is_mobility;
}

