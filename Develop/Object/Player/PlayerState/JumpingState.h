#pragma once
#include "PlayerStateBase.h"
class JumpingState : public PlayerStateBase
{
private:
	float g_velocity;
	Vector2D j_velocity;
	float Held_jump;
	int count;

public:
	JumpingState(class Player* p);

	virtual ~JumpingState();

	virtual void Initialize() override;
	virtual void Update(float delta_seconde) override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual ePlayerState GetState() const override;
};

