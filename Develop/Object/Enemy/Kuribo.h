#pragma once
#include "../Character.h"
#include "../../Utility/Collision.h"
#include "../../Utility/Camera.h"

class Kuribo : public Character
{
private:
	std::vector<int> move_animation;
	int animation_count;
	float animation_time;
	float g_velocity;			//重力
	bool is_ground;				//地上
	int die_count = 0;
	Camera* camera;
	class Player* player;

	Vector2D dv;	//デバック用変数

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
	void Filp_flag(bool flag);
	void Set_Velocity(Vector2D velocity);
	void Set_Camera(Camera* c);
	void Set_Player(Player* p);
private:
	void Movement(float delta_seconde);
	void AnimationControl(float delta_seconde);
};

