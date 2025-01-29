#pragma once
#include "BlockBase.h"
class Brick : public BlockBase
{
	public:
	virtual void Initialize() override;
	virtual void Update(float delta_seconde) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;
	virtual const Vector2D& GetLocation() const override;
	virtual const Collision& GetCollision() const override;
	virtual const unsigned char GetZLayer() const override;
	virtual const bool GetMobility() const override;

private:
	std::vector<int> block_image;
	bool up_count;
	bool down_count;
	void AnimationControl(float delta_seconde);
	float animation_time;
	int animation_count;
};

