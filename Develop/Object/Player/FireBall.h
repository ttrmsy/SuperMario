#pragma once
#include "../Character.h"

class FireBall : public Character
{
private:
	std::vector<int> fire_image;
	float g_velocity;
	double radian;

public:
	virtual void Initialize() override;
	virtual void Update(float delta_seconde) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;
	void Set_Filpflag(bool flag);

private:
	void Movement(float delta_seconde);
};

