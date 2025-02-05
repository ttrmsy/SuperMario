#pragma once
#include "PlayerStateBase.h"
#include "../../../Utility/InputManager.h"

class WalkingState : public PlayerStateBase
{
public:
	InputManager* input;
	float speed;

public:
	WalkingState(class Player* p);
	virtual ~WalkingState();
	virtual void Initialize() override;
	virtual void Update(float delta_seconde) override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual ePlayerState GetState() const override;
	void Set_Speed(float s);
};

