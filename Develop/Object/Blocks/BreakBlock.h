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

	Vector2D loc_1;			//ボックスの左上の座標
	Vector2D loc_2;			//ボックスの左下の座標
	Vector2D loc_3;			//ボックスの右上の座標
	Vector2D loc_4;			//ボックスの右上の座標

	Vector2D velocity;			//ボックスの右上の座標
};

