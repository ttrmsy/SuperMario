#pragma once
#include "ItemBase.h"

class Mushroom : public ItemBase
{
public:
	Mushroom();
	~Mushroom();

	//‰Šú‰»ˆ—
	virtual void Initialize() override;

	//XVˆ—
	virtual void Update(float delta_seconde) override;

	//•`‰æˆ—
	virtual void Draw(const Vector2D& screen_offset) const override;

	//I—¹ˆ—
	virtual void Finalize() override;

private:

};
