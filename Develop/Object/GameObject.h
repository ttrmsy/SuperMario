#pragma once
#include "../Utility/ProjectConfig.h"
#include "../Utility/Vector2D.h"
#include "../Utility/Collision.h"


#define OBJECT_SIZE	(32.0f)

enum State
{
	live,
	down,
	die
};

class GameObject
{
protected:
	Vector2D location;
	Collision collision;
	int image;
	unsigned char z_layer;
	bool is_mobility;
	bool filp_flag;
	bool hit_flag;
	class Player* player;
	State state;

public:
	virtual void Initialize();
	virtual void Update(float delta_second);
	virtual void Draw(const Vector2D& screen_offset) const;
	virtual void Finalize();
	virtual void OnHitCollision(GameObject* hit_object);
	virtual void Set_Hitflag(bool flag);
	virtual const Vector2D& GetLocation() const;
	void SetLocation(const Vector2D location);
	virtual const Collision& GetCollision() const;
	virtual const State& Get_State()const;
	virtual const unsigned char GetZLayer() const;
	virtual const bool GetMobility() const;
};

