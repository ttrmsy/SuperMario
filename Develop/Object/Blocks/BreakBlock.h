#pragma once
#include "BlockBase.h"
class BreakBlock : public BlockBase
{
public:
	virtual void Initialize() override;
	virtual void Update(float delta_seconde) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;
	void Falling(float delta_second);
	void SetLocation(const Vector2D location);

private:
	int break_sound;
	double radian;
	int rotate_count;

	Vector2D loc_1;			//�{�b�N�X�̍���̍��W
	Vector2D loc_2;			//�{�b�N�X�̍����̍��W
	Vector2D loc_3;			//�{�b�N�X�̉E��̍��W
	Vector2D loc_4;			//�{�b�N�X�̉E��̍��W

	Vector2D velocity;			//�{�b�N�X�̉E��̍��W
};

