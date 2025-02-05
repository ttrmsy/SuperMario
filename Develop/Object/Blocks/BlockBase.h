#pragma once
#include "../GameObject.h"

class BlockBase : public GameObject
{
protected:
	int block_sound;

public:
	virtual void Initialize() override
	{

	}

	virtual void Update(float delta_seconde) override
	{

	}

	virtual void Draw(const Vector2D& screen_offset) const override
	{
		__super::Draw(screen_offset);
	}

	virtual void Finalize() override
	{
		block_sound = NULL;
	}

	virtual void OnHitCollision(GameObject* hit_object) override
	{

	}

	virtual const Vector2D& GetLocation() const override
	{
		return location;
	}
	virtual const Collision& GetCollision() const override
	{
		return collision;
	}

	virtual const unsigned char GetZLayer() const override
	{
		return z_layer;
	}

	virtual const bool GetMobility() const override
	{
		return is_mobility;
	}
};