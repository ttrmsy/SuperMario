#pragma once
#include "../GameObject.h"
//#include "../Player/Player.h"

class BlockBase : public GameObject
{
protected:
	int block_sound;
	bool now_bouce;			//â∫Ç©ÇÁê⁄êGÇ≥ÇÍÇΩÇ©Ç«Ç§Ç©
	/*class Player* p_pointer;*/

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
		/*p_pointer = nullptr;*/
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

	const bool GetBounce() const
	{
		return now_bouce;
	}
	
	//void SetPlayerPointer(Player* player)
	//{
	//	if (player != nullptr)
	//	{
	//		p_pointer = player;
	//	}
	//}
};